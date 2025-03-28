//
// Created by Barry Walker on 3/26/25.
//

#include "intromusic.h"

#include <stdlib.h>
#include <clib/alib_protos.h>
#include <clib/dos_protos.h>
#include <clib/exec_protos.h>
#include <devices/audio.h>
#include <graphics/gfxbase.h>
#include <proto/dos.h>

#define PERIOD(clock) ((clock) / 22050)
#define VOLUME 64

struct GfxBase *GfxBase;
struct IOAudio *AudioLeft, *AudioRight;
struct MsgPort *AudioMP;
struct Message *AudioMSG;
LONG clock;
ULONG leftDevice, rightDevice;
BYTE *waveptr;
UBYTE leftChannel = 1;
UBYTE rightChannel = 2;

int main() {
    GfxBase = (struct GfxBase *) OpenLibrary("graphics.library", 0L);
    if (GfxBase == NULL) {
        Printf("Couldn't open graphics.library\n");
        goto bye;
    }
    if (GfxBase->DisplayFlags & PAL) {
        clock = 3546895;
        Printf("Playing on a PAL machine.\n");
    } else {
        clock = 3579545;
        Printf("Playing on an NTSC machine.\n");
    }

    CloseLibrary((struct Library *) GfxBase);

    AudioMP = CreatePort(0, 0);
    if (AudioMP == 0) {
        Printf("Couldn't allocate MsgPort\n");
        goto bye;
    }

    AudioLeft = (struct IOAudio *) AllocMem(sizeof(struct IOAudio), MEMF_PUBLIC | MEMF_CLEAR);
    AudioRight = (struct IOAudio *) AllocMem(sizeof(struct IOAudio), MEMF_PUBLIC | MEMF_CLEAR);
    if (AudioLeft == NULL || AudioRight == NULL) {
        Printf("Couldn't allocate channel memory.\n");
        goto bye;
    }

    AudioLeft->ioa_Request.io_Message.mn_ReplyPort = AudioMP;
    AudioLeft->ioa_Request.io_Message.mn_Node.ln_Pri = 0;
    AudioLeft->ioa_Request.io_Command = ADCMD_ALLOCATE;
    AudioLeft->ioa_Request.io_Flags = ADIOF_NOWAIT;
    AudioLeft->ioa_AllocKey = 0;
    AudioLeft->ioa_Data = &leftChannel;
    AudioLeft->ioa_Length = 1;

    leftDevice = (unsigned char) OpenDevice(AUDIONAME, 0L, (struct IORequest *) AudioLeft, 0L);
    if (leftDevice != 0) {
        Printf("Couldn't open left channel\n");
        goto bye;
    }

    AudioRight->ioa_Request.io_Message.mn_ReplyPort = AudioMP;
    AudioRight->ioa_Request.io_Message.mn_Node.ln_Pri = 0;
    AudioRight->ioa_Request.io_Command = ADCMD_ALLOCATE;
    AudioRight->ioa_Request.io_Flags = ADIOF_NOWAIT;
    AudioRight->ioa_AllocKey = 0;
    AudioRight->ioa_Data = &rightChannel;
    AudioRight->ioa_Length = 1;

    rightDevice = (unsigned char) OpenDevice(AUDIONAME, 0L, (struct IORequest *) AudioRight, 0L);
    if (rightDevice != 0) {
        Printf("Couldn't open right channel\n");
        goto bye;
    }

    AudioLeft->ioa_Request.io_Command = CMD_WRITE;
    AudioLeft->ioa_Request.io_Flags = ADIOF_PERVOL;
    AudioLeft->ioa_Data = pacintro_raw;
    AudioLeft->ioa_Length = pacintro_raw_len;
    AudioLeft->ioa_Period = clock / 11025;
    AudioLeft->ioa_Volume = 64;
    AudioLeft->ioa_Cycles = 1;

    AudioRight->ioa_Request.io_Command = CMD_WRITE;
    AudioRight->ioa_Request.io_Flags = ADIOF_PERVOL;
    AudioRight->ioa_Data = pacintro_raw;
    AudioRight->ioa_Length = pacintro_raw_len;
    AudioRight->ioa_Period = clock / 11025;
    AudioRight->ioa_Volume = 64;
    AudioRight->ioa_Cycles = 1;

    Printf("Ready to play.\n");

    BeginIO((struct IORequest *) AudioLeft);
    BeginIO((struct IORequest *) AudioRight);

    WaitPort(AudioMP);
    GetMsg(AudioMP);
    WaitPort(AudioMP);
    GetMsg(AudioMP);

    AudioLeft->ioa_Request.io_Command = ADCMD_FREE;
    DoIO((struct IORequest *) AudioLeft);

    AudioRight->ioa_Request.io_Command = ADCMD_FREE;
    DoIO((struct IORequest *) AudioRight);

bye:

    if (AudioLeft) {
        FreeMem(AudioLeft, sizeof(struct IOAudio));
    }
    if (AudioRight) {
        FreeMem(AudioRight, sizeof(struct IOAudio));
    }
    if (leftDevice == 0) {
        CloseDevice((struct IORequest *) AudioLeft);
    }
    if (rightDevice == 0) {
        CloseDevice((struct IORequest *) AudioRight);
    }
    if (AudioMP) {
        DeletePort(AudioMP);
    }

    return EXIT_SUCCESS;
}
