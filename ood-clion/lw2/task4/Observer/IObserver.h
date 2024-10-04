#pragma once

#include "../Observable/Observable.h"

template <typename T>
class Observable;

//перенеси в Observable
template<typename T>
class IObserver
{
public:
    // Не зависеть от конкретного Observable
    virtual void Update(const T& data, const Observable<T>* observable) = 0;
    virtual ~IObserver() = default;
};
