//
// Created by Barry Walker on 11/16/24.
//

#ifndef MAZEBORDERS2_H
#define MAZEBORDERS2_H

#define TILE_SIZE   8
#define MAZE_TILES_WIDTH  28 // Maze width in tiles
#define MAZE_TILES_HEIGHT 31 // Maze height in tiles
#define MAZE_WIDTH  (MAZE_TILES_WIDTH * TILE_SIZE) // Maze width in pixels
#define MAZE_HEIGHT (MAZE_TILES_HEIGHT * TILE_SIZE) // Maze height in pixels

#include <graphics/rastport.h>

typedef struct {
    int x1, y1; // Start point
    int x2, y2; // End point
} Line;

typedef struct {
    Point ul;
    Point lr;
} Oval;

Point halfT[] = {
    {14 * TILE_SIZE, 6 * TILE_SIZE + 4},
    {14 * TILE_SIZE, 18 * TILE_SIZE + 4},
    {14 * TILE_SIZE, 24 * TILE_SIZE + 4},
};

Oval ovals[] = {
    {{2 * TILE_SIZE + 4, 2 * TILE_SIZE + 4}, {5 * TILE_SIZE + 4, 4 * TILE_SIZE + 4}},
    {{7 * TILE_SIZE + 4, 2 * TILE_SIZE + 4}, {11 * TILE_SIZE + 4, 4 * TILE_SIZE + 4}},
    {{2 * TILE_SIZE + 4, 6 * TILE_SIZE + 4}, {5 * TILE_SIZE + 4, 7 * TILE_SIZE + 4}},
    {{7 * TILE_SIZE + 4, 15 * TILE_SIZE + 4}, {8 * TILE_SIZE + 4, 19 * TILE_SIZE + 4}},
    {{7 * TILE_SIZE + 4, 21 * TILE_SIZE + 4}, {11 * TILE_SIZE + 4, 22 * TILE_SIZE + 4}},
};

