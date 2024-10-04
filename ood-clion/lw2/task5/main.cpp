#include "Observer/WeatherManager.h"
#include "Observer/CDisplay.h"
#include "Observer/CStatsDisplay.h"

int main()
{
    WeatherManager weatherManagerIn;
    WeatherManager weatherManagerOut;
    StatsDisplay statsDisplay(&weatherManagerIn, &weatherManagerOut);

    weatherManagerIn.RegisterObserver(statsDisplay, 1);
    weatherManagerOut.RegisterObserver(statsDisplay, 2);

    weatherManagerIn.SetMeasurements(100, 0.17, 900);
    std::cout << std::endl << std::endl;
    weatherManagerOut.SetMeasurements(10, 0.8, 761);
    weatherManagerOut.SetMeasurements(30, 80, 800, 20, -1);
    weatherManagerOut.SetMeasurements(30, 80, 800, 20, 180);

    return EXIT_SUCCESS;
}