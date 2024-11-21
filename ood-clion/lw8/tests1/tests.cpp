#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../task1/GumballMachine.h"

class MockGumballMachine : public with_state::IGumballMachine
{
public:
    MOCK_METHOD(void, ReleaseBall, (), (override));
    MOCK_METHOD(unsigned, GetBallCount, (), (const, override));
    MOCK_METHOD(void, SetSoldOutState, (), (override));
    MOCK_METHOD(void, SetNoQuarterState, (), (override));
    MOCK_METHOD(void, SetSoldState, (), (override));
    MOCK_METHOD(void, SetHasQuarterState, (), (override));
};

using namespace with_state;
using ::testing::_;
using ::testing::Return;
using ::testing::Exactly;

// SoldState
TEST(SoldStateTest, DispenseWhenBallCountIsZero)
{
    MockGumballMachine mockMachine;
    SoldState state(mockMachine);

    EXPECT_CALL(mockMachine, ReleaseBall()).Times(1);
    EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(Return(0));
    EXPECT_CALL(mockMachine, SetSoldOutState()).Times(1);

    state.Dispense();
}

TEST(SoldStateTest, DispenseWhenBallCountIsPositive)
{
    MockGumballMachine mockMachine;
    SoldState state(mockMachine);

    EXPECT_CALL(mockMachine, ReleaseBall()).Times(1);
    EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(Return(1));
    EXPECT_CALL(mockMachine, SetNoQuarterState()).Times(1);

    state.Dispense();
}

TEST(SoldStateTest, InsertQuarter)
{
    MockGumballMachine mockMachine;
    SoldState state(mockMachine);

    testing::internal::CaptureStdout();
    state.InsertQuarter();

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Please wait, we're already giving you a gumball\n");
}

TEST(SoldStateTest, EjectQuarter)
{
    MockGumballMachine mockMachine;
    SoldState state(mockMachine);

    testing::internal::CaptureStdout();
    state.EjectQuarter();

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Sorry you already turned the crank\n");
}

TEST(SoldStateTest, TurnCrank)
{
    MockGumballMachine mockMachine;
    SoldState state(mockMachine);

    testing::internal::CaptureStdout();
    state.TurnCrank();

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Turning twice doesn't get you another gumball\n");
}

TEST(SoldStateTest, ToString)
{
    MockGumballMachine mockMachine;
    SoldState state(mockMachine);

    auto output = state.ToString();

    EXPECT_EQ(output, "delivering a gumball");
}

// SoldOutState
TEST(SoldOutStateTest, InsertQuarter)
{
    MockGumballMachine mockMachine;
    SoldOutState state(mockMachine);

    testing::internal::CaptureStdout();
    state.InsertQuarter();

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "You can't insert a quarter, the machine is sold out\n");
}

TEST(SoldOutStateTest, EjectQuarter)
{
    MockGumballMachine mockMachine;
    SoldOutState state(mockMachine);

    testing::internal::CaptureStdout();
    state.EjectQuarter();

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "You can't eject, you haven't inserted a quarter yet\n");
}

TEST(SoldOutStateTest, TurnCrank)
{
    MockGumballMachine mockMachine;
    SoldOutState state(mockMachine);

    testing::internal::CaptureStdout();
    state.TurnCrank();

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "You turned but there's no gumballs\n");
}

TEST(SoldOutStateTest, Dispense)
{
    MockGumballMachine mockMachine;
    SoldOutState state(mockMachine);

    testing::internal::CaptureStdout();
    state.Dispense();

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "No gumball dispensed\n");
}

TEST(SoldOutStateTest, ToString)
{
    MockGumballMachine mockMachine;
    SoldOutState state(mockMachine);

    auto output = state.ToString();

    EXPECT_EQ(output, "sold out");
}

// HasQuarterState
TEST(HasQuarterStateTest, InsertQuarter)
{
    MockGumballMachine mockMachine;
    HasQuarterState state(mockMachine);

    testing::internal::CaptureStdout();
    state.InsertQuarter();

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "You can't insert another quarter\n");
}

TEST(HasQuarterStateTest, EjectQuarter)
{
    MockGumballMachine mockMachine;
    HasQuarterState state(mockMachine);

    testing::internal::CaptureStdout();
    EXPECT_CALL(mockMachine, SetNoQuarterState()).Times(1);
    state.EjectQuarter();

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Quarter returned\n");
}

TEST(HasQuarterStateTest, TurnCrank)
{
    MockGumballMachine mockMachine;
    HasQuarterState state(mockMachine);

    testing::internal::CaptureStdout();
    EXPECT_CALL(mockMachine, SetSoldState()).Times(1);
    state.TurnCrank();

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "You turned...\n");
}

TEST(HasQuarterStateTest, Dispense)
{
    MockGumballMachine mockMachine;
    HasQuarterState state(mockMachine);

    testing::internal::CaptureStdout();
    state.Dispense();

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "No gumball dispensed\n");
}

TEST(HasQuarterStateTest, ToString)
{
    MockGumballMachine mockMachine;
    HasQuarterState state(mockMachine);

    auto output = state.ToString();

    EXPECT_EQ(output, "waiting for turn of crank");
}

// NoQuarterState
TEST(NoQuarterStateTest, InsertQuarter)
{
    MockGumballMachine mockMachine;
    NoQuarterState state(mockMachine);

    testing::internal::CaptureStdout();
    EXPECT_CALL(mockMachine, SetHasQuarterState()).Times(1);
    state.InsertQuarter();

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "You inserted a quarter\n");
}

