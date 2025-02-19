#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../task2-4/Multi/IMultiGumballMachine.h"
#include "../task2-4/Multi/HasQuarterState.h"
#include "../task2-4/Multi/NoQuarterState.h"
#include "../task2-4/Multi/SoldOutState.h"
#include "../task2-4/Multi/SoldState.h"
#include "../task2-4/Multi/MultiGumballMachine.h"

class MockGumballMachine : public IMultiGumballMachine
{
public:
    MOCK_METHOD(void, ReleaseBall, (), (override));
    MOCK_METHOD(unsigned, GetBallCount, (), (const, override));
    MOCK_METHOD(unsigned, GetQuarterCount, (), (const, override));
    MOCK_METHOD(bool, IsFull, (), (const, override));
    MOCK_METHOD(void, AddQuarter, (), (override));
    MOCK_METHOD(void, FillBalls, (unsigned numBalls), (override));
    MOCK_METHOD(void, GiveOutAllQuarters, (), (override));
    MOCK_METHOD(void, SetSoldOutState, (), (override));
    MOCK_METHOD(void, SetNoQuarterState, (), (override));
    MOCK_METHOD(void, SetSoldState, (), (override));
    MOCK_METHOD(void, SetHasQuarterState, (), (override));
};

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

TEST(SoldStateTest, DispenseWhenBallCountIsPositiveQuarterCountIsPositive)
{
    MockGumballMachine mockMachine;
    SoldState state(mockMachine);

    EXPECT_CALL(mockMachine, ReleaseBall()).Times(1);
    EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(Return(1));
    EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(Return(1));
    EXPECT_CALL(mockMachine, SetHasQuarterState()).Times(1);

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

TEST(SoldStateTest, FillBalls)
{
    MockGumballMachine mockMachine;
    SoldState state(mockMachine);

    testing::internal::CaptureStdout();
    state.FillBalls(1);

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Can't add gumball when giving gumball\n");
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

TEST(SoldOutStateTest, EjectQuarterWhenCountIsPositive)
{
    MockGumballMachine mockMachine;
    SoldOutState state(mockMachine);

    EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(Return(2));
    EXPECT_CALL(mockMachine, GiveOutAllQuarters()).Times(1);

    state.EjectQuarter();
}

TEST(SoldOutStateTest, EjectQuarterWhenCountIsZero)
{
    MockGumballMachine mockMachine;
    SoldOutState state(mockMachine);

    testing::internal::CaptureStdout();
    EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(Return(0));
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

TEST(SoldOutStateTest, FillBallsWhenQuarterCountIsPositive)
{
    MockGumballMachine mockMachine;
    SoldOutState state(mockMachine);

    testing::internal::CaptureStdout();
    EXPECT_CALL(mockMachine, FillBalls(1)).Times(1);
    EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(Return(2));
    EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(Return(1));
    EXPECT_CALL(mockMachine, SetHasQuarterState()).Times(1);
    state.FillBalls(1);

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Added gumball\n");
}

TEST(SoldOutStateTest, FillBallsWhenQuarterCountIsZero)
{
    MockGumballMachine mockMachine;
    SoldOutState state(mockMachine);

    testing::internal::CaptureStdout();
    EXPECT_CALL(mockMachine, FillBalls(1)).Times(1);
    EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(Return(2));
    EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(Return(0));
    EXPECT_CALL(mockMachine, SetNoQuarterState()).Times(1);
    state.FillBalls(1);

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Added gumball\n");
}

// HasQuarterState
TEST(HasQuarterStateTest, InsertQuarterWhenQuarterCountIsMax)
{
    MockGumballMachine mockMachine;
    HasQuarterState state(mockMachine);

    testing::internal::CaptureStdout();
    EXPECT_CALL(mockMachine, IsFull).WillOnce(Return(true));
    state.InsertQuarter();

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "You can't insert another quarter\n");
}

TEST(HasQuarterStateTest, InsertQuarterWhenQuarterCountIsNotMax)
{
    MockGumballMachine mockMachine;
    HasQuarterState state(mockMachine);

    testing::internal::CaptureStdout();
    EXPECT_CALL(mockMachine, IsFull).WillOnce(Return(false));
    EXPECT_CALL(mockMachine, AddQuarter).Times(1);
    state.InsertQuarter();

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "You inserted another quarter\n");
}

TEST(HasQuarterStateTest, EjectQuarter)
{
    MockGumballMachine mockMachine;
    HasQuarterState state(mockMachine);

    testing::internal::CaptureStdout();
    EXPECT_CALL(mockMachine, GiveOutAllQuarters()).Times(1);
    EXPECT_CALL(mockMachine, SetNoQuarterState()).Times(1);
    state.EjectQuarter();

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "");
}

