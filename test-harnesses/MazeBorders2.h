//
// Created by Barry Walker on 11/16/24.
//

#ifndef MAZEBORDERS2_H
#define MAZEBORDERS2_H

#define TILE_SIZE 7
#include <graphics/rastport.h>

UWORD maze[] = {
    0, 13 * TILE_SIZE, 4 * TILE_SIZE - 1, 13 * TILE_SIZE,
    4 * TILE_SIZE, 13 * TILE_SIZE - 1, 4 * TILE_SIZE, 10 * TILE_SIZE + 1,
    4 * TILE_SIZE - 1, 10 * TILE_SIZE, 0 * TILE_SIZE + 4, 10 * TILE_SIZE,
    0 * TILE_SIZE + 3, 10 * TILE_SIZE - 1, 0 * TILE_SIZE + 2, 10 * TILE_SIZE - 1,
    0 * TILE_SIZE + 1, 10 * TILE_SIZE - 3, 0 * TILE_SIZE + 1, 10 * TILE_SIZE - 2,
    0 * TILE_SIZE, 10 * TILE_SIZE - 4, 0 * TILE_SIZE, 0 * TILE_SIZE + 4,
    0 * TILE_SIZE + 1, 0 * TILE_SIZE + 3, 0 * TILE_SIZE + 1, 0 * TILE_SIZE + 2,
    0 * TILE_SIZE + 2, 0 * TILE_SIZE + 1, 0 * TILE_SIZE + 3, 0 * TILE_SIZE + 1,
    0 * TILE_SIZE + 4, 0 * TILE_SIZE, 28 * TILE_SIZE - 4, 0 * TILE_SIZE,
    28 * TILE_SIZE - 3, 0 * TILE_SIZE + 1, 28 * TILE_SIZE - 2, 0 * TILE_SIZE + 1,
    28 * TILE_SIZE - 1, 0 * TILE_SIZE + 2, 28 * TILE_SIZE - 1, 0 * TILE_SIZE + 3,
    28 * TILE_SIZE, 0 * TILE_SIZE + 4, 28 * TILE_SIZE, 10 * TILE_SIZE - 4,
    28 * TILE_SIZE - 1, 10 * TILE_SIZE - 3, 28 * TILE_SIZE - 1, 10 * TILE_SIZE - 2,
    28 * TILE_SIZE - 2, 10 * TILE_SIZE - 1, 28 * TILE_SIZE - 3, 10 * TILE_SIZE - 1,
    28 * TILE_SIZE - 4, 10 * TILE_SIZE, 24 * TILE_SIZE + 1, 10 * TILE_SIZE,
    24 * TILE_SIZE, 10 * TILE_SIZE + 1, 24 * TILE_SIZE, 13 * TILE_SIZE - 1,
    24 * TILE_SIZE + 1, 13 * TILE_SIZE, 28 * TILE_SIZE, 13 * TILE_SIZE,

    0, 13 * TILE_SIZE + 3, 4 * TILE_SIZE + 1, 13 * TILE_SIZE + 3,
    4 * TILE_SIZE + 2, 13 * TILE_SIZE + 2, 4 * TILE_SIZE + 2, 13 * TILE_SIZE + 2, // Corner dot
    4 * TILE_SIZE + 3, 13 * TILE_SIZE + 1, 4 * TILE_SIZE + 3, 10 * TILE_SIZE - 1,
    4 * TILE_SIZE + 2, 10 * TILE_SIZE - 2, 4 * TILE_SIZE + 2, 10 * TILE_SIZE - 2, // Corner dot
    4 * TILE_SIZE + 1, 10 * TILE_SIZE - 3, 0 * TILE_SIZE + 5, 10 * TILE_SIZE - 3,
    0 * TILE_SIZE + 4, 10 * TILE_SIZE - 4, 0 * TILE_SIZE + 4, 10 * TILE_SIZE - 4, // Corner dot

    0 * TILE_SIZE + 3, 10 * TILE_SIZE - 5, 0 * TILE_SIZE + 3, 0 * TILE_SIZE + 5,
    0 * TILE_SIZE + 4, 0 * TILE_SIZE + 4, 0 * TILE_SIZE + 4, 0 * TILE_SIZE + 4, // Corner dot
    0 * TILE_SIZE + 5, 0 * TILE_SIZE + 3, 28 * TILE_SIZE - 5, 0 * TILE_SIZE + 3,
    28 * TILE_SIZE - 4, 0 * TILE_SIZE + 4, 28 * TILE_SIZE - 4, 0 * TILE_SIZE + 4, // Corner dot
    28 * TILE_SIZE - 3, 0 * TILE_SIZE + 5, 28 * TILE_SIZE - 3, 10 * TILE_SIZE - 5,
    28 * TILE_SIZE - 4, 10 * TILE_SIZE - 4, 28 * TILE_SIZE - 4, 10 * TILE_SIZE - 4,
    28 * TILE_SIZE - 5, 10 * TILE_SIZE - 3, 24 * TILE_SIZE - 1, 10 * TILE_SIZE - 3,
    24 * TILE_SIZE - 2, 10 * TILE_SIZE - 2, 24 * TILE_SIZE - 2, 10 * TILE_SIZE - 2,
    24 * TILE_SIZE - 3, 10 * TILE_SIZE - 1, 24 * TILE_SIZE - 3, 13 * TILE_SIZE + 1,
    24 * TILE_SIZE - 2, 13 * TILE_SIZE + 2, 24 * TILE_SIZE - 2, 13 * TILE_SIZE + 2,
    24 * TILE_SIZE - 1, 13 * TILE_SIZE + 3, 28 * TILE_SIZE, 13 * TILE_SIZE + 3,

    0 * TILE_SIZE, 16 * TILE_SIZE, 4 * TILE_SIZE - 1, 16 * TILE_SIZE,
    4 * TILE_SIZE, 16 * TILE_SIZE + 1, 4 * TILE_SIZE, 19 * TILE_SIZE - 1,
    4 * TILE_SIZE - 1, 19 * TILE_SIZE, 0 * TILE_SIZE + 4, 19 * TILE_SIZE,
    0 * TILE_SIZE + 2, 19 * TILE_SIZE + 1, 0 * TILE_SIZE + 3, 19 * TILE_SIZE + 1,
    0 * TILE_SIZE + 1, 19 * TILE_SIZE + 2, 0 * TILE_SIZE + 1, 19 * TILE_SIZE + 3,
    0 * TILE_SIZE, 19 * TILE_SIZE + 3, 0 * TILE_SIZE, 30 * TILE_SIZE + 3,

    0 * TILE_SIZE, 16 * TILE_SIZE - 3, 4 * TILE_SIZE + 1, 16 * TILE_SIZE - 3,
    4 * TILE_SIZE + 2, 16 * TILE_SIZE - 2, 4 * TILE_SIZE + 2, 16 * TILE_SIZE - 2, // Corner dot
    4 * TILE_SIZE + 3, 16 * TILE_SIZE - 1, 4 * TILE_SIZE + 3, 19 * TILE_SIZE + 1,
    4 * TILE_SIZE + 2, 19 * TILE_SIZE + 2, 4 * TILE_SIZE + 2, 19 * TILE_SIZE + 2, // Corner dot
    4 * TILE_SIZE + 1, 19 * TILE_SIZE + 3, 0 * TILE_SIZE + 5, 19 * TILE_SIZE + 3,
    0 * TILE_SIZE + 4, 19 * TILE_SIZE + 4, 0 * TILE_SIZE + 4, 19 * TILE_SIZE + 4, // Corner dot
    0 * TILE_SIZE + 3, 19 * TILE_SIZE + 5, 0 * TILE_SIZE + 3, 24 * TILE_SIZE + 2,
    0 * TILE_SIZE + 4, 24 * TILE_SIZE + 3, 0 * TILE_SIZE + 4, 24 * TILE_SIZE + 3, // Corner dot
};

inline void DrawMaze(struct RastPort *rp) {
    SetAPen(rp, 0x04); // Maze color

    for (int i = 0; i < sizeof(maze) / sizeof(maze[0]); i += 4) {
        Move(rp, maze[i], maze[i + 1]);
        Draw(rp, maze[i + 2], maze[i + 3]);
    }
}

#endif //MAZEBORDERS2_H
