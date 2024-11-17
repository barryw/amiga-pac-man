/**
 * @brief   a simple WSG sanity check.
 * @author  Thom Cherryhomes 
 * @email   thom dot cherryhomes at gmail dot com
 * @license GPL v. 3, see license.md for details.
 */

#include <clib/alib_protos.h>
#include <clib/exec_protos.h>
#include <exec/types.h>
#include <devices/audio.h>
#include "waveforms.h"

#define PRIORITY ADALLOC_MINPREC

#define MAXVOLUME 64
#define PERIODSIZE 256

#define CHANNEL0 1
#define CHANNEL1 2
#define CHANNEL2 4
#define CHANNEL3 8

struct IOAudio *audioIOB = 0;
struct MsgPort *port = 0;

UBYTE allocationMap[] =
{
	3, 5, 10, 12
};

UBYTE deviceOpened = FALSE;


/**
 * @brief Initialize sound for playback
 */
int init() {
	deviceOpened = FALSE;

	/* Create our reply port. */
	port = CreatePort(NULL, NULL);
	if (!port) {
		return FALSE;
	}

	/* Create our audio I/O block */
	audioIOB = (struct IOAudio *) CreateExtIO(port, sizeof(struct IOAudio));
	if (!audioIOB) {
		return FALSE;
	}

	/* setup audio block with priority and allocation map */
	/* This gets sent as part of OpenDevice.              */
	audioIOB->ioa_Request.io_Message.mn_Node.ln_Pri = PRIORITY;
	audioIOB->ioa_Data = allocationMap;
	audioIOB->ioa_Length = sizeof(allocationMap);

	if (OpenDevice(AUDIONAME, 0, (struct IORequest *) audioIOB, 0)) /* 0 = success */
	{
		return FALSE;
	}

	deviceOpened = TRUE;

	return TRUE;
}

/**
 * @brief Do each wsg
 */
int do_wsg() {
	int i = 0;

	if (!deviceOpened)
		return FALSE;

	for (i = 0; i < 8; i++) {
		/* Setup I/O block to write to audio device */
		audioIOB->ioa_Request.io_Command = CMD_WRITE;
		audioIOB->ioa_Request.io_Flags = ADIOF_PERVOL;
		audioIOB->ioa_Data = waveforms[i];
		audioIOB->ioa_Length = WAVEFORM_SIZE;
		audioIOB->ioa_Period = PERIODSIZE;
		audioIOB->ioa_Volume = MAXVOLUME;
		audioIOB->ioa_Cycles = 512; /* play waveform for a bit */
		BeginIO((struct IORequest *) audioIOB);
		WaitIO((struct IORequest *) audioIOB);
	}

	return TRUE;
}

/**
 * @brief clean up
 */
int done() {
	if (deviceOpened)
		CloseDevice((struct IORequest *) audioIOB);

	if (audioIOB) {
		DeleteExtIO((struct IORequest *) audioIOB);
	}

	if (port)
		DeletePort(port);

	return TRUE;
}

int main() {
	if (!init())
		done();

	do_wsg();

	done();

	return 0;
}
