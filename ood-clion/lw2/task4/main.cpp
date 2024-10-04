#include "Observer/WeatherManager.h"
#include "Observer/CDisplay.h"
#include "Observer/CStatsDisplay.h"

int main()
{
    WeatherManager weatherManagerIn;
    WeatherManager weatherManagerOut;
    CDisplay display(&weatherManagerIn, &weatherManagerOut);
    StatsDisplay statsDisplay(&weatherManagerIn, &weatherManagerOut);

    weatherManagerIn.RegisterObserver(display, 1);
    weatherManagerOut.RegisterObserver(display, 2);

    weatherManagerIn.SetMeasurements(100, 0.17, 900);
    std::cout << std::endl << std::endl;
    weatherManagerOut.SetMeasurements(10, 0.8, 761);

    return EXIT_SUCCESS;
}