Line leftSideLines[] = {
    // Ghost House
    {11 * TILE_SIZE, 13 * TILE_SIZE, 13 * TILE_SIZE, 13 * TILE_SIZE},
    {13 * TILE_SIZE, 13 * TILE_SIZE, 13 * TILE_SIZE, 13 * TILE_SIZE - 4},
    {13 * TILE_SIZE, 13 * TILE_SIZE - 4, 11 * TILE_SIZE - 4, 13 * TILE_SIZE - 4},
    {11 * TILE_SIZE - 4, 13 * TILE_SIZE - 4, 11 * TILE_SIZE - 4, 16 * TILE_SIZE + 4},
    {11 * TILE_SIZE - 4, 16 * TILE_SIZE + 4, 14 * TILE_SIZE, 16 * TILE_SIZE + 4},
    {11 * TILE_SIZE, 13 * TILE_SIZE, 11 * TILE_SIZE, 16 * TILE_SIZE},
    {11 * TILE_SIZE, 16 * TILE_SIZE, 14 * TILE_SIZE, 16 * TILE_SIZE},

    // Outer line
    {0, 13 * TILE_SIZE, 5 * TILE_SIZE - 1, 13 * TILE_SIZE},
    {5 * TILE_SIZE, 13 * TILE_SIZE - 1, 5 * TILE_SIZE, 10 * TILE_SIZE + 1},
    {5 * TILE_SIZE - 1, 10 * TILE_SIZE, 0 * TILE_SIZE + 4, 10 * TILE_SIZE},
    {0 * TILE_SIZE + 3, 10 * TILE_SIZE - 1, 0 * TILE_SIZE + 2, 10 * TILE_SIZE - 1},
    {0 * TILE_SIZE + 1, 10 * TILE_SIZE - 3, 0 * TILE_SIZE + 1, 10 * TILE_SIZE - 2},
    {0 * TILE_SIZE, 10 * TILE_SIZE - 4, 0 * TILE_SIZE, 0 * TILE_SIZE + 4},
    {0 * TILE_SIZE + 1, 0 * TILE_SIZE + 3, 0 * TILE_SIZE + 1, 0 * TILE_SIZE + 2},
    {0 * TILE_SIZE + 2, 0 * TILE_SIZE + 1, 0 * TILE_SIZE + 3, 0 * TILE_SIZE + 1},
    {0 * TILE_SIZE + 4, 0 * TILE_SIZE, 14 * TILE_SIZE, 0 * TILE_SIZE},
    {0 * TILE_SIZE, 16 * TILE_SIZE, 5 * TILE_SIZE - 1, 16 * TILE_SIZE},
    {5 * TILE_SIZE, 16 * TILE_SIZE + 1, 5 * TILE_SIZE, 19 * TILE_SIZE - 1},
    {5 * TILE_SIZE - 1, 19 * TILE_SIZE, 0 * TILE_SIZE + 4, 19 * TILE_SIZE},
    {0 * TILE_SIZE + 2, 19 * TILE_SIZE + 1, 0 * TILE_SIZE + 3, 19 * TILE_SIZE + 1},
    {0 * TILE_SIZE + 1, 19 * TILE_SIZE + 2, 0 * TILE_SIZE + 1, 19 * TILE_SIZE + 3},
    {0 * TILE_SIZE, 19 * TILE_SIZE + 4, 0 * TILE_SIZE, 30 * TILE_SIZE + 4},
    {0 * TILE_SIZE + 1, 30 * TILE_SIZE + 5, 0 * TILE_SIZE + 1, 30 * TILE_SIZE + 6},
    {0 * TILE_SIZE + 2, 30 * TILE_SIZE + 7, 0 * TILE_SIZE + 3, 30 * TILE_SIZE + 7},
    {0 * TILE_SIZE + 4, 31 * TILE_SIZE, 14 * TILE_SIZE, 31 * TILE_SIZE},

    // Inner line upper half
    {0 * TILE_SIZE, 13 * TILE_SIZE + 4, 5 * TILE_SIZE + 1, 13 * TILE_SIZE + 4},
    {5 * TILE_SIZE + 2, 13 * TILE_SIZE + 4, 5 * TILE_SIZE + 4, 13 * TILE_SIZE + 2},
    {5 * TILE_SIZE + 4, 13 * TILE_SIZE + 2, 5 * TILE_SIZE + 4, 10 * TILE_SIZE - 1},
    {5 * TILE_SIZE + 4, 10 * TILE_SIZE - 2, 5 * TILE_SIZE + 2, 10 * TILE_SIZE - 4},
    {5 * TILE_SIZE + 2, 10 * TILE_SIZE - 4, 0 * TILE_SIZE + 6, 10 * TILE_SIZE - 4},
    {0 * TILE_SIZE + 6, 10 * TILE_SIZE - 4, 0 * TILE_SIZE + 4, 10 * TILE_SIZE - 6},
    {0 * TILE_SIZE + 4, 10 * TILE_SIZE - 6, 0 * TILE_SIZE + 4, 0 * TILE_SIZE + 6},
    {0 * TILE_SIZE + 4, 0 * TILE_SIZE + 6, 0 * TILE_SIZE + 6, 0 * TILE_SIZE + 4},
    {0 * TILE_SIZE + 6, 0 * TILE_SIZE + 4, 14 * TILE_SIZE - 6, 0 * TILE_SIZE + 4},
    {14 * TILE_SIZE - 6, 0 * TILE_SIZE + 4, 14 * TILE_SIZE - 4, 0 * TILE_SIZE + 6},
    {14 * TILE_SIZE - 4, 0 * TILE_SIZE + 6, 14 * TILE_SIZE - 4, 4 * TILE_SIZE + 2},
    {14 * TILE_SIZE - 4, 4 * TILE_SIZE + 2, 14 * TILE_SIZE - 2, 4 * TILE_SIZE + 4},
    {14 * TILE_SIZE - 2, 4 * TILE_SIZE + 4, 14 * TILE_SIZE, 4 * TILE_SIZE + 4},

    // Inner line lower half
    {0 * TILE_SIZE, 16 * TILE_SIZE - 4, 5 * TILE_SIZE + 1, 16 * TILE_SIZE - 4},
    {5 * TILE_SIZE + 2, 16 * TILE_SIZE - 4, 5 * TILE_SIZE + 4, 16 * TILE_SIZE - 2},
    {5 * TILE_SIZE + 4, 16 * TILE_SIZE - 2, 5 * TILE_SIZE + 4, 19 * TILE_SIZE + 1},
    {5 * TILE_SIZE + 4, 19 * TILE_SIZE + 2, 5 * TILE_SIZE + 2, 19 * TILE_SIZE + 4},
    {5 * TILE_SIZE + 2, 19 * TILE_SIZE + 4, 0 * TILE_SIZE + 6, 19 * TILE_SIZE + 4},
    {0 * TILE_SIZE + 6, 19 * TILE_SIZE + 4, 0 * TILE_SIZE + 4, 19 * TILE_SIZE + 6},
    {0 * TILE_SIZE + 4, 19 * TILE_SIZE + 6, 0 * TILE_SIZE + 4, 24 * TILE_SIZE + 2},
    {0 * TILE_SIZE + 4, 24 * TILE_SIZE + 2, 0 * TILE_SIZE + 6, 24 * TILE_SIZE + 4},
    {0 * TILE_SIZE + 6, 24 * TILE_SIZE + 4, 2 * TILE_SIZE + 2, 24 * TILE_SIZE + 4},
    {2 * TILE_SIZE + 2, 24 * TILE_SIZE + 4, 2 * TILE_SIZE + 4, 24 * TILE_SIZE + 6},
    {2 * TILE_SIZE + 4, 24 * TILE_SIZE + 6, 2 * TILE_SIZE + 4, 25 * TILE_SIZE + 2},
    {2 * TILE_SIZE + 4, 25 * TILE_SIZE + 2, 2 * TILE_SIZE + 2, 25 * TILE_SIZE + 4},
    {2 * TILE_SIZE + 2, 25 * TILE_SIZE + 4, 0 * TILE_SIZE + 6, 25 * TILE_SIZE + 4},
    {0 * TILE_SIZE + 6, 25 * TILE_SIZE + 4, 0 * TILE_SIZE + 4, 25 * TILE_SIZE + 6},
    {0 * TILE_SIZE + 4, 25 * TILE_SIZE + 6, 0 * TILE_SIZE + 4, 30 * TILE_SIZE + 2},
    {0 * TILE_SIZE + 4, 30 * TILE_SIZE + 2, 0 * TILE_SIZE + 6, 30 * TILE_SIZE + 4},
    {0 * TILE_SIZE + 6, 30 * TILE_SIZE + 4, 14 * TILE_SIZE, 30 * TILE_SIZE + 4},

    // L shape near bottom power pellet
    {2 * TILE_SIZE + 6, 21 * TILE_SIZE + 4, 5 * TILE_SIZE + 2, 21 * TILE_SIZE + 4},
    {5 * TILE_SIZE + 2, 21 * TILE_SIZE + 4, 5 * TILE_SIZE + 4, 21 * TILE_SIZE + 6},
    {5 * TILE_SIZE + 4, 21 * TILE_SIZE + 6, 5 * TILE_SIZE + 4, 25 * TILE_SIZE + 2},
    {5 * TILE_SIZE + 4, 25 * TILE_SIZE + 2, 5 * TILE_SIZE + 2, 25 * TILE_SIZE + 4},
    {5 * TILE_SIZE + 2, 25 * TILE_SIZE + 4, 5 * TILE_SIZE - 2, 25 * TILE_SIZE + 4},
    {5 * TILE_SIZE - 2, 25 * TILE_SIZE + 4, 5 * TILE_SIZE - 4, 25 * TILE_SIZE + 2},
    {5 * TILE_SIZE - 4, 25 * TILE_SIZE + 2, 5 * TILE_SIZE - 4, 22 * TILE_SIZE + 6},
    {5 * TILE_SIZE - 4, 22 * TILE_SIZE + 6, 5 * TILE_SIZE - 6, 22 * TILE_SIZE + 4},
    {5 * TILE_SIZE - 6, 22 * TILE_SIZE + 4, 2 * TILE_SIZE + 6, 22 * TILE_SIZE + 4},
    {2 * TILE_SIZE + 6, 22 * TILE_SIZE + 4, 2 * TILE_SIZE + 4, 22 * TILE_SIZE + 2},
    {2 * TILE_SIZE + 4, 22 * TILE_SIZE + 2, 2 * TILE_SIZE + 4, 22 * TILE_SIZE - 2},
    {2 * TILE_SIZE + 4, 22 * TILE_SIZE - 2, 2 * TILE_SIZE + 6, 21 * TILE_SIZE + 4},

    // Top T
    {7 * TILE_SIZE + 4, 6 * TILE_SIZE + 6, 7 * TILE_SIZE + 4, 13 * TILE_SIZE + 2},
    {7 * TILE_SIZE + 4, 13 * TILE_SIZE + 2, 7 * TILE_SIZE + 6, 13 * TILE_SIZE + 4},
    {7 * TILE_SIZE + 6, 13 * TILE_SIZE + 4, 8 * TILE_SIZE + 2, 13 * TILE_SIZE + 4},
    {8 * TILE_SIZE + 2, 13 * TILE_SIZE + 4, 8 * TILE_SIZE + 4, 13 * TILE_SIZE + 2},
    {8 * TILE_SIZE + 4, 13 * TILE_SIZE + 2, 8 * TILE_SIZE + 4, 10 * TILE_SIZE + 6},
    {8 * TILE_SIZE + 4, 10 * TILE_SIZE + 6, 8 * TILE_SIZE + 6, 10 * TILE_SIZE + 4},
    {8 * TILE_SIZE + 6, 10 * TILE_SIZE + 4, 11 * TILE_SIZE + 2, 10 * TILE_SIZE + 4},
    {11 * TILE_SIZE + 2, 10 * TILE_SIZE + 4, 11 * TILE_SIZE + 4, 10 * TILE_SIZE + 2},
    {11 * TILE_SIZE + 4, 10 * TILE_SIZE + 2, 11 * TILE_SIZE + 4, 10 * TILE_SIZE - 2},
    {11 * TILE_SIZE + 4, 10 * TILE_SIZE - 2, 11 * TILE_SIZE + 2, 10 * TILE_SIZE - 4},
    {11 * TILE_SIZE + 2, 10 * TILE_SIZE - 4, 8 * TILE_SIZE + 6, 10 * TILE_SIZE - 4},
    {8 * TILE_SIZE + 6, 10 * TILE_SIZE - 4, 8 * TILE_SIZE + 4, 10 * TILE_SIZE - 6},
    {8 * TILE_SIZE + 4, 10 * TILE_SIZE - 6, 8 * TILE_SIZE + 4, 6 * TILE_SIZE + 6},
    {8 * TILE_SIZE + 4, 6 * TILE_SIZE + 6, 8 * TILE_SIZE + 2, 6 * TILE_SIZE + 4},
    {8 * TILE_SIZE + 2, 6 * TILE_SIZE + 4, 8 * TILE_SIZE - 2, 6 * TILE_SIZE + 4},
    {8 * TILE_SIZE - 2, 6 * TILE_SIZE + 4, 8 * TILE_SIZE - 4, 6 * TILE_SIZE + 6},

    // Weird bottom T
    {2 * TILE_SIZE + 6, 27 * TILE_SIZE + 4, 7 * TILE_SIZE + 2, 27 * TILE_SIZE + 4},
    {7 * TILE_SIZE + 2, 27 * TILE_SIZE + 4, 7 * TILE_SIZE + 4, 27 * TILE_SIZE + 2},
    {7 * TILE_SIZE + 4, 27 * TILE_SIZE + 2, 7 * TILE_SIZE + 4, 25 * TILE_SIZE - 2},
    {7 * TILE_SIZE + 4, 25 * TILE_SIZE - 2, 7 * TILE_SIZE + 6, 25 * TILE_SIZE - 4},
    {7 * TILE_SIZE + 6, 25 * TILE_SIZE - 4, 8 * TILE_SIZE + 2, 25 * TILE_SIZE - 4},
    {8 * TILE_SIZE + 2, 25 * TILE_SIZE - 4, 8 * TILE_SIZE + 4, 25 * TILE_SIZE - 2},
    {8 * TILE_SIZE + 4, 25 * TILE_SIZE - 2, 8 * TILE_SIZE + 4, 27 * TILE_SIZE + 2},
    {8 * TILE_SIZE + 4, 27 * TILE_SIZE + 2, 8 * TILE_SIZE + 6, 27 * TILE_SIZE + 4},
    {8 * TILE_SIZE + 6, 27 * TILE_SIZE + 4, 11 * TILE_SIZE + 2, 27 * TILE_SIZE + 4},
    {11 * TILE_SIZE + 2, 27 * TILE_SIZE + 4, 11 * TILE_SIZE + 4, 27 * TILE_SIZE + 6},
    {11 * TILE_SIZE + 4, 27 * TILE_SIZE + 6, 11 * TILE_SIZE + 4, 28 * TILE_SIZE + 2},
    {11 * TILE_SIZE + 4, 28 * TILE_SIZE + 2, 11 * TILE_SIZE + 2, 28 * TILE_SIZE + 4},
    {11 * TILE_SIZE + 2, 28 * TILE_SIZE + 4, 2 * TILE_SIZE + 6, 28 * TILE_SIZE + 4},
    {2 * TILE_SIZE + 6, 28 * TILE_SIZE + 4, 2 * TILE_SIZE + 4, 28 * TILE_SIZE + 2},
    {2 * TILE_SIZE + 4, 28 * TILE_SIZE + 2, 2 * TILE_SIZE + 4, 27 * TILE_SIZE + 6},
    {2 * TILE_SIZE + 4, 27 * TILE_SIZE + 6, 2 * TILE_SIZE + 6, 27 * TILE_SIZE + 4},

    // Bottom Misshapen T
};