TEST(HasQuarterStateTest, TurnCrankWhenQuarterCountIsZero)
{
    MockGumballMachine mockMachine;
    HasQuarterState state(mockMachine);

    testing::internal::CaptureStdout();
    EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(Return(0));
    EXPECT_CALL(mockMachine, SetNoQuarterState()).Times(1);
    state.TurnCrank();

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "No quarters left\n");
}

TEST(HasQuarterStateTest, TurnCrankWhenQuarterCountIsPozitive)
{
    MockGumballMachine mockMachine;
    HasQuarterState state(mockMachine);

    testing::internal::CaptureStdout();
    EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(Return(1));
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

TEST(HasQuarterStateTest, FillBalls)
{
    MockGumballMachine mockMachine;
    HasQuarterState state(mockMachine);

    testing::internal::CaptureStdout();
    EXPECT_CALL(mockMachine, FillBalls(1)).Times(1);
    state.FillBalls(1);

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Gumballs added\n");
}

// NoQuarterState
TEST(NoQuarterStateTest, InsertQuarter)
{
    MockGumballMachine mockMachine;
    NoQuarterState state(mockMachine);

    testing::internal::CaptureStdout();
    EXPECT_CALL(mockMachine, AddQuarter()).Times(1);
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

TEST(NoQuarterStateTest, FillBalls)
{
    MockGumballMachine mockMachine;
    NoQuarterState state(mockMachine);

    testing::internal::CaptureStdout();
    EXPECT_CALL(mockMachine, FillBalls(1)).Times(1);
    state.FillBalls(1);

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Gumballs added\n");
}

// MultiGumballMachine
TEST(MultiGumballMachineTest, InitialState)
{
    MultiGumballMachine machine(5);
    std::string expected = "Mighty Gumball, Inc.\n"
                           "C++-enabled Standing Gumball Model #2016\n"
                           "Inventory: 5 gumballs, 0 quarters\n"
                           "Machine is waiting for quarter";
    EXPECT_EQ(machine.ToString(), expected);
}

TEST(MultiGumballMachineTest, InsertQuarterInNoQuarterState)
{
    MultiGumballMachine machine(2);

    testing::internal::CaptureStdout();
    machine.InsertQuarter();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You inserted a quarter\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 2 gumballs, 1 quarter\n"
                                  "Machine is waiting for turn of crank");
}

TEST(MultiGumballMachineTest, InsertQuarterInHasQuarterStateWhenFull)
{
    MultiGumballMachine machine(2, 1);
    machine.InsertQuarter();

    testing::internal::CaptureStdout();
    machine.InsertQuarter();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You can't insert another quarter\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 2 gumballs, 1 quarter\n"
                                  "Machine is waiting for turn of crank");
}

TEST(MultiGumballMachineTest, InsertQuarterInHasQuarterState)
{
    MultiGumballMachine machine(2, 2);
    machine.InsertQuarter();

    testing::internal::CaptureStdout();
    machine.InsertQuarter();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You inserted another quarter\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 2 gumballs, 2 quarters\n"
                                  "Machine is waiting for turn of crank");
}

//TEST(MultiGumballMachineTest, InsertQuarterInSoldState)
//{
//    MultiGumballMachine machine(2, 2);
//    machine.InsertQuarter();
//    machine.TurnCrank();
//
//    testing::internal::CaptureStdout();
//    machine.InsertQuarter();
//    std::string output = testing::internal::GetCapturedStdout();
//
//    EXPECT_EQ(output, "You inserted a quarter\n");
//    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
//                                  "C++-enabled Standing Gumball Model #2016\n"
//                                  "Inventory: 1 gumball\n"
//                                  "Machine is waiting for turn of crank");
//}

TEST(MultiGumballMachineTest, InsertQuarterInSoldOutState)
{
    MultiGumballMachine machine(0);

    testing::internal::CaptureStdout();
    machine.InsertQuarter();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You can't insert a quarter, the machine is sold out\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 0 gumballs, 0 quarters\n"
                                  "Machine is sold out");
}

TEST(MultiGumballMachineTest, EjectQuarterInNoQuarterState)
{
    MultiGumballMachine machine(2);

    testing::internal::CaptureStdout();
    machine.EjectQuarter();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You haven't inserted a quarter\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 2 gumballs, 0 quarters\n"
                                  "Machine is waiting for quarter");
}

