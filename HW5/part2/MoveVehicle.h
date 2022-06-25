#ifndef MOVE_VEHICLE_H
#define MOVE_VEHICLE_H

#include "CellType.h"
#include "Direction.h"
#include "GameBoard.h"
#include "TransposeList.h"
#include "BoardCell.h"
#include "Utilities.h"

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
        typedef typename GetAtIndex<R, b>::value row;
        typedef typename GetAtIndex<C, row>::value cell;
        return cell::type;
    }

    constexpr static Direction getDirection()
    {
        typedef typename GameBoard::board b;
        typedef typename GetAtIndex<R, b>::value row;
        typedef typename GetAtIndex<C, row>::value cell;
        return cell::direction;
    }
    
    constexpr static CellType getNextCellType()
    {
         typedef typename GameBoard::board b;
        typedef typename GetAtIndex<(D == UP) ? (R + 1) : ((D == DOWN) ? (R - 1) : R), b>::value b1;
        typedef typename GetAtIndex<(D == RIGHT) ? (C + 1) : ((D == LEFT) ? (C - 1) : C), b1>::value cell;
        return cell::type;
    }

    constexpr static int new_R = (D == UP) ? (R - 1) : ((D == DOWN) ? (R + 1) : R);
    constexpr static int new_C = (D == RIGHT) ? (C + 1) : ((D == LEFT) ? (C - 1) : C);
    typedef GameBoard old_board;
    typedef typename GameBoard::board b;
    typedef typename GetAtIndex<R, b>::value prev_row;
    typedef typename GetAtIndex<C, prev_row>::value prev_cell;
    typedef typename GetAtIndex<new_R, b>::value new_row;
    typedef typename SetAtIndex<new_C, prev_cell, new_row>::list changed_new_row;
    
    typedef typename Conditional<(new_R == R), changed_new_row, prev_row>::value row_to_change;
    typedef typename SetAtIndex<C, BoardCell<Empty, 0, 0>, row_to_change>::list changed_prev_row;

    typedef typename Conditional<(new_R == R), SetAtIndex<R, changed_prev_row, b>::list, SetAtIndex<R, changed_prev_row, SetAtIndex<new_R, changed_new_row, b>::list>::list>::value new_b;
    typedef typename GameBoard<new_b, old_board::width, old_board::length> new_board;



public:
    static_assert(R >= 0 && R < GameBoard::width, "R out of bounds");
    static_assert(C >= 0 && C < GameBoard::length, "C out of bounds");
    static_assert(getCellType() != EMPTY, "Selected cell type is EMPTY");
    static_assert(
        ((getDirection() == UP || getDirection() == DOWN) && (D == UP || D == DOWN)) ||
        ((getDirection() == LEFT || getDirection() == RIGHT) && (D == LEFT || D == RIGHT)),
        "Selected cell direction is not valid");
    static_assert(getNextCellType() == EMPTY, "Move is not valid");

    typedef MoveVehicle<new_board, new_R, new_C, D, A - 1>::board board;
};

template <typename GameBoard, int R, int C, Direction D>
struct MoveVehicle<GameBoard, R, C, D, 0>
{
private:
    constexpr static CellType getCellType()
    {
        typedef typename GameBoard::board b;
        typedef typename GetAtIndex<R, b>::value b1;
        typedef typename GetAtIndex<C, b1>::value cell;
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