//#define MOVE_VEHICLE_H

#include "CellType.h"
#include "Direction.h"
#include "GameBoard.h"
#include "TransposeList.h"
#include "BoardCell.h"
#include "Utilities.h"

/*Get Vehicle Location*/
/* template <typename GameBoard, CellType type, int R, int C>
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
}; */


/* Move */
template <CellType T, Direction D, int N>
struct Move
{
    static_assert(T != EMPTY, "CellType is EMPTY");
    constexpr static CellType type = T;
    constexpr static Direction direction = D;
    constexpr static int amount = N;
};

/* template <typename GB, int R, int C, Direction D, int A, int L>
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
}; */

template <typename GB, int R, int C, Direction D>
struct NextCell;

template <typename GB, int R, int C>
struct NextCell<GB, R, C, RIGHT>
{
private:
    typedef typename GB::board b;
    typedef typename GetAtIndex<R, b>::value b1;
    typedef typename GetAtIndex<C + 1, b1>::value nextCell;
public:
    typedef nextCell value;
    constexpr static int nextR = R;
    constexpr static int nextC = C + 1;
};

template <typename GB, int R, int C>
struct NextCell<GB, R, C, LEFT>
{
private:
    typedef typename GB::board b;
    typedef typename GetAtIndex<R, b>::value b1;
    typedef typename GetAtIndex<C - 1, b1>::value nextCell;
public:
    typedef nextCell value;
    constexpr static int nextR = R;
    constexpr static int nextC = C - 1;
};

template <typename GB, int R, int C>
struct NextCell<GB, R, C, UP>
{
private:
    typedef typename GB::board b;
    typedef typename GetAtIndex<R - 1, b>::value b1;
    typedef typename GetAtIndex<C, b1>::value nextCell;
public:
    typedef nextCell value;
    constexpr static int nextR = R - 1;
    constexpr static int nextC = C;
};

template <typename GB, int R, int C>
struct NextCell<GB, R, C, DOWN>
{
private:
    typedef typename GB::board b;
    typedef typename GetAtIndex<R + 1, b>::value b1;
    typedef typename GetAtIndex<C, b1>::value nextCell;
public:
    typedef nextCell value;
    constexpr static int nextR = R + 1;
    constexpr static int nextC = C;
};

template <int A, typename GB, int R, int C, Direction D>
struct MoveCells;

template <int A, typename GB, int R, int C>
struct MoveCells<A, GB, R, C, LEFT>
{
private:
    typedef typename GB::board b;
    typedef typename GetAtIndex<R, b>::value b1;
    typedef typename GetAtIndex<C, b1>::value cell;

    typedef typename SetAtIndex<C - 1, cell, b1>::list newRow;
    typedef typename SetAtIndex<R, newRow, b>::list newBoard;

    typedef GameBoard<newBoard> newGameBoard;
public:
    typedef typename MoveCells<A - 1, newGameBoard, R, C + 1, LEFT>::value value;
};

template <typename GB, int R, int C>
struct MoveCells <0, GB, R, C, LEFT>
{
private:
    typedef typename GB::board b;
    typedef typename GetAtIndex<R, b>::value b1;
    typedef BoardCell<EMPTY, RIGHT, 0> emptyCell;

    typedef typename SetAtIndex<C - 1, emptyCell, b1>::list newRow;
    typedef typename SetAtIndex<R, newRow, b>::list newBoard;

    typedef GameBoard<newBoard> newGameBoard;
public:
    typedef newGameBoard value;
};

template <int A, typename GB, int R, int C>
struct MoveCells<A, GB, R, C, RIGHT>
{
private:
    typedef typename GB::board b;
    typedef typename GetAtIndex<R, b>::value b1;
    typedef typename GetAtIndex<C, b1>::value cell;

    typedef typename SetAtIndex<C + 1, cell, b1>::list newRow;
    typedef typename SetAtIndex<R, newRow, b>::list newBoard;

    typedef GameBoard<newBoard> newGameBoard;
public:
    typedef typename MoveCells<A - 1, newGameBoard, R, C - 1, RIGHT>::value value;
};

template <typename GB, int R, int C>
struct MoveCells <0, GB, R, C, RIGHT>
{
private:
    typedef typename GB::board b;
    typedef typename GetAtIndex<R, b>::value b1;
    typedef BoardCell<EMPTY, RIGHT, 0> emptyCell;

    typedef typename SetAtIndex<C + 1, emptyCell, b1>::list newRow;
    typedef typename SetAtIndex<R, newRow, b>::list newBoard;

    typedef GameBoard<newBoard> newGameBoard;
public:
    typedef newGameBoard value;
};

template <int A, typename GB, int R, int C>
struct MoveCells<A, GB, R, C, DOWN>
{
private:
    typedef typename GB::board bTemp;
    typedef typename Transpose<bTemp>::matrix b;
    typedef typename GetAtIndex<C, b>::value b1;
    typedef typename GetAtIndex<R, b1>::value cell;

