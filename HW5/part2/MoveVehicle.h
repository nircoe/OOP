#ifndef MOVE_VEHICLE_H
#define MOVE_VEHICLE_H

#include "CellType.h"
#include "Direction.h"
#include "GameBoard.h"

/* Move */
template <CellType T, Direction D, int N>
struct Move
{
private:
    template <CellType T2>
    struct GetCellType
    {
        constexpr static CellType type()
        {
            static_assert(T2 != Empty, "CellType is Empty");
            return T2;
        };
    };

    template <CellType T2, Direction D2>
    struct GetDirection
    {
        constexpr static Direction direction()
        {
            static_assert(T2 != Empty, "CellType is Empty");
            return D2;
        };
    };

    template <CellType T2, int N2>
    struct GetAmount
    {
        constexpr static int amount()
        {
            static_assert(T2 != Empty, "CellType is Empty");
            return N2;
        };
    };

public:
    constexpr static CellType type = GetCellType<T>::type();
    constexpr static Direction direction = GetDirection<T, D>::direction();
    constexpr static int amount = GetAmount<T, N>::amount();
};

/* MoveVehicle */
template <typename G, int R, int C, Direction D, int A>
struct MoveVehicle
{
    constexpr static CellType type = X;
};

#endif