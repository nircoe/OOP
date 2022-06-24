#ifndef LIST_H
#define LIST_H

/* List */
template <typename... TT>
struct List;

template <>
struct List<>
{
    constexpr static int size = 0;
};

template <typename T, typename... TT>
struct List<T, TT...>
{
    constexpr static int size = sizeof...(TT) + 1;
    typedef T head;
    typedef List<TT...> next;
};

/* PrependList */
template <typename T, typename L>
struct PrependList;

template <typename T, typename... L>
struct PrependList<T, List<L...>>
{
    typedef List<T, L...> list;
};

/* GetAtIndex */
template <int N, typename T>
struct GetAtIndex;

template <int N, typename T, typename... TT>
struct GetAtIndex<N, List<T, TT...>>
{
    typedef typename GetAtIndex<N - 1, List<TT...>>::value value;
};

template <typename T, typename... TT>
struct GetAtIndex<0, List<T, TT...>>
{
    typedef T value;
};

/* SetAtIndex */
template <int N, typename U, typename T>
struct SetAtIndex;

template <int N, typename U, typename T, typename... TT>
struct SetAtIndex<N, U, List<T, TT...>>
{
    typedef typename PrependList<T, typename SetAtIndex<N - 1, U, List<TT...>>::list>::list list;
};

template <typename U, typename T, typename... TT>
struct SetAtIndex<0, U, List<T, TT...>>
{
    typedef typename PrependList<U, List<TT...>>::list list;
};

/* Help functions */
template<int N, typename T>
struct GetNth;

template<int N, typename T, typename... TT >
struct GetNth<N, List<T, TT...>>
{
    typedef typename GetNth<N-1, List<TT... >>::Head Head;
};

template<typename T, typename... TT>
struct GetNth<0, List<T, TT...>>
{
    typedef T Head;
};

template <bool g, typename T, typename E>
struct IF
{
    typedef T RET;
};

template <typename T, typename E>
struct IF<false, T, E>
{
    typedef E RET;
};

#endif