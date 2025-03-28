#include "sound_manager.h"

#include <exec/types.h>
#include <exec/memory.h>
#include <exec/execbase.h>
#include <devices/audio.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <graphics/gfxbase.h>
#include <string.h>
#include <clib/alib_protos.h>

#define STACK_SIZE 4096
#define CHANNELS 4

struct SoundChannel {
    struct IOAudio *ios[CHANNELS];
    struct MsgPort *ports[CHANNELS];
    int count;
};

struct SoundData {
    UBYTE *data;
    ULONG length;
    ULONG sampleRate;
    BYTE priority;
    UBYTE volume;
    BOOL stereo;
};

static ULONG audioClock;

static void init_audio_system() {
    struct GfxBase *gfx = (struct GfxBase *) OpenLibrary("graphics.library", 0);
    audioClock = gfx ? (gfx->DisplayFlags & PAL ? 3546895 : 3579545) : 3579545;
    if (gfx) CloseLibrary((struct Library *) gfx);
}

static void free_channel(struct IOAudio *io, struct MsgPort *port) {
    if (io) {
        io->ioa_Request.io_Command = ADCMD_FREE;
        DoIO((struct IORequest *) io);
        CloseDevice((struct IORequest *) io);
        FreeMem(io, sizeof(struct IOAudio));
    }
    if (port) DeletePort(port);
}

static void free_all_channels(struct SoundChannel *ch) {
    for (int i = 0; i < ch->count; ++i)
        free_channel(ch->ios[i], ch->ports[i]);
    FreeMem(ch, sizeof(struct SoundChannel));
}

static struct SoundChannel *allocate_sound_channel(const BYTE priority, const BOOL stereo) {
    static const UBYTE monoMasks[] = {1, 2, 4, 8};
    static const UBYTE stereoMasks[] = {3, 5, 10, 12};
    const UBYTE *maskList = stereo ? stereoMasks : monoMasks;
    const ULONG maskCount = stereo ? sizeof(stereoMasks) : sizeof(monoMasks);

    struct MsgPort *port = CreatePort(0, 0);
    if (!port) return NULL;

    struct IOAudio *master = AllocMem(sizeof(struct IOAudio), MEMF_PUBLIC | MEMF_CLEAR);
    if (!master) {
        DeletePort(port);
        return NULL;
    }

    master->ioa_Request.io_Message.mn_ReplyPort = port;
    master->ioa_Request.io_Message.mn_Node.ln_Pri = priority;
    master->ioa_Request.io_Command = ADCMD_ALLOCATE;
    master->ioa_Request.io_Flags = ADIOF_NOWAIT;
    master->ioa_Data = (UBYTE *) maskList;
    master->ioa_Length = maskCount;

    if (OpenDevice(AUDIONAME, 0L, (struct IORequest *) master, 0L)) {
        FreeMem(master, sizeof(struct IOAudio));
        DeletePort(port);
        return NULL;
    }

    const UBYTE owned = (ULONG) master->ioa_Request.io_Unit & 0x0F;
    int count = 0;
    for (int i = 0; i < CHANNELS; ++i)
        if (owned & 1 << i) ++count;

    if (count == 0) {
        free_channel(master, port);
        return NULL;
    }

    struct SoundChannel *ch = AllocMem(sizeof(struct SoundChannel), MEMF_PUBLIC | MEMF_CLEAR);
    if (!ch) {
        free_channel(master, port);
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < CHANNELS && index < count; ++i) {
        if (owned & 1 << i) {
            struct IOAudio *io = AllocMem(sizeof(struct IOAudio), MEMF_PUBLIC | MEMF_CLEAR);
            struct MsgPort *msgPort = CreatePort(0, 0);
            if (!io || !msgPort) {
                if (io) FreeMem(io, sizeof(struct IOAudio));
                if (msgPort) DeletePort(msgPort);
                continue;
            }
            *io = *master;
            io->ioa_Request.io_Message.mn_ReplyPort = msgPort;
            io->ioa_Request.io_Unit = (struct Unit *) (ULONG) (1 << i);
            ch->ios[index] = io;
            ch->ports[index] = msgPort;
            ++index;
        }
    }

    FreeMem(master, sizeof(struct IOAudio));
    DeletePort(port);

    ch->count = index;
    return ch;
}

void sound_task() {
    struct Task *thisTask = FindTask(NULL);
    struct SoundData *snd = thisTask->tc_UserData;
    struct SoundChannel *ch = allocate_sound_channel(snd->priority, snd->stereo);
    if (!ch) goto cleanup;

    ULONG period = audioClock / snd->sampleRate;

    for (int i = 0; i < ch->count; ++i) {
        struct IOAudio *io = ch->ios[i];
        io->ioa_Request.io_Command = CMD_WRITE;
        io->ioa_Request.io_Flags = ADIOF_PERVOL | ADIOF_NOWAIT;
        io->ioa_Data = snd->data;
        io->ioa_Length = snd->length;
        io->ioa_Period = period;
        io->ioa_Volume = snd->volume;
        io->ioa_Cycles = 1;
        BeginIO((struct IORequest *) io);
    }

    for (int i = 0; i < ch->count; ++i) {
        WaitPort(ch->ports[i]);
        GetMsg(ch->ports[i]);
    }

    free_all_channels(ch);

cleanup:
    FreeMem(snd, sizeof(struct SoundData));
    FreeMem(thisTask->tc_SPLower, STACK_SIZE);
    FreeMem(thisTask, sizeof(struct Task));
}

void play_sound(const UBYTE *data, const ULONG length, const ULONG sampleRate, const BOOL stereo, const BYTE priority,
                const UBYTE volume) {
    struct SoundData *snd = AllocMem(sizeof(struct SoundData), MEMF_PUBLIC | MEMF_CLEAR);
    if (!snd) return;

    snd->data = (UBYTE *) data;
    snd->length = length;
    snd->sampleRate = sampleRate;
    snd->priority = priority;
    snd->volume = volume ? volume : DEFAULT_VOLUME;
    snd->stereo = stereo;

    struct Task *task = AllocMem(sizeof(struct Task), MEMF_PUBLIC | MEMF_CLEAR);
    if (!task) goto fail;

    task->tc_Node.ln_Type = NT_TASK;
    task->tc_Node.ln_Pri = 5;
    task->tc_Node.ln_Name = "SoundTask";
    task->tc_UserData = snd;
    task->tc_SPLower = AllocMem(STACK_SIZE, MEMF_PUBLIC | MEMF_CLEAR);
    if (!task->tc_SPLower) goto fail_task;

    task->tc_SPUpper = (APTR) ((ULONG) task->tc_SPLower + STACK_SIZE);
    task->tc_SPReg = task->tc_SPUpper;

    if (!AddTask(task, sound_task, NULL)) {
        FreeMem(task->tc_SPLower, STACK_SIZE);
        goto fail_task;
    }

    return;

fail_task:
    FreeMem(task, sizeof(struct Task));
fail:
    FreeMem(snd, sizeof(struct SoundData));
}

void init_sound_manager() {
    init_audio_system();
}
