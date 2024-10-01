#pragma once

#include <unordered_set>
#include <map>
#include "../Observer/IObserver.h"
#include "IObservable.h"

template<class T>
class Observable : public IObservable<T>
{
public:
    typedef IObserver<T> ObserverType;

    void RegisterObserver(ObserverType& observer, int priority) override
    {
        auto result = m_priorityToObservers.insert({priority, {}});
        result.first->second.insert(&observer);
        m_observerToPriority[&observer] = priority;
    }

    void RemoveObserver(ObserverType& observer) override
    {
        auto it = m_observerToPriority.find(&observer);
        if (it != m_observerToPriority.end())
        {
            int priority = it->second;
            m_priorityToObservers[priority].erase(&observer);

            if (m_priorityToObservers[priority].empty())
            {
                m_priorityToObservers.erase(priority);
            }

            m_observerToPriority.erase(it);
        }
    }

protected:
    void NotifyObservers()
    {
        T data = GetChangedData();
        auto copyOfObserver = m_priorityToObservers;
        for (auto it = copyOfObserver.rbegin(); it != copyOfObserver.rend(); ++it)
        {
            for (auto& observer : it->second)
            {
                observer->Update(data);
            }
        }
    }

    virtual T GetChangedData() const = 0;

private:
    std::map<int, std::unordered_set<ObserverType*>> m_priorityToObservers;
    std::map<ObserverType*, int> m_observerToPriority;
};
