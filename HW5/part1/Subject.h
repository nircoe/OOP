#ifndef SUBJECT_H
#define SUBJECT_H

#include <iostream>

#include "OOP5EventException.h"
#include "Observer.h"

template<typename T>
class Observer;

template<typename T>
class Subject
{
    Observer<T>* head;

    void notify(const T& param)
    {
        for (Observer<T> *itr = head; itr != nullptr; itr = itr->next)
        {
            itr->handleEvent(param);
        }
    }

    void addObserver(Observer<T>& observer)
    {
        Observer<T> *last = nullptr;
        for (Observer<T> *itr = head; itr != nullptr; itr = itr->next)
        {
            last = itr;
            if(itr == &observer)
                throw ObserverAlreadyKnownToSubject();
        }
        if(last == nullptr)
        {
            head = &observer; // next and prev already nullptr since constructor
        }
        else
        {
            last->next = &observer;
            observer.prev = last;
            observer.next = nullptr;
        }
    }

    void removeObserver(Observer<T>& observer)
    {
        for (Observer<T> *itr = head; itr != nullptr; itr = itr->next)
        {
            if(itr == &observer)
            {
                if(itr->prev)
                    itr->prev->next = itr->next;
                else // itr is head
                    head = itr->next;
                if(itr->next)
                    itr->next->prev = itr->prev;
                return;
            }
        }
        throw ObserverUnknownToSubject();
    }

    public:
        Subject() : head(nullptr){};

        Subject<T> &operator+=(Observer<T>& observer)
        {
            this->addObserver(observer);
            return *this;
        }

        Subject<T> &operator-=(Observer<T>& observer)
        {
            this->removeObserver(observer);
            return *this;
        }

        Subject<T> &operator()(const T& param)
        {
            this->notify(param);
            return *this;
        }
};


#endif