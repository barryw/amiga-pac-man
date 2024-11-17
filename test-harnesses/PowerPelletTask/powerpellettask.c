/**
 * @brief   Power Pellet Task
 * @verbose Blink the power pellet register using the timer device.
 * @author  Thomas Cherryhomes
 * @email   thom dot cherryhomes at gmail dot com
 * @license GPL v. 3, see LICENSE for details.
 */

#include <clib/alib_protos.h>
#include <clib/dos_protos.h>
#include <clib/exec_protos.h>
#include <clib/graphics_protos.h>
#include <clib/intuition_protos.h>
#include <devices/timer.h>
#include <exec/lists.h>
#include <exec/nodes.h>
#include <exec/ports.h>
#include <exec/tasks.h>
#include <exec/types.h>
#include <graphics/gfx.h>
#include <graphics/gfxbase.h>
#include <hardware/custom.h>
#include <hardware/intbits.h>
#include <intuition/intuition.h>

#include "../font.h"
#include "../MazeBorders2.h"

#define SCREEN_HEIGHT 218
#define SCREEN_WIDTH 320

struct GfxBase *GfxBase;
struct IntuitionBase *IntuitionBase;
extern struct Custom custom;

/** The Test Harness *******************************************************/

volatile int frame_count = 0;
volatile BOOL powerPelletOn = FALSE;
volatile BOOL pauseBlink = TRUE;

struct Task *task;

struct Screen *sPacMan;
struct Window *wPacMan;

struct NewScreen nsPacMan = {
	.LeftEdge = 0, .TopEdge = 0,
	.Width = SCREEN_WIDTH, .Height = SCREEN_HEIGHT, .Depth = 4,
	.DetailPen = 3, .BlockPen = 0,
	.ViewModes = 0,
	.Type = CUSTOMSCREEN | SCREENQUIET,
	.Font = NULL,
	.DefaultTitle = "PACMAN",
	.Gadgets = NULL,
};

struct NewWindow nwPacMan =
{
	0, 0,
	SCREEN_WIDTH, SCREEN_HEIGHT,
	0, 1,
	IDCMP_RAWKEY,
	BORDERLESS | BACKDROP,
	NULL,
	NULL,
	"PAC-MAN(tm)",
	NULL,
	NULL,
	SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT,
	CUSTOMSCREEN
};

struct TextAttr taFont = {
	"Arcade8.font",
	8,
	FS_NORMAL,
	FPF_DESIGNED
};

USHORT colorTable[16] =
{
	0x000, /* 0: Black */
	0xFF0, /* 1: Yellow */
	0xF00, /* 2: Light Red */
	0xFFF, /* 3: White */
	0x00F, /* 4: Light Blue */
	0xF0F, /* 5: Light Magenta */
	0x0FF, /* 6: Light Cyan */
	0x770, /* 7: Dark Yellow (pale orange?) */
	0x0F0, /* 8: Light Green */
	0xFA0, /* 9: Light Orange */
	0xFEF, /* A: Pinky white */
	0xFCB, /* B: Power Pellet */
	0x0FF, /* C: Light Cyan */
	0xF00, /* D: Light Red */
	0xF0F, /* E: Light Magenta */
	0xFFF, /* F: White */
};

UWORD bmPellet[] =
{
	/* BITPLANE 0 */
	0x7800, /* 0111100000000000 */
	0xFC00, /* 1111110000000000 */
	0xFC00, /* 1111110000000000 */
	0xFC00, /* 1111110000000000 */
	0xFC00, /* 1111110000000000 */
	0x7800, /* 0111100000000000 */

	/* BITPLANE 1 */
	0x7800, /* 0111100000000000 */
	0xFC00, /* 1111110000000000 */
	0xFC00, /* 1111110000000000 */
	0xFC00, /* 1111110000000000 */
	0xFC00, /* 1111110000000000 */
	0x7800, /* 0111100000000000 */

	/* BITPLANE 3 */
	0x7800, /* 0111100000000000 */
	0xFC00, /* 1111110000000000 */
	0xFC00, /* 1111110000000000 */
	0xFC00, /* 1111110000000000 */
	0xFC00, /* 1111110000000000 */
	0x7800, /* 0111100000000000 */
};

struct Image iPellet =
{
	0, 0,
	6, 6, 4,
	bmPellet,
	0x0B, 0x00
};

