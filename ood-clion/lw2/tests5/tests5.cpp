#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../task5/Observer/Data/WeatherData.h"
#include "../task5/Observer/WeatherManager.h"

class MockDisplay : public IObserver<WeatherData>
{
public:
    MOCK_METHOD(void, Update, (const WeatherData& data, const IObservable<WeatherData>* observable), (override));

    MockDisplay() = default;
};

TEST (Test5, success_display)
{
    WeatherManager weatherDataIn;
    WeatherManager weatherDataOut;
    MockDisplay mockDisplay;

    weatherDataIn.RegisterObserver(mockDisplay, 1);
    weatherDataOut.RegisterObserver(mockDisplay, 2);

    EXPECT_CALL(mockDisplay, Update(testing::_, &weatherDataIn)).Times(1);
    EXPECT_CALL(mockDisplay, Update(testing::_, &weatherDataOut)).Times(1);

    weatherDataIn.SetMeasurements(30, 60, 763.0);
    weatherDataOut.SetMeasurements(12, 70, 800.0, 33, 52);
}