#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../SimUDuck/FlyStrategy/IFlyBehavior.h"
#include "../SimUDuck/QuackStrategy/IQuackBehavior.h"
#include "../SimUDuck/QuackStrategy/MuteQuackBehavior.h"
#include "../SimUDuck/FlyStrategy/FlyNoWay.h"
#include "../SimUDuck/FlyStrategy/FlyWithWings.h"
#include "../SimUDuck/DanceStrategy/NoDance.h."
#include "../SimUDuck/DanceStrategy/MinuetDance.h"
#include "../SimUDuck/DanceStrategy/WaltzDance.h"
#include "../SimUDuck/Duck.h"
#include <memory>

class MockFlyBehavior : public IFlyBehavior
{
public:
    MOCK_METHOD(void, Fly, (), (override));
};

class MockQuackBehavior : public IQuackBehavior
{
public:
    MOCK_METHOD(void, Quack, (), (override));
};

class MockDanceBehavior : public IDanceBehavior
{
public:
    MOCK_METHOD(void, Dance, (), (override));
};

class MockDuck : public Duck
{
public:
    MockDuck(std::unique_ptr<IFlyBehavior>&& flyBehavior,
             std::unique_ptr<IQuackBehavior>&& quackBehavior,
             std::unique_ptr<IDanceBehavior>&& danceBehavior)
            : Duck(std::move(flyBehavior), std::move(quackBehavior), std::move(danceBehavior))
    {
    }

    void Display() const override
    {
        MockDisplay();
    }

    MOCK_METHOD(void, MockDisplay, (), (const));
};

TEST(DuckTest, QuackAfterSecondFlight)
{
    auto mockFly = std::make_unique<MockFlyBehavior>();
    auto mockQuack = std::make_unique<MockQuackBehavior>();
    auto mockDance = std::make_unique<MockDanceBehavior>();

    MockFlyBehavior* flyPtr = mockFly.get();
    MockQuackBehavior* quackPtr = mockQuack.get();

    MockDuck duck(std::move(mockFly), std::move(mockQuack), std::move(mockDance));

    EXPECT_CALL(*flyPtr, Fly()).Times(2);
    EXPECT_CALL(*quackPtr, Quack()).Times(1);

    duck.Fly();
    duck.Fly();
}

class MockMuteQuackBehavior : public MuteQuackBehavior
{
public:
    MOCK_METHOD(void, Quack, (), (override));
};

TEST(DuckTest, CannotQuack)
{
    auto mockFly = std::make_unique<MockFlyBehavior>();
    auto mockDance = std::make_unique<MockDanceBehavior>();
    auto mockMuteQuack = std::make_unique<MockMuteQuackBehavior>();

    MockFlyBehavior* flyPtr = mockFly.get();
    MockMuteQuackBehavior* muteQuackPtr = mockMuteQuack.get();

    MockDuck duck(std::move(mockFly), std::move(mockMuteQuack), std::move(mockDance));

    EXPECT_CALL(*flyPtr, Fly()).Times(4);
    EXPECT_CALL(*muteQuackPtr, Quack()).Times(0);

    duck.Fly();
    duck.Fly();
    duck.Fly();
    duck.Fly();
}

class MockFlyNoWay : public FlyNoWay
{
public:
    MOCK_METHOD(void, Fly, (), (override));
};

class MockFlyWithWings : public FlyWithWings
{
public:
    MOCK_METHOD(void, Fly, (), (override));
};

TEST(DuckTest, CannotFly)
{
    auto mockFlyNoWay = std::make_unique<MockFlyNoWay>();
    auto mockDance = std::make_unique<MockDanceBehavior>();
    auto mockQuack = std::make_unique<MockQuackBehavior>();

    MockFlyNoWay* flyPtr = mockFlyNoWay.get();
    MockQuackBehavior* quackPtr = mockQuack.get();

    MockDuck duck(std::move(mockFlyNoWay), std::move(mockQuack), std::move(mockDance));

    EXPECT_CALL(*flyPtr, Fly()).Times(4);
    EXPECT_CALL(*quackPtr, Quack()).Times(0);

    duck.Fly();
    duck.Fly();
    duck.Fly();
    duck.Fly();
}

TEST(DuckTest, FlightsCount)
{
    MockDuck duck(
               std::make_unique<MockFlyNoWay>(),
            std::make_unique<MockQuackBehavior>(),
            std::make_unique<MockDanceBehavior>()
    );


    duck.Fly();
    duck.Fly();
    EXPECT_TRUE(duck.GetFlightCount() == 0);

    duck.SetFlyBehavior(std::make_unique<MockFlyWithWings>());
    duck.Fly();
    duck.Fly();
    EXPECT_TRUE(duck.GetFlightCount() == 2);
}

class MockNoDance : public NoDance
{
public:
    MOCK_METHOD(void, Dance, (), (override));
};

class MockMinuetDance : public MinuetDance
{
public:
    MOCK_METHOD(void, Dance, (), (override));
};

class MockWaltzDance : public WaltzDance
{
public:
    MOCK_METHOD(void, Dance, (), (override));
};

TEST(DanceTest, Strategy)
{
    auto mockFlyNoWay = std::make_unique<MockFlyNoWay>();
    auto mockQuack = std::make_unique<MockQuackBehavior>();

    auto mockNoDance = std::make_unique<MockNoDance>();
    auto mockMinuetDance = std::make_unique<MockMinuetDance>();
    auto mockWaltzDance = std::make_unique<MockWaltzDance>();

    MockNoDance* noDancePtr = mockNoDance.get();
    MockMinuetDance* minuetDancePtr = mockMinuetDance.get();
    MockWaltzDance* waltzDancePtr = mockWaltzDance.get();

    MockDuck duck(std::move(mockFlyNoWay), std::move(mockQuack), std::move(mockNoDance));

    EXPECT_CALL(*noDancePtr, Dance()).Times(1);
    duck.Dance();

    EXPECT_CALL(*minuetDancePtr, Dance()).Times(1);
    duck.SetDanceBehavior(std::move(mockMinuetDance));
    duck.Dance();

    EXPECT_CALL(*waltzDancePtr, Dance()).Times(1);
    duck.SetDanceBehavior(std::move(mockWaltzDance));
    duck.Dance();

    EXPECT_THROW(duck.SetDanceBehavior(nullptr), ActionCannotBeNullException);
}