// int BlinkPelletWait() {
// #ifdef __AMIGAOS32__
// 	TimeDelay(UNIT_VBLANK, 0, 100000);
// #else
// 	struct timeval tv;
//
// 	/* Create the timer ************************************************/
//
// 	struct MsgPort *timerPort = CreatePort(0, 0); /* Private port */
//
// 	if (!timerPort) return -1;
//
// 	struct timerequest *timerMsg = (struct timerequest *) CreateExtIO(timerPort, sizeof(struct timerequest));
//
// 	if (!timerMsg) {
// 		DeletePort(timerPort);
// 		return FALSE;
// 	}
//
// 	const int error = OpenDevice(TIMERNAME, UNIT_VBLANK, (struct IORequest *) timerMsg, 0);
//
// 	if (error) {
// 		if (timerMsg->tr_node.io_Message.mn_ReplyPort)
// 			DeletePort(timerMsg->tr_node.io_Message.mn_ReplyPort);
// 		CloseDevice((struct IORequest *) timerMsg);
// 		DeleteExtIO((struct IORequest *) timerMsg);
// 		return FALSE;
// 	}
//
// 	/* Set the timer to fire every BLINK microseconds *******************/
//
// 	tv.tv_secs = 0;
// 	tv.tv_micro = 100000;
//
// 	timerMsg->tr_node.io_Command = TR_ADDREQUEST;
// 	timerMsg->tr_time = tv;
//
// 	/* Do it. */
// 	DoIO((struct IORequest *) timerMsg);
//
// 	/* Tear down and close timer ****************************************/
//
// 	if (timerMsg->tr_node.io_Message.mn_ReplyPort)
// 		DeletePort(timerMsg->tr_node.io_Message.mn_ReplyPort);
//
// 	CloseDevice((struct IORequest *) timerMsg);
//
// 	/* DeleteExtIO will close the timerPort */
// 	DeleteExtIO((struct IORequest *) timerMsg);
// #endif
//
// 	return TRUE;
// }

/* The blink-on color, as blink-off is all zeroes. */

#define BLINK_R 0xF
#define BLINK_G 0xC
#define BLINK_B 0xB
#define BLINK_COLOR 0x0B

// void PowerPelletTask() {
// 	int bOnOff = 0;
//
// 	FOREVER /* RJ Mical'ism */
// 	{
// 		/* we only start task after screen is ready, so... */
//
// 		// ReSharper disable once CppDFAEndlessLoop
// 		SetRGB4(&sPacMan->ViewPort,
// 		        BLINK_COLOR,
// 		        bOnOff ? BLINK_R : 0x00,
// 		        bOnOff ? BLINK_G : 0x00,
// 		        bOnOff ? BLINK_B : 0x00);
//
// 		bOnOff = !bOnOff;
//
// 		/* The DoIO will cause a Wait(), so no needless spinning */
// 		BlinkPelletWait();
// 	}
// }

void __amigainterrupt BlinkPowerPelletInterrupt() {
	if (!pauseBlink) {
		if (frame_count < 6) {
			frame_count++;
		} else {
			frame_count = 0;
			SetRGB4(&sPacMan->ViewPort, BLINK_COLOR,
			        powerPelletOn ? BLINK_R : 0x0000,
			        powerPelletOn ? BLINK_G : 0x0000,
			        powerPelletOn ? BLINK_B : 0x0000);

			powerPelletOn = (BOOL) !powerPelletOn;
		}
	} else {
		SetRGB4(&sPacMan->ViewPort, BLINK_COLOR, BLINK_R, BLINK_G, BLINK_B);
	}
	// Acknowledge the interrupt to avoid system lock-ups
	custom.intreq = INTF_VERTB; // Clear VBL interrupt
}

void drawRectangle(struct RastPort *rp, const int tileX, const int tileY) {
	const int pixPerTile = SCREEN_HEIGHT / 31;
	const WORD startX = tileX * pixPerTile;
	const WORD startY = tileY * pixPerTile;
	const WORD endX = tileX * pixPerTile + pixPerTile;
	const WORD endY = tileY * pixPerTile + pixPerTile;

	Move(rp, startX, startY);
	Draw(rp, endX, startY);
	Draw(rp, endX, endY);
	Draw(rp, startX, endY);
	Draw(rp, startX, startY);
}

