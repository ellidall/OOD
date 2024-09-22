#pragma once

#include <iostream>
#include <functional>

class Duck
{
public:
	Duck(
        std::function<void()> flyBehavior,
        std::function<void()> quackBehavior,
        std::function<void()> danceBehavior
	): m_flyBehavior(std::move(flyBehavior)),
       m_quackBehavior(std::move(quackBehavior)),
       m_danceBehavior(std::move(danceBehavior)),
       m_flightCount(0)
    {}

	virtual ~Duck() = default;
	virtual void Display() const = 0;

	void Quack() const
	{
		m_quackBehavior();
	}

	void Swim() const
	{
		std::cout << "I'm swimming" << std::endl;
	}

	void Fly()
	{
        m_flyBehavior();
        m_flightCount++;
	}

	void Dance() const
	{
		m_danceBehavior();
	}

    void SetFlyBehavior(std::function<void()> flyFunction)
    {
        m_flyBehavior = std::move(flyFunction);
    }

    void SetDanceBehavior(std::function<void()> danceFunction)
    {
        m_quackBehavior = std::move(danceFunction);
    }

    void SetQuackBehavior(std::function<void()> quackFunction)
    {
        m_danceBehavior = std::move(quackFunction);
    }

	[[nodiscard]] int GetFlightCount() const
	{
		return m_flightCount;
	}

private:
    std::function<void()> m_flyBehavior;
    std::function<void()> m_quackBehavior;
    std::function<void()> m_danceBehavior;
    int m_flightCount = 0;
};
