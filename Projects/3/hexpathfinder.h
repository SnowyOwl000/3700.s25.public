//
// Created by bob on 11/23/18.
//

#ifndef HEXPATHFINDER_H
#define HEXPATHFINDER_H

#include <cstdint>

const uint32_t
        MAX_ROWS    = 50,
        MAX_COLS    = 50,
        DRAW_E      = 6,
        DRAW_V      = 5,
        DRAW_X_LEFT = 54,
        DRAW_Y_TOP  = 708;

#define computeX(c) (DRAW_X_LEFT + DRAW_E + (3 * DRAW_E * (c)) / 2)
#define computeY(r,c) (DRAW_Y_TOP - DRAW_V - 2 * DRAW_V * (r) - ((c) & 1u) * DRAW_V)

//
// these are constants to use in the maze cells
//

enum CellValues {
    WALL_UP         = 0x01u,
    WALL_UP_RIGHT   = 0x02u,
    WALL_DOWN_RIGHT = 0x04u,
    WALL_DOWN       = 0x08u,
    WALL_DOWN_LEFT  = 0x10u,
    WALL_UP_LEFT    = 0x20u,
    VISITED         = 0x40u,
    DEAD_END        = 0x80u
};

//=============================================================================
// void printMaze(uint8_t maze[][MAX_COLS],int nR,int nC);
//  print the given maze
//
// Parameters
//  maze - MAX_ROWS x MAX_COLS character array containing maze information
//  nR   - number of rows in the maze
//  nC   - number of columns in the maze
//

void printMaze(uint8_t maze[][MAX_COLS],uint32_t nR,uint32_t nC);

#endif //HEXPATHFINDER_H
