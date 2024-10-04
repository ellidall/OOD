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
    // почему при удалении текущено объекта происходят проблемы, а при удалении другого нет
    {
        T data = GetChangedData();
        auto copyOfObservers = m_observers;
        for (auto& observer: copyOfObservers)
        {
            observer->Update(data);
        }
    }

    virtual T GetChangedData() const = 0;

private:
    std::set<ObserverType*> m_observers;
};
