#include "Observable/WeatherManager.h"
#include "Observer/CDisplay.h"
#include "Observer/CStatsDisplay.h"

int main()
{
    WeatherManager weatherManager;
    CDisplay display;
    StatsDisplay statsDisplay;

    weatherManager.RegisterObserver(display, 1);
    weatherManager.RegisterObserver(statsDisplay, 2);

    weatherManager.SetMeasurements(100, 0.17, 900);
    std::cout << std::endl << std::endl;
    weatherManager.SetMeasurements(10, 0.8, 761);

    return EXIT_SUCCESS;
}