// void setupPelletBlink() {
// 	struct UCopList *uCopList = AllocMem(sizeof(struct UCopList), MEMF_PUBLIC | MEMF_CLEAR);
// 	if (!uCopList) return;
// 	CINIT(uCopList, 15);
// 	// for (int i = 0; i < 6; i++) {
// 	// 	//CWAIT(uCopList, 0, 0);
// 	// 	CWAIT(uCopList, 0xff, 0xff);
// 	// }
// 	// CMOVE(uCopList, custom.color[0xb], 0x0000);
// 	// for (int i = 0; i < 6; i++) {
// 	// 	//CWAIT(uCopList, 0, 0);
// 	// 	CWAIT(uCopList, 0xff, 0xff);
// 	// }
// 	CWAIT(uCopList, 0x00, 0x00);
// 	CMOVE(uCopList, custom.color[0], 0x0000);
// 	CWAIT(uCopList, 0x62, 0x00);
// 	CMOVE(uCopList, custom.color[0], 0x0FCB);
// 	CEND(uCopList);
//
// 	struct ViewPort *viewPort = ViewPortAddress(wPacMan);
// 	Forbid();
// 	viewPort->UCopIns = uCopList;
// 	Permit();
// 	RethinkDisplay();
// }

/* The Test Harness ******************************************************/

int main() {
	struct Interrupt *vbint = AllocMem(sizeof(struct Interrupt), MEMF_PUBLIC | MEMF_CLEAR);

	GfxBase = (struct GfxBase *) OpenLibrary("graphics.library", 0);

	if (!GfxBase)
		goto bye;

	IntuitionBase = (struct IntuitionBase *) OpenLibrary("intuition.library", 0);

	if (!IntuitionBase)
		goto bye;

	FontInit_Arcade8();
	AddFont(&Arcade8Font);

	nsPacMan.Font = &taFont;

	sPacMan = OpenScreen(&nsPacMan);
	if (!sPacMan)
		goto bye;

	LoadRGB4(&sPacMan->ViewPort, colorTable, 16);

	nwPacMan.Screen = sPacMan;
	wPacMan = OpenWindow(&nwPacMan);
	if (!wPacMan)
		goto bye;

	ClearPointer(wPacMan);
	SetRast(wPacMan->RPort, 0);

	struct RastPort *rp = &sPacMan->RastPort;

	// Set the drawing pen to a specific color(e.g., 2 = red, 1 = blue, etc.)
	SetAPen(rp, 0xa);

	for (int x = 0; x < 28; x++) {
		for (int y = 0; y < 31; y++) {
			drawRectangle(rp, x, y);
		}
	}

	// // Draw the outline of a rectangle
	// Move(rp, 0, 0); // Move to the top-left corner
	// Draw(rp, sPacMan->Width - 1, 0); // Draw to the top-right corner
	// Draw(rp, sPacMan->Width - 1, sPacMan->Height - 1); // Draw to the bottom-right corner
	// Draw(rp, 0, sPacMan->Height - 1); // Draw to the bottom-left corner
	// Draw(rp, 0, 0);

	DrawMaze(&sPacMan->RastPort);
	//DrawBorder(wPacMan->RPort, &boMaze, 0, 0);

	DrawImage(wPacMan->RPort, &iPellet, 1 * 7 + 1, 3 * 7 + 1);
	DrawImage(wPacMan->RPort, &iPellet, 26 * 7 + 1, 3 * 7 + 1);
	DrawImage(wPacMan->RPort, &iPellet, 1 * 7 + 1, 23 * 7 + 1);
	DrawImage(wPacMan->RPort, &iPellet, 26 * 7 + 1, 23 * 7 + 1);

	if (vbint) {
		vbint->is_Node.ln_Type = NT_INTERRUPT;
		vbint->is_Node.ln_Pri = -60;
		vbint->is_Node.ln_Name = "PowerPelletTask";
		vbint->is_Code = &BlinkPowerPelletInterrupt;

		AddIntServer(INTB_VERTB, vbint);
	}

	Delay(300);
	pauseBlink = FALSE;

	//setupPelletBlink();
	//task = CreateTask("powerpellet.task", 0, &PowerPelletTask, 1000);

	WaitPort(wPacMan->UserPort);
	struct IntuiMessage *msg;
	while ((msg = (struct IntuiMessage *) GetMsg(wPacMan->UserPort)) != NULL) {
		ReplyMsg((struct Message *) msg);
	}

bye:
	RemIntServer(INTB_VERTB, vbint);
	FreeMem(vbint, sizeof(struct Interrupt));

	if (task)
		DeleteTask(task);

	RemFont(&Arcade8Font);

	if (wPacMan) {
		// struct ViewPort *viewPort = ViewPortAddress(wPacMan);
		// if (viewPort && viewPort->UCopIns) {
		// 	FreeVPortCopLists(viewPort);
		// 	RemakeDisplay();
		// }
		CloseWindow(wPacMan);
	}

	if (sPacMan)
		CloseScreen(sPacMan);

	if (IntuitionBase)
		CloseLibrary((struct Library *) IntuitionBase);

	if (GfxBase)
		CloseLibrary((struct Library *) GfxBase);
}
