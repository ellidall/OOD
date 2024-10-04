#include "Observer/WeatherManager.h"
#include "Observer/Display/FishermanDisplay.h"
#include "Observer/Display/StatsDisplay.h"

int main()
{
    WeatherManager weatherManager;
    FishermanDisplay fishermanDisplay;
    StatsDisplay statsDisplay;

    weatherManager.RegisterObserver(fishermanDisplay, Event::Pressure);
    weatherManager.RegisterObserver(fishermanDisplay, Event::Temperature);
    weatherManager.RegisterObserver(statsDisplay, Event::Temperature);
    weatherManager.RegisterObserver(statsDisplay, Event::Pressure);
    weatherManager.RegisterObserver(statsDisplay, Event::Humidity);
    weatherManager.RegisterObserver(statsDisplay, Event::WindSpeed);
    weatherManager.RegisterObserver(statsDisplay, Event::WindDirection);

    weatherManager.SetMeasurements(30, 80, 800, 20, 180);
    weatherManager.SetWindDirection(20);

    return EXIT_SUCCESS;
}