TEST(NoQuarterStateTest, EjectQuarter)
{
    MockGumballMachine mockMachine;
    NoQuarterState state(mockMachine);

    testing::internal::CaptureStdout();
    state.EjectQuarter();

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "You haven't inserted a quarter\n");
}

TEST(NoQuarterStateTest, TurnCrank)
{
    MockGumballMachine mockMachine;
    NoQuarterState state(mockMachine);

    testing::internal::CaptureStdout();
    state.TurnCrank();

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "You turned but there's no quarter\n");
}

TEST(NoQuarterStateTest, Dispense)
{
    MockGumballMachine mockMachine;
    NoQuarterState state(mockMachine);

    testing::internal::CaptureStdout();
    state.Dispense();

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "You need to pay first\n");
}

TEST(NoQuarterStateTest, ToString)
{
    MockGumballMachine mockMachine;
    NoQuarterState state(mockMachine);

    auto output = state.ToString();

    EXPECT_EQ(output, "waiting for quarter");
}

// GumballMachine
TEST(GumballMachineTest, InitialState)
{
    GumballMachine machine(5);
    std::string expected = "Mighty Gumball, Inc.\n"
                           "C++-enabled Standing Gumball Model #2016\n"
                           "Inventory: 5 gumballs\n"
                           "Machine is waiting for quarter";
    EXPECT_EQ(machine.ToString(), expected);
}

TEST(GumballMachineTest, InsertQuarterInNoQuarterState)
{
    GumballMachine machine(2);

    testing::internal::CaptureStdout();
    machine.InsertQuarter();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You inserted a quarter\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 2 gumballs\n"
                                  "Machine is waiting for turn of crank");
}

TEST(GumballMachineTest, InsertQuarterInHasQuarterState)
{
    GumballMachine machine(2);
    machine.InsertQuarter();

    testing::internal::CaptureStdout();
    machine.InsertQuarter();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You can't insert another quarter\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 2 gumballs\n"
                                  "Machine is waiting for turn of crank");
}

TEST(GumballMachineTest, InsertQuarterInSoldState)
{
    GumballMachine machine(2);
    machine.InsertQuarter();
    machine.TurnCrank();

    testing::internal::CaptureStdout();
    machine.InsertQuarter();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You inserted a quarter\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 1 gumball\n"
                                  "Machine is waiting for turn of crank");
}

TEST(GumballMachineTest, InsertQuarterInSoldOutState)
{
    GumballMachine machine(0);

    testing::internal::CaptureStdout();
    machine.InsertQuarter();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You can't insert a quarter, the machine is sold out\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 0 gumballs\n"
                                  "Machine is sold out");
}

TEST(GumballMachineTest, EjectQuarterInNoQuarterState)
{
    GumballMachine machine(2);

    testing::internal::CaptureStdout();
    machine.EjectQuarter();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You haven't inserted a quarter\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 2 gumballs\n"
                                  "Machine is waiting for quarter");
}

TEST(GumballMachineTest, EjectQuarterInHasQuarterState)
{
    GumballMachine machine(2);
    machine.InsertQuarter();

    testing::internal::CaptureStdout();
    machine.EjectQuarter();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Quarter returned\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 2 gumballs\n"
                                  "Machine is waiting for quarter");
}

TEST(GumballMachineTest, EjectQuarterInSoldState)
{
    GumballMachine machine(2);
    machine.InsertQuarter();
    machine.TurnCrank();

    testing::internal::CaptureStdout();
    machine.EjectQuarter();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You haven't inserted a quarter\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 1 gumball\n"
                                  "Machine is waiting for quarter");
}

TEST(GumballMachineTest, EjectQuarterInSoldOutState)
{
    GumballMachine machine(0);

    testing::internal::CaptureStdout();
    machine.EjectQuarter();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You can't eject, you haven't inserted a quarter yet\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 0 gumballs\n"
                                  "Machine is sold out");
}

TEST(GumballMachineTest, TurnCrankInNoQuarterState)
{
    GumballMachine machine(2);

    testing::internal::CaptureStdout();
    machine.TurnCrank();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You turned but there's no quarter\nYou need to pay first\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 2 gumballs\n"
                                  "Machine is waiting for quarter");
}

TEST(GumballMachineTest, TurnCrankInHasQuarterState)
{
    GumballMachine machine(2);
    machine.InsertQuarter();

    testing::internal::CaptureStdout();
    machine.TurnCrank();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You turned...\nA gumball comes rolling out the slot...\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 1 gumball\n"
                                  "Machine is waiting for quarter");
}

TEST(GumballMachineTest, TurnCrankInSoldState)
{
    GumballMachine machine(2);
    machine.InsertQuarter();
    machine.TurnCrank();

    testing::internal::CaptureStdout();
    machine.TurnCrank();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You turned but there's no quarter\nYou need to pay first\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 1 gumball\n"
                                  "Machine is waiting for quarter");
}

TEST(GumballMachineTest, TurnCrankInSoldOutState)
{
    GumballMachine machine(0);

    testing::internal::CaptureStdout();
    machine.TurnCrank();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You turned but there's no gumballs\nNo gumball dispensed\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 0 gumballs\n"
                                  "Machine is sold out");
}
