//#define MOVE_VEHICLE_H

#include "CellType.h"
#include "Direction.h"
#include "GameBoard.h"
#include "TransposeList.h"
#include "BoardCell.h"
#include "Utilities.h"

/* FindCar */
template <typename GameBoard, CellType T, int R, int C>
struct FindCar
{
private:
    typedef typename GameBoard::board b;
    typedef typename GetAtIndex<R, b>::value b1;
    typedef typename GetAtIndex<C, b1>::value cell;
    constexpr static int nextR = (C - 1 < 0) ? R - 1 : R;
    constexpr static int nextC = (C - 1 < 0) ? GameBoard::width - 1 : C - 1;
    constexpr static bool isCar = cell::type == T;

public:
    constexpr static int row = ConditionalInteger<isCar, R, FindCar<GameBoard, T, nextR, nextC>::row>::value;
    constexpr static int column = ConditionalInteger<isCar, C, FindCar<GameBoard, T, nextR, nextC>::column>::value;
};

template <typename GameBoard, CellType T>
struct FindCar<GameBoard, T, 0, 0>
{
private:
    typedef typename GameBoard::board b;
    typedef typename GetAtIndex<0, b>::value b1;
    typedef typename GetAtIndex<0, b1>::value cell;
    constexpr static bool isCar = cell::type == T;

public:
    constexpr static int row = ConditionalInteger<isCar, 0, -1>::value;
    constexpr static int column = ConditionalInteger<isCar, 0, -1>::value;
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

/* NextCell */
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

/* MoveCells */
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

/* MoveVehicle */
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