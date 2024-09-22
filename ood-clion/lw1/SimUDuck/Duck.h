#pragma once

#include "FlyStrategy/IFlyBehavior.h"
#include "FlyStrategy/FlyNoWay.h"
#include "QuackStrategy/IQuackBehavior.h"
#include "QuackStrategy/MuteQuackBehavior.h"
#include "DanceStrategy/IDanceBehavior.h"
#include "Exception/ActionCannotBeNullException.h"
#include <cassert>
#include <iostream>
#include <memory>

class Duck
{
public:
	Duck(
		std::unique_ptr<IFlyBehavior>&& flyBehavior,
		std::unique_ptr<IQuackBehavior>&& quackBehavior,
		std::unique_ptr<IDanceBehavior>&& danceBehavior
	)
	{	
		SetFlyBehavior(std::move(flyBehavior));
		SetQuackBehavior(std::move(quackBehavior));
		SetDanceBehavior(std::move(danceBehavior));
	}

	virtual ~Duck() = default;
	virtual void Display() const = 0;

	void Quack() const
	{
		m_quackBehavior->Quack();
	}

	void Swim() const
	{
		std::cout << "I'm swimming" << std::endl;
	}

	void Fly()
	{
        m_flyBehavior->Fly();
		if (dynamic_cast<FlyNoWay*>(m_flyBehavior.get()) == nullptr)
		{
            m_flightCount++;
			if (m_flightCount != 0 && m_flightCount % 2 == 0 && dynamic_cast<MuteQuackBehavior*>(m_quackBehavior.get()) == nullptr)
			{
				m_quackBehavior->Quack();
			}
		}
	}

	void Dance() const
	{
		m_danceBehavior->Dance();
	}

	void SetFlyBehavior(std::unique_ptr<IFlyBehavior>&& flyBehavior)
	{
		if (flyBehavior == nullptr)
		{
			throw ActionCannotBeNullException();
		}
		m_flightCount = 0;
		m_flyBehavior = std::move(flyBehavior);
	}

	void SetQuackBehavior(std::unique_ptr<IQuackBehavior>&& quackBehavior)
	{
		if (quackBehavior == nullptr)
		{
			throw ActionCannotBeNullException();
		}
		m_quackBehavior = std::move(quackBehavior);
	}

	void SetDanceBehavior(std::unique_ptr<IDanceBehavior>&& danceBehavior)
	{
		if (danceBehavior == nullptr)
		{
			throw ActionCannotBeNullException();
		}
		m_danceBehavior = std::move(danceBehavior);
	}

	[[nodiscard]] int GetFlightCount() const
	{
		return m_flightCount;
	}

private:
	std::unique_ptr<IFlyBehavior> m_flyBehavior;
	std::unique_ptr<IQuackBehavior> m_quackBehavior;
	std::unique_ptr<IDanceBehavior> m_danceBehavior;
	int m_flightCount = 0;
};
