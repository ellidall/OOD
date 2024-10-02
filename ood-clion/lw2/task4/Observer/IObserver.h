#pragma once

#include "../Observable/Observable.h"

template <typename T>
class Observable;

template<typename T>
class IObserver
{
public:
    virtual void Update(const T& data, const Observable<T>* observable) = 0;
    virtual ~IObserver() = default;
};
