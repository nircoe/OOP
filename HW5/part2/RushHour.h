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

template <typename GameBoard, int R, int C, int A>
struct CheckEmptyUntilTheEnd
{
private:
    typedef typename GameBoard::board b;
    typedef typename GetAtIndex<R, b>::value row;
    typedef typename GetAtIndex<C, row>::value cell;
    constexpr static bool isEmpty = cell::type == EMPTY || cell::type == X;

public:
    constexpr static bool result = ConditionalInteger<
                              isEmpty,
                              CheckEmptyUntilTheEnd<GameBoard, R, C + 1, A - 1>::result,
                          false > ::value;
};

template <typename GameBoard, int R, int C>
struct CheckEmptyUntilTheEnd<GameBoard, R, C, -1>
{
    constexpr static bool result = true;
};

template <typename GameBoard>
struct CheckWin
{
private:
    typedef FindCar<GameBoard, X, GameBoard::length - 1, GameBoard::width - 1> redCarPosition;
    constexpr static bool isWin = CheckEmptyUntilTheEnd<GameBoard, redCarPosition::row, redCarPosition::column, GameBoard::width - redCarPosition::column - 1>::result;
public:
    constexpr static bool result = isWin;
};

template <typename GameBoard, typename M>
struct CheckSolution;

template <typename GameBoard, typename M, typename... MM>
struct CheckSolution<GameBoard, List<M, MM...>>
{
private:
    typedef FindCar<GameBoard, M::type, GameBoard::length - 1, GameBoard::width - 1> carPosition;
    typedef typename MoveVehicle<GameBoard, carPosition::row, carPosition::column, M::direction, M::amount>::board newBoard;

public:
    constexpr static bool result = CheckSolution<newBoard, List<MM...>>::result;
};

template <typename GameBoard>
struct CheckSolution<GameBoard, List<>>
{
    constexpr static bool result = CheckWin<GameBoard>::result;
};

#endif
