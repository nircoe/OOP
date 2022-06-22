#ifndef OBSERVER_H
#define OBSERVER_H

template <typename T>
class Subject;

template<typename T>
class Observer
{
    Observer<T> *next;
    Observer<T> *prev;

public:
    Observer() : next(nullptr), prev(nullptr){};

    virtual void handleEvent(const T &) = 0;

    friend class Subject<T>;
};

#endif