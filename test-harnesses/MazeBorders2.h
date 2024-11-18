//
// Created by Barry Walker on 11/16/24.
//

#ifndef MAZEBORDERS2_H
#define MAZEBORDERS2_H

#define TILE_SIZE   7
#define MAZE_TILES_WIDTH  28 // Maze width in tiles
#define MAZE_TILES_HEIGHT 31 // Maze height in tiles
#define MAZE_WIDTH  (MAZE_TILES_WIDTH * TILE_SIZE) // Maze width in pixels
#define MAZE_HEIGHT (MAZE_TILES_HEIGHT * TILE_SIZE) // Maze height in pixels

#include <graphics/rastport.h>

typedef struct {
    int x1, y1; // Start point
    int x2, y2; // End point
} Line;

Line leftSideLines[] = {
    // Outer line
    {0, 13 * TILE_SIZE, 4 * TILE_SIZE - 1, 13 * TILE_SIZE},
    {4 * TILE_SIZE, 13 * TILE_SIZE - 1, 4 * TILE_SIZE, 10 * TILE_SIZE + 1},
    {4 * TILE_SIZE - 1, 10 * TILE_SIZE, 0 * TILE_SIZE + 4, 10 * TILE_SIZE},
    {0 * TILE_SIZE + 3, 10 * TILE_SIZE - 1, 0 * TILE_SIZE + 2, 10 * TILE_SIZE - 1},
    {0 * TILE_SIZE + 1, 10 * TILE_SIZE - 3, 0 * TILE_SIZE + 1, 10 * TILE_SIZE - 2},
    {0 * TILE_SIZE, 10 * TILE_SIZE - 4, 0 * TILE_SIZE, 0 * TILE_SIZE + 4},
    {0 * TILE_SIZE + 1, 0 * TILE_SIZE + 3, 0 * TILE_SIZE + 1, 0 * TILE_SIZE + 2},
    {0 * TILE_SIZE + 2, 0 * TILE_SIZE + 1, 0 * TILE_SIZE + 3, 0 * TILE_SIZE + 1},
    {0 * TILE_SIZE + 4, 0 * TILE_SIZE, 14 * TILE_SIZE, 0 * TILE_SIZE},
    {0 * TILE_SIZE, 16 * TILE_SIZE, 4 * TILE_SIZE - 1, 16 * TILE_SIZE},
    {4 * TILE_SIZE, 16 * TILE_SIZE + 1, 4 * TILE_SIZE, 19 * TILE_SIZE - 1},
    {4 * TILE_SIZE - 1, 19 * TILE_SIZE, 0 * TILE_SIZE + 4, 19 * TILE_SIZE},
    {0 * TILE_SIZE + 2, 19 * TILE_SIZE + 1, 0 * TILE_SIZE + 3, 19 * TILE_SIZE + 1},
    {0 * TILE_SIZE + 1, 19 * TILE_SIZE + 2, 0 * TILE_SIZE + 1, 19 * TILE_SIZE + 3},
    {0 * TILE_SIZE, 19 * TILE_SIZE + 4, 0 * TILE_SIZE, 30 * TILE_SIZE + 3},
    {0 * TILE_SIZE + 1, 30 * TILE_SIZE + 4, 0 * TILE_SIZE + 1, 30 * TILE_SIZE + 5},
    {0 * TILE_SIZE + 2, 30 * TILE_SIZE + 6, 0 * TILE_SIZE + 3, 30 * TILE_SIZE + 6},
    {0 * TILE_SIZE + 4, 31 * TILE_SIZE, 14 * TILE_SIZE, 31 * TILE_SIZE},

    // Inner line
    {0, 13 * TILE_SIZE + 3, 4 * TILE_SIZE + 1, 13 * TILE_SIZE + 3},
    {4 * TILE_SIZE + 2, 13 * TILE_SIZE + 2, 4 * TILE_SIZE + 2, 13 * TILE_SIZE + 2},
    {4 * TILE_SIZE + 3, 13 * TILE_SIZE + 1, 4 * TILE_SIZE + 3, 10 * TILE_SIZE - 1},
    {4 * TILE_SIZE + 2, 10 * TILE_SIZE - 2, 4 * TILE_SIZE + 2, 10 * TILE_SIZE - 2},
    {4 * TILE_SIZE + 1, 10 * TILE_SIZE - 3, 0 * TILE_SIZE + 5, 10 * TILE_SIZE - 3},
    {0 * TILE_SIZE + 4, 10 * TILE_SIZE - 4, 0 * TILE_SIZE + 4, 10 * TILE_SIZE - 4},
    {0 * TILE_SIZE + 3, 10 * TILE_SIZE - 5, 0 * TILE_SIZE + 3, 0 * TILE_SIZE + 5},
    {0 * TILE_SIZE + 4, 0 * TILE_SIZE + 4, 0 * TILE_SIZE + 4, 0 * TILE_SIZE + 4},
    {0 * TILE_SIZE + 5, 0 * TILE_SIZE + 3, 14 * TILE_SIZE, 0 * TILE_SIZE + 3},
    {0 * TILE_SIZE, 16 * TILE_SIZE - 3, 4 * TILE_SIZE + 1, 16 * TILE_SIZE - 3},
    {4 * TILE_SIZE + 2, 16 * TILE_SIZE - 2, 4 * TILE_SIZE + 2, 16 * TILE_SIZE - 2},
    {4 * TILE_SIZE + 3, 16 * TILE_SIZE - 1, 4 * TILE_SIZE + 3, 19 * TILE_SIZE + 1},
    {4 * TILE_SIZE + 2, 19 * TILE_SIZE + 2, 4 * TILE_SIZE + 2, 19 * TILE_SIZE + 2},
    {4 * TILE_SIZE + 1, 19 * TILE_SIZE + 3, 0 * TILE_SIZE + 5, 19 * TILE_SIZE + 3},
    {0 * TILE_SIZE + 4, 19 * TILE_SIZE + 4, 0 * TILE_SIZE + 4, 19 * TILE_SIZE + 4},
    {0 * TILE_SIZE + 3, 19 * TILE_SIZE + 5, 0 * TILE_SIZE + 3, 24 * TILE_SIZE + 2},
    {0 * TILE_SIZE + 4, 24 * TILE_SIZE + 3, 0 * TILE_SIZE + 4, 24 * TILE_SIZE + 3},
    {0 * TILE_SIZE + 5, 24 * TILE_SIZE + 4, 2 * TILE_SIZE + 1, 24 * TILE_SIZE + 4},
    {2 * TILE_SIZE + 2, 24 * TILE_SIZE + 5, 2 * TILE_SIZE + 2, 24 * TILE_SIZE + 5},
    {2 * TILE_SIZE + 3, 24 * TILE_SIZE + 6, 2 * TILE_SIZE + 3, 24 * TILE_SIZE + 8},
    {2 * TILE_SIZE + 2, 24 * TILE_SIZE + 9, 2 * TILE_SIZE + 2, 24 * TILE_SIZE + 9},
    {2 * TILE_SIZE + 1, 25 * TILE_SIZE + 3, 0 * TILE_SIZE + 5, 25 * TILE_SIZE + 3},
    {0 * TILE_SIZE + 4, 25 * TILE_SIZE + 4, 0 * TILE_SIZE + 4, 25 * TILE_SIZE + 4},
    {0 * TILE_SIZE + 3, 25 * TILE_SIZE + 5, 0 * TILE_SIZE + 3, 30 * TILE_SIZE + 2},
    {0 * TILE_SIZE + 4, 30 * TILE_SIZE + 3, 0 * TILE_SIZE + 4, 30 * TILE_SIZE + 3},
    {0 * TILE_SIZE + 5, 30 * TILE_SIZE + 4, 14 * TILE_SIZE, 30 * TILE_SIZE + 4},
};

