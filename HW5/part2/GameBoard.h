#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "List.h"

template <typename B, int W, int L>
struct GameBoard;

template <typename... B, int W, int L>
struct GameBoard<List<B...>, W, L>
{
    typedef List<B...> board;
    constexpr static int width = W;
    constexpr static int length = L;
};


#endif