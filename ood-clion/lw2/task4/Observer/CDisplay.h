#pragma once

#include <iostream>
#include "../Data/WeatherData.h"
#include "IObserver.h"

class CDisplay : public IObserver<WeatherData>
{
private:
    void Update(const WeatherData& data) override
    {
        std::cout << "Current Temp " << data.temperature << std::endl;
        std::cout << "Current Humidity " << data.humidity << std::endl;
        std::cout << "Current Pressure " << data.pressure << std::endl;
        std::cout << "----------------" << std::endl;
    }
};