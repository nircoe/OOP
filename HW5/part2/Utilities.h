#ifndef UTILITIES_H
#define UTILITIES_H

/* Conditional */
template <bool B, typename U, typename T>
struct Conditional;

template <typename U, typename T>
struct Conditional<true, U, T>
{
    typedef U value;
};

template <typename U, typename T>
struct Conditional<false, U, T>
{
    typedef T value;
};

/* ConditionalInteger */
template <bool B, int U, int T>
struct ConditionalInteger;

template <int U, int T>
struct ConditionalInteger<true, U, T>
{
    constexpr static int value = U;
};

template <int U, int T>
struct ConditionalInteger<false, U, T>
{
    constexpr static int value = T;
};

#endif