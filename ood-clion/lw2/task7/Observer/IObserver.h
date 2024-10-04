#pragma once

#include "Data/Event.h"

template <typename T, typename EventType>
class IObservable;

template<typename T, typename EventType>
class IObserver
{
public:
    virtual void Update(T const& data, EventType event) = 0;
    virtual ~IObserver() = default;
};

template<typename T, typename EventType>
class IObservable
{
public:
    virtual ~IObservable() = default;
    virtual void RegisterObserver(IObserver<T, EventType> & observer, EventType event) = 0;
    virtual void RemoveObserver(IObserver<T, EventType> & observer, EventType event) = 0;
    virtual void NotifyObservers(Event event) = 0;
};
