/**
 * @brief   Draw Maze and place PacMan Sprite
 * @verbose Draw the Maze into window specified and place PacMan Sprite
 * @author  Thomas Cherryhomes
 * @email   thom dot cherryhomes at gmail dot com
 * @license GPL v. 3, see LICENSE for details.
 */

#include <clib/alib_protos.h>
#include <clib/dos_protos.h>
#include <clib/exec_protos.h>
#include <clib/graphics_protos.h>
#include <clib/intuition_protos.h>
#include <exec/types.h>
#include <exec/exec.h>
#include <graphics/gfx.h>
#include <graphics/gfxbase.h>
#include <graphics/sprite.h>
#include <intuition/intuition.h>

#include "../font.h"

struct GfxBase *GfxBase;
struct IntuitionBase *IntuitionBase;

/** The Test Harness *******************************************************/


struct Screen *sPacMan;
struct Window *wPacMan;

struct NewScreen nsPacMan =
{
	0, 0,
	320, 200, 4,
	3, 0, /* 0, 1 */
	SPRITES,
	CUSTOMSCREEN,
	NULL,
	"PAC-MAN(tm)",
	NULL
};

struct NewWindow nwPacMan =
{
	0, 0,
	320, 200,
	0, 1,
	NULL,
	BORDERLESS | BACKDROP,
	NULL,
	NULL,
	"PAC-MAN(tm)",
	NULL,
	NULL,
	320, 200, 320, 200,
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
	0x0F0, /* B: Light Green */
	0x0FF, /* C: Light Cyan */
	0xF00, /* D: Light Red */
	0xF0F, /* E: Light Magenta */
	0xFFF, /* F: White */
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

struct SimpleSprite pacSprite =
{
	pacman_right_0,
	16,
	64, 64,
	1
};

/* Maze data here */
SHORT m1[] =
{
	13, 7, 16, 4,
	16, 4, 177, 4,
	177, 4, 180, 7,
	180, 7, 180, 60,
	180, 60, 177, 63,
	177, 63, 151, 63,
	151, 63, 150, 64,
	150, 64, 150, 81,
	150, 81, 151, 82,
	151, 82, 180, 82,
	180, 84, 150, 84,
	150, 84, 148, 82,
	148, 82, 148, 63,
	148, 63, 150, 61,
	150, 61, 176, 61,
	176, 61, 178, 59,
	178, 59, 178, 8,
	178, 8, 176, 6,
	176, 6, 101, 6,
	101, 6, 99, 8,
	99, 8, 99, 28,
	99, 28, 97, 30,
	97, 30, 96, 30,
	96, 30, 94, 28,
	94, 28, 94, 8,
	94, 8, 92, 6,
	92, 6, 17, 6,
	17, 6, 15, 8,
	15, 8, 15, 59,
	15, 59, 17, 61,
	17, 61, 43, 61,
	43, 61, 45, 63,
	45, 63, 45, 82,
	45, 82, 43, 84,
	43, 84, 13, 84,
	13, 82, 42, 82,
	42, 82, 43, 81,
	43, 81, 43, 64,
	43, 64, 42, 63,
	42, 63, 16, 63,
	16, 63, 13, 60,
	13, 60, 13, 7
};

USHORT m11[] =
{
	13, 97, 43, 97,
	43, 97, 45, 99,
	45, 99, 45, 117,
	45, 117, 43, 119,
	43, 119, 17, 119,
	17, 119, 15, 121,
	15, 121, 15, 150,
	15, 150, 17, 152,
	17, 152, 25, 152,
	25, 152, 27, 154,
	27, 154, 27, 155,
	27, 155, 25, 157,
	25, 157, 17, 157,
	17, 157, 15, 159,
	15, 159, 15, 185,
	15, 185, 17, 187,
	17, 187, 176, 187,
	176, 187, 178, 185,
	178, 185, 178, 159,
	178, 159, 176, 157,
	176, 157, 168, 157,
	168, 157, 166, 155,
	166, 155, 166, 154,
	166, 154, 168, 152,
	168, 152, 176, 152,
	176, 152, 178, 150,
	178, 150, 178, 121,
	178, 121, 176, 119,
	176, 119, 150, 119,
	150, 119, 148, 117,
	148, 117, 148, 99,
	148, 99, 150, 97,
	150, 97, 180, 97
};

SHORT m12[] =
{
	13, 99, 42, 99,
	42, 99, 43, 100,
	43, 100, 43, 116,
	43, 116, 42, 117,
	42, 117, 16, 117,
	16, 117, 13, 120,
	13, 120, 13, 186,
	13, 186, 16, 189,
	16, 189, 177, 189,
	177, 189, 180, 186,
	180, 186, 180, 120,
	180, 120, 177, 117,
	177, 117, 151, 117,
	151, 117, 150, 116,
	150, 116, 150, 100,
	150, 100, 151, 99,
	151, 99, 180, 99
};

SHORT f1[] =
{
	30, 19, 43, 19,
	43, 19, 45, 21,
	45, 21, 45, 28,
	45, 28, 43, 30,
	43, 30, 30, 30,
	30, 30, 28, 28,
	28, 28, 28, 21,
	28, 21, 30, 19
};

SHORT f2[] =
{
	60, 19, 78, 19,
	78, 19, 80, 21,
	80, 21, 80, 28,
	80, 28, 78, 30,
	78, 30, 60, 30,
	60, 30, 58, 28,
	58, 28, 58, 21,
	58, 21, 60, 19
};

SHORT f3[] =
{
	115, 19, 133, 19,
	133, 19, 135, 21,
	135, 21, 135, 28,
	135, 28, 133, 30,
	133, 30, 115, 30,
	115, 30, 113, 28,
	113, 28, 113, 21,
	113, 21, 115, 19
};

SHORT f4[] =
{
	150, 19, 163, 19,
	163, 19, 165, 21,
	165, 21, 165, 28,
	165, 28, 163, 30,
	163, 30, 150, 30,
	150, 30, 148, 28,
	148, 28, 148, 21,
	148, 21, 150, 19
};

SHORT f5[] =
{
	30, 42, 43, 42,
	43, 42, 45, 44,
	45, 44, 45, 45,
	45, 45, 43, 47,
	43, 47, 30, 47,
	30, 47, 28, 45,
	28, 45, 28, 44,
	28, 44, 30, 42
};

SHORT f6[] =
{
	60, 42, 61, 42,
	61, 42, 63, 44,
	63, 44, 63, 59,
	63, 59, 65, 61,
	65, 61, 78, 61,
	78, 61, 80, 63,
	80, 63, 80, 64,
	80, 64, 78, 66,
	78, 66, 65, 66,
	65, 66, 63, 68,
	63, 68, 63, 82,
	63, 82, 61, 84,
	61, 84, 60, 84,
	60, 84, 58, 82,
	58, 82, 58, 44,
	58, 44, 60, 42
};

SHORT f7[] =
{
	78, 42, 115, 42,
	115, 42, 117, 44,
	117, 44, 117, 45,
	117, 45, 115, 47,
	115, 47, 101, 47,
	101, 47, 99, 49,
	99, 49, 99, 64,
	99, 64, 97, 66,
	97, 66, 96, 66,
	96, 66, 94, 64,
	94, 64, 94, 49,
	94, 49, 92, 47,
	92, 47, 78, 47,
	78, 47, 76, 45,
	76, 45, 76, 44,
	76, 44, 78, 42
};

SHORT f8[] =
{
	132, 42, 133, 42,
	133, 42, 135, 44,
	135, 44, 135, 82,
	135, 82, 133, 84,
	133, 84, 132, 84,
	132, 84, 130, 82,
	130, 82, 130, 68,
	130, 68, 128, 66,
	128, 66, 115, 66,
	115, 66, 113, 64,
	113, 64, 115, 61,
	115, 61, 128, 61,
	128, 61, 130, 59,
	130, 59, 130, 44,
	130, 44, 132, 42 /* BUG */
};

SHORT f9[] =
{
	150, 42, 163, 42,
	163, 42, 165, 44,
	165, 44, 165, 45,
	165, 45, 163, 47,
	163, 47, 150, 47,
	150, 47, 148, 45,
	148, 45, 148, 44,
	148, 44, 150, 42
};

SHORT f10[] =
{
	104, 80, 117, 80,
	117, 80, 117, 102,
	117, 102, 76, 102,
	76, 102, 76, 80,
	76, 80, 89, 80,
	89, 80, 89, 82,
	89, 82, 78, 82,
	78, 82, 78, 100,
	78, 100, 115, 100,
	115, 100, 115, 82,
	115, 82, 104, 82,
	104, 82, 104, 80
};

SHORT f11[] =
{
	60, 97, 61, 97,
	61, 97, 63, 99,
	63, 99, 63, 117,
	63, 117, 61, 119,
	61, 119, 60, 119,
	60, 119, 58, 117,
	58, 117, 58, 99,
	58, 99, 60, 97
};

SHORT f12[] =
{
	78, 114, 115, 114,
	115, 114, 117, 116,
	117, 116, 117, 117,
	117, 117, 115, 119,
	101, 119, 99, 121,
	99, 121, 99, 136,
	99, 136, 97, 138,
	97, 138, 96, 138,
	96, 138, 94, 136,
	94, 136, 94, 121,
	94, 121, 92, 119,
	92, 119, 78, 119,
	78, 119, 76, 117,
	76, 117, 76, 116,
	76, 116, 78, 114
};

SHORT f13[] =
{
	132, 97, 133, 97,
	133, 97, 135, 99,
	135, 99, 135, 117,
	135, 117, 133, 119,
	133, 119, 132, 119,
	132, 119, 130, 117,
	130, 117, 130, 99,
	130, 99, 132, 97
};

SHORT f14[] =
{
	30, 133, 44, 133,
	44, 133, 46, 135,
	46, 135, 46, 155,
	46, 155, 44, 157,
	44, 157, 43, 157,
	43, 157, 41, 155,
	41, 155, 41, 140,
	41, 140, 39, 138,
	39, 138, 30, 138,
	30, 138, 28, 136,
	28, 136, 28, 135,
	28, 135, 30, 133
};

SHORT f15[] =
{
	60, 133, 78, 133,
	78, 133, 80, 135,
	80, 135, 80, 136,
	80, 136, 78, 138,
	78, 138, 60, 138,
	60, 138, 58, 136,
	58, 136, 58, 135,
	58, 135, 60, 133
};

SHORT f16[] =
{
	115, 133, 133, 133,
	133, 133, 135, 135,
	135, 135, 135, 136,
	135, 136, 133, 138,
	133, 138, 115, 138,
	115, 138, 113, 136,
	113, 136, 113, 135,
	113, 135, 115, 133
};

SHORT f17[] =
{
	149, 133, 163, 133,
	163, 133, 165, 135,
	165, 135, 165, 136,
	165, 136, 163, 138,
	163, 138, 154, 138,
	154, 138, 152, 140,
	152, 140, 152, 154,
	152, 154, 150, 156,
	150, 156, 149, 156,
	149, 156, 147, 154,
	147, 154, 147, 135,
	147, 135, 149, 133
};

SHORT f18[] =
{
	30, 169, 56, 169,
	56, 169, 58, 167,
	58, 167, 58, 154,
	58, 154, 60, 152,
	60, 152, 61, 152,
	61, 152, 63, 154,
	63, 154, 63, 167,
	63, 167, 65, 169,
	65, 169, 78, 169,
	78, 169, 80, 171,
	80, 171, 80, 172,
	80, 172, 78, 174,
	78, 174, 30, 174,
	30, 174, 28, 172,
	28, 172, 28, 171,
	28, 171, 30, 169
};

short f19[] =
{
	78, 152, 115, 152,
	115, 152, 117, 154,
	117, 154, 117, 155,
	117, 155, 115, 157,
	115, 157, 101, 157,
	101, 157, 99, 159,
	99, 159, 99, 172,
	99, 172, 97, 174,
	97, 174, 96, 174,
	96, 174, 94, 172,
	94, 172, 94, 159,
	94, 159, 92, 157,
	92, 157, 78, 157,
	78, 157, 76, 155,
	76, 155, 76, 154,
	76, 154, 78, 152
};

SHORT f20[] =
{
	132, 152, 133, 152,
	133, 152, 135, 154,
	135, 154, 135, 167,
	135, 167, 137, 169,
	137, 169, 163, 169,
	163, 169, 165, 171,
	165, 171, 165, 172,
	165, 172, 163, 174,
	163, 174, 115, 174,
	115, 174, 113, 172,
	113, 172, 113, 171,
	113, 171, 115, 169,
	115, 169, 128, 169,
	128, 169, 130, 167,
	130, 167, 130, 154,
	130, 154, 132, 152
};

struct Border boF20 =
{
	0, 0,
	4,
	4,
	JAM1,
	32,
	f20,
	NULL
};

struct Border boF19 =
{
	0, 0,
	4,
	4,
	JAM1,
	32,
	f19,
	&boF20
};

struct Border boF18 =
{
	0, 0,
	4,
	4,
	JAM1,
	32,
	f18,
	&boF19
};

struct Border boF17 =
{
	0, 0,
	4,
	4,
	JAM1,
	24,
	f17,
	&boF18
};

struct Border boF16 =
{
	0, 0,
	4,
	4,
	JAM1,
	16,
	f16,
	&boF17
};

struct Border boF15 =
{
	0, 0,
	4,
	4,
	JAM1,
	16,
	f15,
	&boF16
};

struct Border boF14 =
{
	0, 0,
	4,
	4,
	JAM1,
	24,
	f14,
	&boF15
};

struct Border boF13 =
{
	0, 0,
	4,
	4,
	JAM1,
	16,
	f13,
	&boF14
};

struct Border boF12 =
{
	0, 0,
	4,
	4,
	JAM1,
	30,
	f12,
	&boF13
};

struct Border boF11 = /* BUG */
{
	0, 0,
	4,
	4,
	JAM1,
	16,
	f11,
	&boF12
};

struct Border boF10 =
{
	0, 0,
	4,
	4,
	JAM1,
	24,
	f10,
	&boF11,
};

struct Border boF9 =
{
	0, 0,
	4,
	4,
	JAM1,
	16,
	f9,
	&boF10
};

struct Border boF8 = /* BUG */
{
	0, 0,
	4,
	4,
	JAM1,
	30, /* 30 */
	f8,
	&boF9
};

struct Border boF7 =
{
	0, 0,
	4,
	4,
	JAM1,
	32,
	f7,
	&boF8
};

struct Border boF6 =
{
	0, 0,
	4,
	4,
	JAM1,
	32,
	f6,
	&boF7
};

struct Border boF5 =
{
	0, 0,
	4,
	4,
	JAM1,
	16,
	f5,
	&boF6
};

struct Border boF4 =
{
	0, 0,
	4,
	4,
	JAM1,
	16,
	f4,
	&boF5
};

struct Border boF3 =
{
	0, 0,
	4,
	4,
	JAM1,
	16,
	f3,
	&boF4
};

struct Border boF2 =
{
	0, 0,
	4,
	4,
	JAM1,
	16,
	f2,
	&boF3
};

struct Border boF1 =
{
	0, 0,
	4,
	4,
	JAM1,
	16,
	f1,
	&boF2
};

/* How many points can a border have? A: 127. */

struct Border boMaze2 =
{
	0, 0,
	4,
	4,
	JAM1,
	34,
	m12,
	&boF1
};

struct Border boMaze1 =
{
	0, 0,
	4,
	4,
	JAM1,
	66, /* 102 */
	m11,
	&boMaze2
};

struct Border boMaze =
{
	0, 0,
	4, /* frontpen */
	4, /* backpen */
	JAM1,
	84, /* Number of (X,Y) coordinate pairs */
	m1, /* pointer to coordinates */
	&boMaze1, /* NextBorder boMaze2 */
};

struct IntuiText my_body_text2 =
{
	0,
	0,
	JAM1,
	27,
	15,
	NULL,
	"(C) 1986 NAMCO",
	NULL
};

struct IntuiText my_body_text =
{
	0,
	0,
	JAM1,
	15,
	5,
	NULL,
	"PAC-MAN(TM)",
	&my_body_text2
};

struct IntuiText button_text =
{
	0,
	0,
	JAM1,
	6,
	3,
	NULL,
	"OK",
	NULL
};

char reqTitle[] = "ABOUT";

void about() {
	AutoRequest(wPacMan,
	            &my_body_text,
	            NULL,
	            &button_text,
	            NULL,
	            NULL,
	            320, 88);
}

int main() {
	int spr = 0;

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

	DrawBorder(wPacMan->RPort, &boMaze, 0, 7);

	spr = GetSprite(&pacSprite, -1);
	const int k = (spr & 0x06) * 2 + 16;
	ChangeSprite(&sPacMan->ViewPort, &pacSprite, (UWORD *) &pacman_right_0);
	MoveSprite(&sPacMan->ViewPort, &pacSprite, 96, 145);
	WaitTOF();

	SetRGB4(&sPacMan->ViewPort, k + 1, 0x0f, 0x0f, 0x00);

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
