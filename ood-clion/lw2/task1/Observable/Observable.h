#pragma once

#include <set>
#include "../Observer/IObserver.h"
#include "IObservable.h"

template<class T>
class Observable : public IObservable<T>
{
public:
    using ObserverType = IObserver<T>;

    void RegisterObserver(ObserverType& observer) override
    {
        m_observers.insert(&observer);
    }

    void RemoveObserver(ObserverType& observer) override
    {
        m_observers.erase(&observer);
    }

protected:
    void NotifyObservers() override
    {
        T data = GetChangedData();
        for (auto& observer: m_observers)
        {
            observer->Update(data);
        }
    }

    virtual T GetChangedData() const = 0;

private:
    std::set<ObserverType*> m_observers;
};
