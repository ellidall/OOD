#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../task4/Data/WeatherData.h"
#include "../task4/Observer/WeatherManager.h"

class MockDisplay : public IObserver<WeatherData>
{
public:
    MOCK_METHOD(void, Update, (const WeatherData& data, const Observable<WeatherData>* observable), (override));

    MockDisplay() = default;
};

TEST (observer_test4, duo_observable_success)
{
    WeatherManager weatherDataIn;
    WeatherManager weatherDataOut;
    MockDisplay mockDisplay;

    weatherDataIn.RegisterObserver(mockDisplay, 1);
    weatherDataOut.RegisterObserver(mockDisplay, 2);

    EXPECT_CALL(mockDisplay, Update(testing::_, &weatherDataIn)).Times(3);
    EXPECT_CALL(mockDisplay, Update(testing::_, &weatherDataOut)).Times(1);

    weatherDataIn.SetMeasurements(20, 30, 720);
    weatherDataIn.SetMeasurements(30, 50, 800);
    weatherDataIn.SetMeasurements(10, 40, 700);
    weatherDataOut.SetMeasurements(19, 67, 798);
}