int numLeftLines = sizeof(leftSideLines) / sizeof(Line);
int numOvals = sizeof(ovals) / sizeof(Oval);
int numHalfTs = sizeof(halfT) / sizeof(Point);

inline void mirrorLines(const Line *leftLines, const int count, Line *mirroredLines) {
    const int centerX = MAZE_WIDTH / 2; // Axis of symmetry in pixels (center of the maze)
    for (int i = 0; i < count; i++) {
        mirroredLines[i].x1 = centerX + (centerX - leftLines[i].x1);
        mirroredLines[i].y1 = leftLines[i].y1;
        mirroredLines[i].x2 = centerX + (centerX - leftLines[i].x2);
        mirroredLines[i].y2 = leftLines[i].y2;
    }
}

inline void genHalfT(Line *lines, const Point upperRight) {
    int lineIndex = 0;

    lines[lineIndex++] = (Line){upperRight.x, upperRight.y, upperRight.x - 3 * TILE_SIZE - 2, upperRight.y};
    lines[lineIndex++] = (Line){
        upperRight.x - 3 * TILE_SIZE - 2, upperRight.y, upperRight.x - 3 * TILE_SIZE - 4, upperRight.y + 2
    };
    lines[lineIndex++] = (Line){
        upperRight.x - 3 * TILE_SIZE - 4, upperRight.y + 2, upperRight.x - 3 * TILE_SIZE - 4, upperRight.y + 6
    };
    lines[lineIndex++] = (Line){
        upperRight.x - 3 * TILE_SIZE - 4, upperRight.y + 6, upperRight.x - 3 * TILE_SIZE - 2, upperRight.y + 8
    };
    lines[lineIndex++] = (Line){upperRight.x - 3 * TILE_SIZE - 2, upperRight.y + 8, upperRight.x - 6, upperRight.y + 8};
    lines[lineIndex++] = (Line){upperRight.x - 6, upperRight.y + 8, upperRight.x - 4, upperRight.y + 10};
    lines[lineIndex++] = (Line){
        upperRight.x - 4, upperRight.y + 10, upperRight.x - 4, upperRight.y + 3 * TILE_SIZE + 6
    };
    lines[lineIndex++] = (Line){
        upperRight.x - 4, upperRight.y + 3 * TILE_SIZE + 6, upperRight.x - 2, upperRight.y + 3 * TILE_SIZE + 8
    };
    lines[lineIndex] = (Line){
        upperRight.x - 2, upperRight.y + 3 * TILE_SIZE + 8, upperRight.x, upperRight.y + 3 * TILE_SIZE + 8
    };
}

