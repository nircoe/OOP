#ifndef RUSH_HOUR_H
#define RUSH_HOUR_H

#include "GameBoard.h"
#include "BoardCell.h"
#include "List.h"
#include "MoveVehicle.h"
#include "Printer.h"
#include "Direction.h"
#include "TransposeList.h"
#include "Utilities.h"

template <typename GameBoard>
struct CheckWin
{
private:

    constexpr static CellType getCellType(int R, int C)
    {
        typedef typename GameBoard::board b;
        typedef typename GetAtIndex<R, b>::value row;
        typedef typename GetAtIndex<C, row>::value cell;
        return cell::type;
    }

    constexpr static int getCellLength(int R, int C)
    {
        typedef typename GameBoard::board b;
        typedef typename GetAtIndex<R, b>::value row;
        typedef typename GetAtIndex<C, row>::value cell;
        return cell::length;
    }

    constexpr static bool FindRedCar(int R, int C)
    {
        static_assert((R < GameBoard::length), "No red car in board");
        constexpr static int next_R = (C < GameBoard::width) ? R : R + 1;
        constexpr static int next_C = (C < GameBoard::width) ? C + 1 : 0;
        return (getCellType(R, C) == X) ? CheckNextEmpty(R, C + getCellLength(R, C)) : FindRedCar(next_R, next_C);
    }

    constexpr static bool CheckNextEmpty(int R, int C)
    {
        return (C == GameBoard::width) ? true : ((getCellType(R, C) == EMPTY) ? CheckNextEmpty(R, C + 1) : false);
    }

    constexpr static bool IsWin()
    {
        return FindRedCar(0, 0);
    }

public:
    constexpr bool result = IsWin();
};

template <typename GB, typename Move>
struct CheckSolution
{

};

template <typename GB, typename... Moves>
struct CheckSolution
{

};

#endif
