/**
 * @brief   Power Pellet Task
 * @verbose Blink the power pellet register using the timer device.
 * @author  Thomas Cherryhomes
 * @email   thom dot cherryhomes at gmail dot com
 * @license GPL v. 3, see LICENSE for details.
 */

#include <stdio.h>
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
#include <hardware/dmabits.h>
#include <hardware/intbits.h>
#include <intuition/intuition.h>
#include <intuition/screens.h>
#include <proto/intuition.h>

#include "../font.h"
#include "../MazeBorders2.h"

#define SCREEN_HEIGHT 288
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

volatile UWORD __chip my_copper[] = {
    0x8E, 0x2C, // DIWSTRT (Start display at line 44)
    0x90, 0x2C + 288, // DIWSTOP (Stop at line 332)
    0x100, 0x2204, // BPLCON0 (Enable interlace mode)
    0xFFFF, 0xFFFE, // Wait forever
};


struct NewScreen nsPacMan = {
    .LeftEdge = 0, .TopEdge = 0,
    .Width = SCREEN_WIDTH, .Height = SCREEN_HEIGHT, .Depth = 4,
    .DetailPen = 3, .BlockPen = 0,
    .ViewModes = LACE,
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

// USHORT colorTable[16] =
// {
//     0x000, /* 0: Black */
//     0xFF0, /* 1: Yellow */
//     0xF00, /* 2: Light Red */
//     0xFFF, /* 3: White */
//     0x00C, /* 4: Light Blue */
//     0xFBF, /* 5: Light Magenta */
//     0x0FF, /* 6: Light Cyan */
//     0x770, /* 7: Dark Yellow (pale orange?) */
//     0x0F0, /* 8: Light Green */
//     0xFA0, /* 9: Light Orange */
//     0xFEF, /* A: Pinky white */
//     0xFAA, /* B: Power Pellet */
//     0x0FF, /* C: Light Cyan */
//     0xF00, /* D: Light Red */
//     0xF0F, /* E: Light Magenta */
//     0xFFF, /* F: White */
// };

USHORT colorTable[16] =
{
    0x000, /* 0: Black */
    0xFFF, /* 1: Yellow */
    0x00C, /* 2: Light Red */
    0xF00, /* 3: White */
    0x00C, /* 4: Light Blue */
    0xFBF, /* 5: Light Magenta */
    0x0FF, /* 6: Light Cyan */
    0x770, /* 7: Dark Yellow (pale orange?) */
    0x0F0, /* 8: Light Green */
    0xFA0, /* 9: Light Orange */
    0xFEF, /* A: Pinky white */
    0xFAA, /* B: Power Pellet */
    0x0FF, /* C: Light Cyan */
    0xF00, /* D: Light Red */
    0xF0F, /* E: Light Magenta */
    0xFFF, /* F: White */
};

__chip UWORD sprite[] = {
    // Bitplane 0
    0x0000, 0x03C0, 0x0FF0, 0x1FF8,
    0x3FFC, 0x3FFC, 0x0F3C, 0x4F3E,
    0x7FFE, 0x7FFE, 0x7FFE, 0x7FFE,
    0x7FFE, 0x7FFE, 0x6E76, 0x4662,
    // Bitplane 1
    0x0000, 0x03C0, 0x0FF0, 0x1FF8,
    0x279C, 0x030C, 0x33CC, 0x73CE,
    0x679E, 0x7FFE, 0x7FFE, 0x7FFE,
    0x7FFE, 0x7FFE, 0x6E76, 0x4662,
};


// __chip UWORD bmPellet[] =
// {
//     // Bitplane 0
//     0x0000,
//     0x3800,
//     0x7c00,
//     0xfe00,
//     0xfe00,
//     0xfe00,
//     0x7c00,
//     0x3800,
//
//     // Bitplane 1
//     0x0000,
//     0x3800,
//     0x7c00,
//     0xfe00,
//     0xfe00,
//     0xfe00,
//     0x7c00,
//     0x3800,
//
//     // Bitplane 3
//     0x0000,
//     0x3800,
//     0x7c00,
//     0xfe00,
//     0xfe00,
//     0xfe00,
//     0x7c00,
//     0x3800,
// };

struct Image iPellet =
{
    0, 0,
    16, 16, 2,
    sprite,
    0x03, 0x00
};

#define BLINK_R 0xF
#define BLINK_G 0xC
#define BLINK_B 0xB
#define BLINK_COLOR 0x0B

void __amigainterrupt __saveds BlinkPowerPelletInterrupt() {
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
    custom.intreq = INTF_SETCLR | INTF_VERTB; // Properly acknowledge VBL interrupt
}

/* The Test Harness ******************************************************/

int main() {
    printf("Opening graphics lib\n");
    GfxBase = (struct GfxBase *) OpenLibrary("graphics.library", 0);

    if (!GfxBase)
        goto bye;

    printf("Opening intuition\n");
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

    //ActivateWindow(wPacMan);
    UWORD *emptyPointer = AllocMem(22 * sizeof(UWORD), MEMF_CHIP | MEMF_CLEAR);
    SetPointer(wPacMan, emptyPointer, 0, 0, 0, 0);
    SetRast(wPacMan->RPort, 0);

    struct RastPort *rp = &sPacMan->RastPort;

    // Set the drawing pen to a specific color(e.g., 2 = red, 1 = blue, etc.)
    SetAPen(rp, 0xa);

    // RectFill(rp, 0, 0, 28 * TILE_SIZE, 31 * TILE_SIZE);
    //
    // SetAPen(rp, 0x00);
    //
    // for (int x = 0; x < 28; x++) {
    //     for (int y = 0; y < 31; y++) {
    //         RectFill(rp, x * TILE_SIZE + 1, y * TILE_SIZE + 1, x * TILE_SIZE + TILE_SIZE - 1,
    //                  y * TILE_SIZE + TILE_SIZE - 1);
    //     }
    // }

    WaitBOVP(ViewPortAddress(wPacMan));
    DrawMaze(rp);

    DrawImage(rp, &iPellet, 1 * TILE_SIZE + 1, 3 * TILE_SIZE);
    DrawImage(rp, &iPellet, 26 * TILE_SIZE + 1, 3 * TILE_SIZE);
    DrawImage(rp, &iPellet, 1 * TILE_SIZE + 1, 23 * TILE_SIZE);
    DrawImage(rp, &iPellet, 26 * TILE_SIZE + 1, 23 * TILE_SIZE);

    Move(rp, 11 * TILE_SIZE, 18 * TILE_SIZE - 1);
    SetAPen(rp, 0x01);
    Text(rp, "READY!", 6);

    struct Interrupt *vbint = AllocMem(sizeof(struct Interrupt), MEMF_PUBLIC | MEMF_CLEAR);
    if (vbint) {
        vbint->is_Node.ln_Type = NT_INTERRUPT;
        vbint->is_Node.ln_Pri = -60;
        vbint->is_Node.ln_Name = "PowerPelletTask";
        vbint->is_Code = BlinkPowerPelletInterrupt;

        AddIntServer(INTB_VERTB, vbint);
    }

    Delay(300);

    SetAPen(rp, 0x00);
    RectFill(rp, 11 * TILE_SIZE - 2, 17 * TILE_SIZE, 17 * TILE_SIZE + 3, 18 * TILE_SIZE);

    SetAPen(rp, 0x02);
    Move(rp, 9 * TILE_SIZE, 18 * TILE_SIZE - 1);
    Text(rp, "GAME  OVER", 10);

    pauseBlink = FALSE;

    WaitPort(wPacMan->UserPort);
    struct IntuiMessage *msg;
    while ((msg = (struct IntuiMessage *) GetMsg(wPacMan->UserPort)) != NULL) {
        ReplyMsg((struct Message *) msg);
    }

    ClearPointer(wPacMan);
    FreeMem(emptyPointer, 22 * sizeof(UWORD));

bye:
    if (vbint) {
        RemIntServer(INTB_VERTB, vbint);
        FreeMem(vbint, sizeof(struct Interrupt));
    }

    if (task)
        DeleteTask(task);

    RemFont(&Arcade8Font);

    if (wPacMan) {
        CloseWindow(wPacMan);
    }

    if (sPacMan)
        CloseScreen(sPacMan);

    if (IntuitionBase)
        CloseLibrary((struct Library *) IntuitionBase);

    if (GfxBase)
        CloseLibrary((struct Library *) GfxBase);
}
