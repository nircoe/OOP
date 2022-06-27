#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "List.h"
#include "CellType.h"
#include "TransposeList.h"

template <int I, typename L>
struct Length
{
    constexpr static int value = I;
};

template <int I, typename L, typename... LL>
struct Length<I, List<L, LL...>>
{
    constexpr static int value = Length<I + 1, List<LL...>>::value;
};

template <typename B>
struct GameBoard;

template <typename... B>
struct GameBoard<List<B...>>
{
private:
    typedef typename Transpose<List<B...>>::matrix transposed;
public:
    typedef List<B...> board;
    constexpr static int length = Length<0, List<B...>>::value;
    constexpr static int width = Length<0, transposed>::value;
};

#endif