int numLeftLines = sizeof(leftSideLines) / sizeof(Line);

inline void mirrorLines(const Line *leftLines, const int count, Line *mirroredLines) {
    const int centerX = MAZE_WIDTH / 2; // Axis of symmetry in pixels (center of the maze)
    for (int i = 0; i < count; i++) {
        mirroredLines[i].x1 = centerX + (centerX - leftLines[i].x1);
        mirroredLines[i].y1 = leftLines[i].y1;
        mirroredLines[i].x2 = centerX + (centerX - leftLines[i].x2);
        mirroredLines[i].y2 = leftLines[i].y2;
    }
}

// Function to generate all maze lines
inline void generateMazeLines(Line *combinedLines, int *totalLines) {
    // Copy original left-side lines
    for (int i = 0; i < numLeftLines; i++) {
        combinedLines[i] = leftSideLines[i];
    }

    // Add mirrored lines
    Line mirroredLines[numLeftLines];
    mirrorLines(leftSideLines, numLeftLines, mirroredLines);

    for (int i = 0; i < numLeftLines; i++) {
        combinedLines[numLeftLines + i] = mirroredLines[i];
    }

    *totalLines = 2 * numLeftLines;
}

// Draw the maze on the RastPort
inline void DrawMaze(struct RastPort *rp) {
    Line combinedLines[2 * numLeftLines];
    int totalLines;

    // Generate full maze lines
    generateMazeLines(combinedLines, &totalLines);

    // Draw the lines
    SetAPen(rp, 0x04); // Maze color
    for (int i = 0; i < totalLines; i++) {
        Move(rp, combinedLines[i].x1, combinedLines[i].y1);
        Draw(rp, combinedLines[i].x2, combinedLines[i].y2);
    }
}

#endif //MAZEBORDERS2_H