    typedef typename SetAtIndex<R + 1, cell, b1>::list newRow;
    typedef typename SetAtIndex<C, newRow, b>::list newBoard;
    typedef typename Transpose<newBoard>::matrix newBoard2;

    typedef GameBoard<newBoard2> newGameBoard;
public:
    typedef typename MoveCells<A - 1, newGameBoard, R - 1, C, DOWN>::value value;
};

template <typename GB, int R, int C>
struct MoveCells <0, GB, R, C, DOWN>
{
private:
    typedef typename GB::board bTemp;
    typedef typename Transpose<bTemp>::matrix b;
    typedef typename GetAtIndex<C, b>::value b1;
    typedef BoardCell<EMPTY, RIGHT, 0> emptyCell;

    typedef typename SetAtIndex<R + 1, emptyCell, b1>::list newRow;
    typedef typename SetAtIndex<C, newRow, b>::list newBoard;
    typedef typename Transpose<newBoard>::matrix newBoard2;

    typedef GameBoard<newBoard2> newGameBoard;
public:
    typedef newGameBoard value;
};

template <int A, typename GB, int R, int C>
struct MoveCells<A, GB, R, C, UP>
{
private:
    typedef typename GB::board bTemp;
    typedef typename Transpose<bTemp>::matrix b;
    typedef typename GetAtIndex<C, b>::value b1;
    typedef typename GetAtIndex<R, b1>::value cell;

    typedef typename SetAtIndex<R - 1, cell, b1>::list newRow;
    typedef typename SetAtIndex<C, newRow, b>::list newBoard;
    typedef typename Transpose<newBoard>::matrix newBoard2;

    typedef GameBoard<newBoard2> newGameBoard;
public:
    typedef typename MoveCells<A - 1, newGameBoard, R + 1, C, UP>::value value;
};

template <typename GB, int R, int C>
struct MoveCells <0, GB, R, C, UP>
{
private:
    typedef typename GB::board bTemp;
    typedef typename Transpose<bTemp>::matrix b;
    typedef typename GetAtIndex<C, b>::value b1;
    typedef BoardCell<EMPTY, RIGHT, 0> emptyCell;

    typedef typename SetAtIndex<R - 1, emptyCell, b1>::list newRow;
    typedef typename SetAtIndex<C, newRow, b>::list newBoard;
    typedef typename Transpose<newBoard>::matrix newBoard2;

    typedef GameBoard<newBoard2> newGameBoard;
public:
    typedef newGameBoard value;
};

template <typename GB, int R, int C, Direction D, int A>
struct MoveVehicle
{
private:
    constexpr static int width = GB::width;
    constexpr static int length = GB::length;

    typedef typename GB::board b;
    typedef typename GetAtIndex<R, b>::value b1;
    typedef typename GetAtIndex<C, b1>::value cell;

    typedef NextCell<GB, R, C, D> nextCell;
    typedef typename nextCell::value nextCellValue;
    typedef typename MoveCells<ConditionalInteger<
        nextCellValue::type == cell::type,
        0, // No move if same type
        cell::length>::value, GB, R, C, D>::value afterMove;
    typedef typename Conditional<
        nextCellValue::type == cell::type,
        MoveVehicle<GB, nextCell::nextR, nextCell::nextC, D, A>,
        MoveVehicle<afterMove, nextCell::nextR, nextCell::nextC, D, A - 1>
    >::value res;

public:
    static_assert(C >= 0 && C < GB::width, "C out of bounds");
    static_assert(R >= 0 && R < GB::length, "R out of bounds");
    static_assert(cell::type != EMPTY, "Selected cell type is EMPTY");
    static_assert(
        ((cell::direction == UP || cell::direction == DOWN) && (D == UP || D == DOWN)) ||
        ((cell::direction == LEFT || cell::direction == RIGHT) && (D == LEFT || D == RIGHT)),
        "Selected cell direction is not valid");
    static_assert(
        nextCellValue::type == EMPTY || nextCellValue::type == cell::type,
        "Next cell is not empty");

    typedef typename res::board board;
};


template <typename GB, int R, int C, Direction D>
struct MoveVehicle<GB, R, C, D, 0>
{
private:
    typedef typename GB::board b;
    typedef typename GetAtIndex<R, b>::value b1;
    typedef typename GetAtIndex<C, b1>::value cell;

public:
    static_assert(C >= 0 && C < GB::width, "C out of bounds");
    static_assert(R >= 0 && R < GB::length, "R out of bounds");
    static_assert(cell::type != EMPTY, "Selected cell type is EMPTY");
    static_assert(
        ((cell::direction == UP || cell::direction == DOWN) && (D == UP || D == DOWN)) ||
        ((cell::direction == LEFT || cell::direction == RIGHT) && (D == LEFT || D == RIGHT)),
        "Selected cell direction is not valid");

    typedef GB board;
};


//#endif