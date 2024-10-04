#pragma once

#include <iostream>
#include "../Data/WeatherData.h"
#include "../Data/Event.h"
#include "../IObserver.h"

class FishermanDisplay : public IObserver<WeatherData, Event>
{
private:
    void Update(WeatherData const& data, Event event) override
    {
        std::cout << "|FishermanDisplay|" << std::endl;
        if (event == Event::Temperature)
        {
            std::cout << "> Current Temperature: " << data.temperature << std::endl;
        }
        else if (event == Event::Pressure)
        {
            std::cout << "> Current Pressure: " << data.pressure << std::endl;
        }
        std::cout << "---------------------" << std::endl;
    }
};
