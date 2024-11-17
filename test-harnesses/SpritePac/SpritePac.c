/**
 * @brief   Animate PAC-MAN sprite
 * @verbose Using the GELs system
 * @author  Thomas Cherryhomes
 * @email   thom dot cherryhomes at gmail dot com
 * @license GPL v. 3, see LICENSE for details.
 */

#include <clib/alib_protos.h>
#include <clib/intuition_protos.h>
#include <clib/dos_protos.h>
#include <clib/graphics_protos.h>
#include <clib/exec_protos.h>
#include <exec/types.h>
#include <exec/exec.h>
#include <graphics/gfx.h>
#include <graphics/gfxbase.h>
#include <graphics/sprite.h>
#include <intuition/intuition.h>

#include "../font.h"
#include "../Colors.h"

struct GfxBase *GfxBase;
struct IntuitionBase *IntuitionBase;
struct Screen *sPacMan;
struct Window *wPacMan;

struct NewScreen nsPacMan = {
	.LeftEdge = 0, .TopEdge = 0,
	.Width = 320, .Height = 200, .Depth = 4,
	.DetailPen = 0, .BlockPen = 1,
	.ViewModes = SPRITES,
	.Type = CUSTOMSCREEN,
	.Font = NULL,
	.DefaultTitle = "PACMAN",
	.Gadgets = NULL
};

struct NewWindow nwPacMan = {
	.LeftEdge = 0, .TopEdge = 0,
	.Width = 320, .Height = 200,
	.DetailPen = 0, .BlockPen = 1,
	.IDCMPFlags = NULL,
	.Flags = ACTIVATE | BORDERLESS | BACKDROP,
	.FirstGadget = NULL,
	.CheckMark = NULL,
	.Title = "PACMAN",
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

USHORT colorTable[] =
{
	BLACK,
	YELLOW,
	LIGHT_RED,
	WHITE,
	LIGHT_BLUE,
	LIGHT_MAGENTA,
	LIGHT_CYAN,
	DARK_YELLOW,
	LIGHT_GREEN,
	LIGHT_ORANGE,
	PINKY_WHITE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	WHITE
};

/**
 * Sprite bitmaps
 */
UWORD pacman_right_0[] =
{
	0, 0,
	0x0000, 0x0000, /* 0000000000000000 */
	0x07C0, 0x0000, /* 0000011111000000 */
	0x1FC0, 0x0000, /* 0001111111000000 */
	0x3F80, 0x0000, /* 0011111110000000 */
	0x3F00, 0x0000, /* 0011111100000000 */
	0x7E00, 0x0000, /* 0111111000000000 */
	0x7C00, 0x0000, /* 0111110000000000 */
	0x7800, 0x0000, /* 0111100000000000 */
	0x7C00, 0x0000, /* 0111110000000000 */
	0x7E00, 0x0000, /* 0111111000000000 */
	0x3F00, 0x0000, /* 0011111100000000 */
	0x3F80, 0x0000, /* 0011111110000000 */
	0x1FC0, 0x0000, /* 0001111111000000 */
	0x07C0, 0x0000, /* 0000011111000000 */
	0x0000, 0x0000, /* 0000000000000000 */
	0x0000, 0x0000, /* 0000000000000000 */
	0, 0
};

UWORD pacman_right_1[] =
{
	0, 0,
	0x0000, 0x0000, /* 0000000000000000 */
	0x07C0, 0x0000, /* 0000011111000000 */
	0x1FF0, 0x0000, /* 0001111111110000 */
	0x3FF8, 0x0000, /* 0011111111111000 */
	0x3FF8, 0x0000, /* 0011111111111000 */
	0x7FE0, 0x0000, /* 0111111111100000 */
	0x7F00, 0x0000, /* 0111111100000000 */
	0x7800, 0x0000, /* 0111100000000000 */
	0x7F00, 0x0000, /* 0111111100000000 */
	0x7FE0, 0x0000, /* 0111111111100000 */
	0x3FF8, 0x0000, /* 0011111111111000 */
	0x3FF8, 0x0000, /* 0011111111111000 */
	0x1FF0, 0x0000, /* 0001111111110000 */
	0x07C0, 0x0000, /* 0000011111000000 */
	0x0000, 0x0000, /* 0000000000000000 */
	0x0000, 0x0000, /* 0000000000000000 */
	0, 0
};

UWORD pacman_right_2[] =
{
	0, 0,
	0x0000, 0x0000, /* 0000000000000000 */
	0x07C0, 0x0000, /* 0000011111000000 */
	0x1FF0, 0x0000, /* 0001111111110000 */
	0x3FF8, 0x0000, /* 0011111111111000 */
	0x3FF8, 0x0000, /* 0011111111111000 */
	0x7FFC, 0x0000, /* 0111111111111100 */
	0x7FFC, 0x0000, /* 0111111111111100 */
	0x7FFC, 0x0000, /* 0111111111111100 */
	0x7FFC, 0x0000, /* 0111111111111100 */
	0x7FFC, 0x0000, /* 0111111111111100 */
	0x3FF8, 0x0000, /* 0011111111111000 */
	0x3FF8, 0x0000, /* 0011111111111000 */
	0x1FF0, 0x0000, /* 0001111111110000 */
	0x07C0, 0x0000, /* 0000011111000000 */
	0x0000, 0x0000, /* 0000000000000000 */
	0x0000, 0x0000, /* 0000000000000000 */
	0, 0,
};
struct SimpleSprite pacSprite =
{
	pacman_right_0,
	16,
	64, 64,
	1
};

/**
 * The test harness, display PAC-MAN chomping his mouth, facing right.
 */
int main() {
	SHORT spr = 0;

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

	spr = GetSprite(&pacSprite, -1);
	if (spr < 0) goto bye;
	const SHORT k = (spr & 0x06) * 2 + 16;

	SetRGB4(&sPacMan->ViewPort, k + 1, 0x0F, 0x0F, 0x00);
	SetRGB4(&sPacMan->ViewPort, k + 2, 0x0F, 0x0F, 0x00);
	SetRGB4(&sPacMan->ViewPort, k + 3, 0x0F, 0x0F, 0x00);
	SetRGB4(&sPacMan->ViewPort, k + 4, 0x0F, 0x0F, 0x00);

	/* Set initial X position */
	SHORT x = 0;

	for (SHORT i = 0; i < 128; i++) {
		ChangeSprite(&sPacMan->ViewPort, &pacSprite, (UWORD *) &pacman_right_0);
		MoveSprite(&sPacMan->ViewPort, &pacSprite, x++, 100);
		WaitTOF();
		ChangeSprite(&sPacMan->ViewPort, &pacSprite, (UWORD *) &pacman_right_1);
		MoveSprite(&sPacMan->ViewPort, &pacSprite, x++, 100);
		WaitTOF();
		ChangeSprite(&sPacMan->ViewPort, &pacSprite, (UWORD *) &pacman_right_2);
		MoveSprite(&sPacMan->ViewPort, &pacSprite, x++, 100);
		WaitTOF();
	}

	MoveSprite(&sPacMan->ViewPort, &pacSprite, 64, 100);

	//TimeDelay(UNIT_VBLANK, 10, 0);
	Delay(600);

bye:
	if (spr > 0)
		FreeSprite(spr);

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
