#ifndef BOARD_CELL_H
#define BOARD_CELL_H

#include "CellType.h"
#include "Direction.h"

template <CellType T, Direction D, int N>
struct BoardCell
{
    constexpr static CellType type = T;
    constexpr static Direction direction = N;
    constexpr static int length = N;
};

#endif