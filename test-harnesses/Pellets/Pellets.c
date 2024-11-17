/**
 * @brief   Draw Pellets
 * @verbose Draw Pellets for the board
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
#include <intuition/intuition.h>

#include "Dots.h"
#include "../font.h"
#include "../MazeBorders.h"

#define TEXT_HEIGHT			8
#define HEADER_HISCORE_X	232
#define HEADER_HISCORE_Y 	24
#define SCORE_HISCORE_Y 	(HEADER_HISCORE_Y + TEXT_HEIGHT)
#define HEADER_1UP_Y		48
#define SCORE_1UP_Y			(HEADER_1UP_Y + TEXT_HEIGHT)
#define HEADER_2UP_Y		72
#define SCORE_2UP_Y			(HEADER_2UP_Y + TEXT_HEIGHT)
#define SCORE_X				264

struct GfxBase *GfxBase;
struct IntuitionBase *IntuitionBase;


/** The Test Harness *******************************************************/


struct Task *task;

struct Screen *sPacMan;
struct Window *wPacMan;

struct NewScreen nsPacMan = {
	.LeftEdge = 0, .TopEdge = 0,
	.Width = 320, .Height = 200, .Depth = 4,
	.DetailPen = 3, .BlockPen = 0,
	.ViewModes = NULL,
	.Type = CUSTOMSCREEN,
	.Font = NULL,
	.DefaultTitle = "PAC-MAN",
	.Gadgets = NULL
};

struct NewWindow nwPacMan = {
	.LeftEdge = 0, .TopEdge = 0,
	.Width = 320, .Height = 200,
	.DetailPen = 0, .BlockPen = 1,
	.IDCMPFlags = NULL,
	.Flags = BORDERLESS | BACKDROP,
	.FirstGadget = NULL,
	.CheckMark = NULL,
	.Title = "PAC-MAN",
	.Screen = NULL,
	.BitMap = NULL,
	.MinWidth = 320, .MinHeight = 200, .MaxWidth = 320, .MaxHeight = 200,
	.Type = CUSTOMSCREEN
};

struct TextAttr taFont = {
	.ta_Name = "Arcade8.font",
	.ta_YSize = 8,
	.ta_Style = FS_NORMAL,
	.ta_Flags = FPF_DESIGNED
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

struct Image dots[256];

void dots_setup() {
	int i = 0, d = 0;

	for (i = 0; i < sizeof(dotmap); i++) {
		if (dotmap[i] > 0x02)
			continue;

		dots[d].LeftEdge = dot_x[i & 0x1F];
		dots[d].TopEdge = dot_y[i >> 5];
		dots[d].Width = dots[d].Height = 6;
		dots[d].Depth = 1;

		if (dotmap[i] == 0x01) {
			dots[d].ImageData = (unsigned short *) &bmPellet[0];
		} else if (dotmap[i] == 0x02) {
			dots[d].ImageData = (unsigned short *) &bmEnergizer[0];
		}

		dots[d].PlanePick = dots[d].PlaneOnOff = 0x0B;
		dots[d].NextImage = &dots[d + 1];
		d++;
	}

	dots[d - 1].NextImage = NULL;
}

void dot_plot(const int d) {
	const struct Image *img = NULL;

	if (dotmap[d] < 0xFC) {
		switch (dotmap[d]) {
			case 0x01:
				img = &iPellet;
				break;
			case 0x02:
				img = &iEnergizer;
				break;
			default:
				break;
		}
	}

	DrawImage(wPacMan->RPort, img, dot_x[d & 0x1F], dot_y[d >> 5]);
}

void dots_plot() {
	for (int i = 0; i < sizeof(dotmap); i++) {
		dot_plot(i);
	}
}

int main() {
	GfxBase = (struct GfxBase *)
			OpenLibrary("graphics.library", 0);

	if (!GfxBase)
		goto bye;

	IntuitionBase = (struct IntuitionBase *)
			OpenLibrary("intuition.library", 0);

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

	SetRast(wPacMan->RPort, 0);

	dots_setup();

	DrawBorder(wPacMan->RPort, &boMaze, 0, 7);
	DrawImage(wPacMan->RPort, &dots[0], 0, 0);

	Delay(600);

bye:
	RemFont(&Arcade8Font);

	if (wPacMan)
		CloseWindow(wPacMan);

	if (sPacMan)
		CloseScreen(sPacMan);

	if (IntuitionBase)
		CloseLibrary((struct Library *) IntuitionBase);

	if (GfxBase)
		CloseLibrary((struct Library *) GfxBase);
}
