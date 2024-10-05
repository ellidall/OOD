#pragma once

#include <unordered_set>
#include <map>
#include "IObserver.h"

template<typename T, typename EventType>
class Observable : public IObservable<T, EventType>
{
public:
    using ObserverType = IObserver<T, EventType>;

    void RegisterObserver(ObserverType& observer, EventType event) override
    {
        // обработать исключение при вставке
        m_observers[event].insert(&observer);
    }

    void RemoveObserver(ObserverType& observer, EventType event) override
    {
        auto it = m_observers.find(event);
        if (it != m_observers.end())
        {
            it->second.erase(&observer);
        }
    }

protected:
    void NotifyObservers(EventType event) override
    {
        T data = GetChangedData();

        auto it = m_observers.find(event);
        if (it != m_observers.end())
        {
            auto observersCopy = it->second;
            for (auto& observer : observersCopy)
            {
                observer->Update(data, event);
            }
        }
    }

    virtual T GetChangedData() const = 0;

private:
    std::map<EventType, std::unordered_set<ObserverType*>> m_observers;
};
