#pragma once

#include <iostream>
#include "../Data/WeatherData.h"
#include "IObserver.h"

class CDisplay : public IObserver<WeatherData>
{
public:
    CDisplay(
            Observable<WeatherData>* m_weatherDataIn,
            Observable<WeatherData>* m_weatherDataOut
    ) : m_weatherDataIn(m_weatherDataIn), m_weatherDataOut(m_weatherDataOut)
    {}

private:

    void Update(const WeatherData& data, const Observable<WeatherData>* observable) override
    {
        std::string location;
        if (observable == m_weatherDataIn)
        {
            location = "Inside Weather Station";
        }
        else if (observable == m_weatherDataOut)
        {
            location = "Outside Weather Station";
        }
        else
        {
            std::cout << "Weather Station is unknown" << std::endl;
            return;
        }

        std::cout << "Location " << location << std::endl;
        std::cout << "Current Temp " << data.temperature << std::endl;
        std::cout << "Current Humidity " << data.humidity << std::endl;
        std::cout << "Current Pressure " << data.pressure << std::endl;
        std::cout << "Current Wind direction " << data.windDirection << std::endl;
        std::cout << "Current Wind speed " << data.windSpeed << std::endl;
        std::cout << "----------------" << std::endl;
    }

    const Observable<WeatherData>* m_weatherDataIn;
    const Observable<WeatherData>* m_weatherDataOut;
};