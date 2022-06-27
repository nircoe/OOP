#ifndef MOVE_VEHICLE_H
#define MOVE_VEHICLE_H

#include "CellType.h"
#include "Direction.h"
#include "GameBoard.h"
#include "TransposeList.h"
#include "BoardCell.h"
#include "Utilities.h"

/*Get Vehicle Location*/
template <typename GameBoard, CellType type, int R, int C>
struct GetVehicle
{
private:

    typedef typename GameBoard::board b;
    typedef typename GetAtIndex<R, b>::value row_list;
    typedef typename GetAtIndex<C, row_list>::value cell;
    static_assert((R < GameBoard::length), "No red car in board");
    constexpr static int next_R = (C < GameBoard::width) ? R : R + 1;
    constexpr static int next_C = (C < GameBoard::width) ? C + 1 : 0;
    constexpr static int n_R = ConditionalInteger<(next_R < GameBoard::length), next_R, -1>::value;
    constexpr static int n_C = ConditionalInteger<(next_R < GameBoard::length), next_C, -1>::value;

public:

    constexpr static int row = (cell::type == type) ? R : GetVehicle<GameBoard, type, n_R, n_C>::row;
    constexpr static int column = (cell::type == type) ? C : GetVehicle<GameBoard, type, n_R, n_C>::column;
};

template <typename GameBoard, CellType type>
struct GetVehicle<GameBoard, type, -1, -1>
{
  
    constexpr static int row = -1;
    constexpr static int column = -1;
};


/* Move */
template <CellType T, Direction D, int N>
struct Move
{
    static_assert(T != EMPTY, "CellType is EMPTY");
    constexpr static CellType type = T;
    constexpr static Direction direction = D;
    constexpr static int amount = N;
};

template <typename GB, int R, int C, Direction D, int A, int L>
struct MoveVehicleAux
{
private:

    constexpr static CellType getCellType()
    {
        typedef typename GB::board b;
        typedef typename GetAtIndex<R, b>::value row;
        typedef typename GetAtIndex<C, row>::value cell;
        return cell::type;
    }

    constexpr static Direction getDirection()
    {
        typedef typename GB::board b;
        typedef typename GetAtIndex<R, b>::value row;
        typedef typename GetAtIndex<C, row>::value cell;
        return cell::direction;
    }

    constexpr static CellType getNextCellType()
    {
        constexpr int new_R = (D == UP) ? (R - 1) : ((D == DOWN) ? (R + 1) : R);
        constexpr int new_C = (D == RIGHT) ? (C + 1) : ((D == LEFT) ? (C - 1) : C);
        typedef typename GB::board b;
        typedef typename GetAtIndex<new_R, b>::value b1;
        typedef typename GetAtIndex<new_C, b1>::value cell;
        return cell::type;
    }

    constexpr static int new_R = (D == UP) ? (R - A) : ((D == DOWN) ? (R + A) : R);
    constexpr static int new_C = (D == RIGHT) ? (C + A) : ((D == LEFT) ? (C - A) : C);
    constexpr static int next_R = (D == UP) ? (R - 1) : ((D == DOWN) ? (R + 1) : R);
    constexpr static int next_C = (D == RIGHT) ? (C + 1) : ((D == LEFT) ? (C - 1) : C);
    typedef GB old_board;
    typedef typename GB::board b;
    typedef typename GetAtIndex<R, b>::value prev_row;
    typedef typename GetAtIndex<C, prev_row>::value prev_cell;
    typedef typename GetAtIndex<new_R, b>::value new_row;
    typedef typename SetAtIndex<new_C, prev_cell, new_row>::list changed_new_row;
    
    typedef typename Conditional<(new_R == R), changed_new_row, prev_row>::value row_to_change;
    typedef typename SetAtIndex<C, BoardCell<EMPTY, UP, 0>, row_to_change>::list changed_prev_row;

    typedef typename SetAtIndex<R, changed_prev_row, b>::list true_list;
    typedef typename SetAtIndex<new_R, changed_new_row, b>::list inner_false_list;
    typedef typename SetAtIndex<R, changed_prev_row, inner_false_list>::list false_list;
    typedef typename Conditional<(new_R == R), true_list, false_list>::value new_b;


public:

    static_assert(R >= 0 && R < GB::width, "R out of bounds");
    static_assert(C >= 0 && C < GB::length, "C out of bounds");
    static_assert(getCellType() != EMPTY, "Selected cell type is EMPTY");
    static_assert(
        ((getDirection() == UP || getDirection() == DOWN) && (D == UP || D == DOWN)) ||
        ((getDirection() == LEFT || getDirection() == RIGHT) && (D == LEFT || D == RIGHT)),
        "Selected cell direction is not valid");
    static_assert(getNextCellType() == EMPTY, "Move is not valid");

    typedef typename MoveVehicleAux<GameBoard<new_b>, next_R, next_C, D, A, L - 1>::board board;
};

template <typename GB, int R, int C, Direction D, int A>
struct MoveVehicleAux<GB, R, C, D, A, 0>
{
private:
    constexpr static CellType getCellType()
    {
        typedef typename GB::board b;
        typedef typename GetAtIndex<R, b>::value b1;
        typedef typename GetAtIndex<C, b1>::value cell;
        return cell::type;
    }

    constexpr static Direction getDirection()
    {
        typedef typename GB::board b;
        typedef typename GetAtIndex<C, b>::value b1;
        typedef typename GetAtIndex<R, b1>::value cell;
        return cell::direction;
    }

public:
    static_assert(R >= 0 && R < GB::width, "R out of bounds");
    static_assert(C >= 0 && C < GB::length, "C out of bounds");
    static_assert(getCellType() != EMPTY, "Selected cell type is EMPTY");
    static_assert(
        ((getDirection() == UP || getDirection() == DOWN) && (D == UP || D == DOWN)) ||
        ((getDirection() == LEFT || getDirection() == RIGHT) && (D == LEFT || D == RIGHT)),
        "Selected cell direction is not valid");

    typedef GB board;
};

/* MoveVehicle */
template <typename GB, int R, int C, Direction D, int A>
struct MoveVehicle
{
private:

    typedef typename GB::board b;
    typedef typename GetAtIndex<R, b>::value b1;
    typedef typename GetAtIndex<C, b1>::value cell;

    constexpr static int row = GetVehicle<GB, cell::type, 0, 0>::row;
    constexpr static int column = GetVehicle<GB, cell::type, 0, 0>::column;

public:
    typedef typename MoveVehicleAux<GameBoard<GB>, row, column, D, A, cell::length>::board board;
};


#endif