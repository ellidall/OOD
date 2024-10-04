#pragma once

template <typename T>
class IObservable;

//перенеси в Observable
template<typename T>
class IObserver
{
public:
    // Не зависеть от конкретного Observable
    virtual void Update(const T& data, const IObservable<T>* observable) = 0;
    virtual ~IObserver() = default;
};

template<typename T>
class IObservable
{
public:
    virtual ~IObservable() = default;
    virtual void RegisterObserver(IObserver<T>& observer, int priority) = 0;
    virtual void NotifyObservers() = 0;
    virtual void RemoveObserver(IObserver<T>& observer) = 0;
};