TEST(MultiGumballMachineTest, EjectQuarterInHasQuarterState)
{
    MultiGumballMachine machine(2);
    machine.InsertQuarter();

    testing::internal::CaptureStdout();
    machine.EjectQuarter();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Give out all quarters\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 2 gumballs, 0 quarters\n"
                                  "Machine is waiting for quarter");
}

//TEST(MultiGumballMachineTest, EjectQuarterInSoldState)
//{
//    MultiGumballMachine machine(2);
//    machine.InsertQuarter();
//    machine.TurnCrank();
//
//    testing::internal::CaptureStdout();
//    machine.EjectQuarter();
//    std::string output = testing::internal::GetCapturedStdout();
//
//    EXPECT_EQ(output, "You haven't inserted a quarter\n");
//    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
//                                  "C++-enabled Standing Gumball Model #2016\n"
//                                  "Inventory: 1 gumball\n"
//                                  "Machine is waiting for quarter");
//}

TEST(MultiGumballMachineTest, EjectQuarterInSoldOutState)
{
    MultiGumballMachine machine(0);

    testing::internal::CaptureStdout();
    machine.EjectQuarter();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You can't eject, you haven't inserted a quarter yet\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 0 gumballs, 0 quarters\n"
                                  "Machine is sold out");
}

TEST(MultiGumballMachineTest, TurnCrankInNoQuarterState)
{
    MultiGumballMachine machine(2);

    testing::internal::CaptureStdout();
    machine.TurnCrank();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You turned but there's no quarter\nYou need to pay first\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 2 gumballs, 0 quarters\n"
                                  "Machine is waiting for quarter");
}

//TEST(MultiGumballMachineTest, TurnCrankInHasQuarterState)
//{
//    MultiGumballMachine machine(2);
//    machine.InsertQuarter();
//
//    testing::internal::CaptureStdout();
//    machine.TurnCrank();
//    std::string output = testing::internal::GetCapturedStdout();
//
//    EXPECT_EQ(output, "You turned...\nA gumball comes rolling out the slot...\n");
//    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
//                                  "C++-enabled Standing Gumball Model #2016\n"
//                                  "Inventory: 1 gumball, 0 quarters\n"
//                                  "Machine is waiting for quarter");
//}
//
//TEST(MultiGumballMachineTest, TurnCrankInSoldState)
//{
//    MultiGumballMachine machine(2);
//    machine.InsertQuarter();
//    machine.TurnCrank();
//
//    testing::internal::CaptureStdout();
//    machine.TurnCrank();
//    std::string output = testing::internal::GetCapturedStdout();
//
//    EXPECT_EQ(output, "You turned but there's no quarter\nYou need to pay first\n");
//    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
//                                  "C++-enabled Standing Gumball Model #2016\n"
//                                  "Inventory: 1 gumball\n"
//                                  "Machine is waiting for quarter");
//}
//
//TEST(MultiGumballMachineTest, TurnCrankInSoldOutState)
//{
//    MultiGumballMachine machine(0);
//
//    testing::internal::CaptureStdout();
//    machine.TurnCrank();
//    std::string output = testing::internal::GetCapturedStdout();
//
//    EXPECT_EQ(output, "You turned but there's no gumballs\nNo gumball dispensed\n");
//    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
//                                  "C++-enabled Standing Gumball Model #2016\n"
//                                  "Inventory: 0 gumballs\n"
//                                  "Machine is sold out");
//}

//TEST(MultiGumballMachineTest, FillBallsInNoQuarterState)
//{
//    MultiGumballMachine machine(2);
//
//    testing::internal::CaptureStdout();
//    machine.Fill(4);
//    std::string output = testing::internal::GetCapturedStdout();
//
//    EXPECT_EQ(output, "Gumballs added\n");
//    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
//                                  "C++-enabled Standing Gumball Model #2016\n"
//                                  "Inventory: 4 gumballs, 0 quarters\n"
//                                  "Machine is waiting for quarter");
//}

TEST(MultiGumballMachineTest, FillBallsInNoQuarterState)
{
    MultiGumballMachine machine(2);

    testing::internal::CaptureStdout();
    machine.Fill(4);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Gumballs added\n");
    EXPECT_EQ(machine.ToString(), "Mighty Gumball, Inc.\n"
                                  "C++-enabled Standing Gumball Model #2016\n"
                                  "Inventory: 4 gumballs, 0 quarters\n"
                                  "Machine is waiting for quarter");
}
