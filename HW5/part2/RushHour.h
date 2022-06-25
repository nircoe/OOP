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
#include "CellType.h"

template <typename GameBoard, int R, int C>
struct CheckEmptyUntillTheEnd
{
private:

    typedef typename GameBoard::board b;
    typedef typename GetAtIndex<R, b>::value row;
    typedef typename GetAtIndex<C, row>::value cell;

public:

    constexpr static bool result = (C == GameBoard::width) ? true : ((cell::type == EMPTY) ? CheckEmptyUntillTheEnd<GameBoard, R, C + 1>::result : false);

};

template <typename GameBoard, int R, int C>
struct CheckWinAux
{
private:

    typedef typename GameBoard::board b;
    typedef typename GetAtIndex<R, b>::value row;
    typedef typename GetAtIndex<C, row>::value cell;
    static_assert((R < GameBoard::length), "No red car in board");
    constexpr static int next_R = (C < GameBoard::width) ? R : R + 1;
    constexpr static int next_C = (C < GameBoard::width) ? C + 1 : 0;

public:

    constexpr static bool result = (cell::type == X) ? CheckEmptyUntillTheEnd<GameBoard, R, C + cell::length>::result : CheckWinAux<GameBoard, next_R, next_C>::result;
};

template <typename GameBoard>
struct CheckWin
{
    constexpr static bool result = CheckWinAux<GameBoard, 0, 0>::result;
};

template<int R, int C>
struct Point
{
    constexpr static int row = R;
    constexpr static int column = C;
};

template <typename GameBoard, typename... M>
struct CheckSolution;

template <typename GameBoard, typename M>
struct CheckSolution<GameBoard, List<M>>
{
private:
    typedef typename List<M>::head move;
    constexpr static int row = GetVehicle<GameBoard, move::type, 0, 0>::R;
    constexpr static int column = GetVehicle<GameBoard, move::type, 0, 0>::C;

    typedef typename MoveVehicle<GameBoard, row, column, move::direction, move::amount>::board board_after_move;

public:
    constexpr static bool result = CheckWin<board_after_move>::result;

};

template <typename GameBoard, typename... M>
struct CheckSolution<GameBoard, List<M...>>
{
private:
    typedef typename List<M...>::head move;
    typedef typename List<M...>::next next_moves;
    constexpr static int row = GetVehicle<GameBoard, move::type, 0, 0>::row;
    constexpr static int column = GetVehicle<GameBoard, move::type, 0, 0>::column;

    typedef typename MoveVehicle<GameBoard, row, column, move::direction, move::amount>::board board_after_move;

public:
    constexpr static bool result = CheckSolution<board_after_move, next_moves>::result;
};

#endif