inline void genOval(Line *lines, const Oval oval) {
    int lineIndex = 0;
    const Point topLeft = oval.ul;
    const Point bottomRight = oval.lr;

    lines[lineIndex++] = (Line){topLeft.x + 2, topLeft.y, bottomRight.x - 2, topLeft.y};
    lines[lineIndex++] = (Line){topLeft.x + 2, bottomRight.y, bottomRight.x - 2, bottomRight.y};
    lines[lineIndex++] = (Line){topLeft.x, topLeft.y + 2, topLeft.x, bottomRight.y - 2};
    lines[lineIndex++] = (Line){bottomRight.x, topLeft.y + 2, bottomRight.x, bottomRight.y - 2};
    lines[lineIndex++] = (Line){topLeft.x, topLeft.y + 2, topLeft.x + 2, topLeft.y};
    lines[lineIndex++] = (Line){topLeft.x, bottomRight.y - 2, topLeft.x + 2, bottomRight.y};
    lines[lineIndex++] = (Line){bottomRight.x - 2, topLeft.y, bottomRight.x, topLeft.y + 2};
    lines[lineIndex] = (Line){bottomRight.x - 2, bottomRight.y, bottomRight.x, bottomRight.y - 2};
}

// Function to generate all maze lines
inline void generateMazeLines(Line *combinedLines, int *totalLines) {
    int currentIndex = 0;

    // Copy original left-side lines
    for (int i = 0; i < numLeftLines; i++) {
        combinedLines[currentIndex++] = leftSideLines[i];
    }

    // Half Ts (or full Ts when they're mirrored)
    for (int i = 0; i < numHalfTs; i++) {
        Line tLines[9];
        genHalfT(tLines, halfT[i]);

        for (int j = 0; j < 9; j++) {
            combinedLines[currentIndex++] = tLines[j];
        }

        Line mirroredTLines[9];
        mirrorLines(tLines, 9, mirroredTLines);

        for (int j = 0; j < 9; j++) {
            combinedLines[currentIndex++] = mirroredTLines[j];
        }
    }

    // Add the ovals
    for (int i = 0; i < numOvals; i++) {
        Line ovalLines[8]; // Temporary storage for oval lines
        genOval(ovalLines, ovals[i]);

        // Append oval lines to combinedLines
        for (int j = 0; j < 8; j++) {
            combinedLines[currentIndex++] = ovalLines[j];
        }

        // Mirror the oval lines
        Line mirroredOvalLines[8];
        mirrorLines(ovalLines, 8, mirroredOvalLines);

        // Append mirrored oval lines to combinedLines
        for (int j = 0; j < 8; j++) {
            combinedLines[currentIndex++] = mirroredOvalLines[j];
        }
    }

    // Add mirrored lines
    Line mirroredLeftLines[numLeftLines];
    mirrorLines(leftSideLines, numLeftLines, mirroredLeftLines);

    for (int i = 0; i < numLeftLines; i++) {
        combinedLines[currentIndex++] = mirroredLeftLines[i];
    }

    *totalLines = currentIndex;
}

// Draw the maze on the RastPort
inline void DrawMaze(struct RastPort *rp) {
    Line combinedLines[2 * numLeftLines + 16 * numOvals + 54];
    int totalLines;

    // Generate full maze lines
    generateMazeLines(combinedLines, &totalLines);

    // Draw the lines
    SetAPen(rp, 0x04); // Maze color
    for (int i = 0; i < totalLines; i++) {
        Move(rp, combinedLines[i].x1, combinedLines[i].y1);
        Draw(rp, combinedLines[i].x2, combinedLines[i].y2);
    }

    // Draw the pink ghost house door
    SetAPen(rp, 0x05);
    RectFill(rp, 13 * TILE_SIZE + 1, 12 * TILE_SIZE + 5, 15 * TILE_SIZE - 1, 12 * TILE_SIZE + 7);
}

#endif //MAZEBORDERS2_H
