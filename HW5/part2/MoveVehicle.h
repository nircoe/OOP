#ifndef MOVE_VEHICLE_H
#define MOVE_VEHICLE_H

#include "CellType.h"
#include "Direction.h"
#include "GameBoard.h"
#include "TransposeList.h"

/* Move */
template <CellType T, Direction D, int N>
struct Move
{
    static_assert(T != EMPTY, "CellType is EMPTY");
    constexpr static CellType type = T;
    constexpr static Direction direction = D;
    constexpr static int amount = N;
};

/* MoveVehicle */
template <typename GameBoard, int R, int C, Direction D, int A>
struct MoveVehicle
{
private:
    constexpr static CellType getCellType()
    {
        typedef typename GameBoard::board b;
        typedef typename GetAtIndex<C, b>::value b1;
        typedef typename GetAtIndex<R, b1>::value cell;
        return cell::type;
    }

    constexpr static Direction getDirection()
    {
        typedef typename GameBoard::board b;
        typedef typename GetAtIndex<C, b>::value b1;
        typedef typename GetAtIndex<R, b1>::value cell;
        return cell::direction;
    }

    constexpr static CellType getNextCellType()
    {
        typedef typename IF<D == UP || D == DOWN, typename GameBoard::board, typename Transpose<typename GameBoard::board>::matrix>::RET b;
        typedef typename GetAtIndex<(D == UP || D == DOWN ? C : R) + (D == UP || D == LEFT ? -1 : 1), b>::value b1;
        typedef typename GetAtIndex<(D == UP || D == DOWN ? R : C) , b1>::value cell;
        return cell::type;
    }

public:
    static_assert(R >= 0 && R < GameBoard::width, "R out of bounds");
    static_assert(C >= 0 && C < GameBoard::length, "C out of bounds");
    static_assert(getCellType() != EMPTY, "Selected cell type is EMPTY");
    static_assert(
        ((getDirection() == UP || getDirection() == DOWN) && (D == UP || D == DOWN)) ||
        ((getDirection() == LEFT || getDirection() == RIGHT) && (D == LEFT || D == RIGHT)),
        "Selected cell direction is not valid");
    static_assert(getNextCellType() == EMPTY, "Move is not valid");
    typedef GameBoard board;
};

template <typename GameBoard, int R, int C, Direction D>
struct MoveVehicle<GameBoard, R, C, D, 0>
{
private:
    constexpr static CellType getCellType()
    {
        typedef typename GameBoard::board b;
        typedef typename GetAtIndex<C, b>::value b1;
        typedef typename GetAtIndex<R, b1>::value cell;
        return cell::type;
    }

    constexpr static Direction getDirection()
    {
        typedef typename GameBoard::board b;
        typedef typename GetAtIndex<C, b>::value b1;
        typedef typename GetAtIndex<R, b1>::value cell;
        return cell::direction;
    }

public:
    static_assert(R >= 0 && R < GameBoard::width, "R out of bounds");
    static_assert(C >= 0 && C < GameBoard::length, "C out of bounds");
    static_assert(getCellType() != EMPTY, "Selected cell type is EMPTY");
    static_assert(
        ((getDirection() == UP || getDirection() == DOWN) && (D == UP || D == DOWN)) ||
        ((getDirection() == LEFT || getDirection() == RIGHT) && (D == LEFT || D == RIGHT)),
        "Selected cell direction is not valid");
    typedef GameBoard board;
};

#endif