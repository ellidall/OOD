#pragma once

#include <iostream>
#include <limits>
#include "../Data/WeatherData.h"
#include "IObserver.h"

class Stats
{
public:
    void Update(double value)
    {
        if (m_minValue > value)
        {
            m_minValue = value;
        }
        if (m_maxValue < value)
        {
            m_maxValue = value;
        }

        m_acc += value;
        m_countAcc++;
    }

    [[nodiscard]] double GetMin() const
    {
        return m_minValue;
    }

    [[nodiscard]] double GetMax() const
    {
        return m_maxValue;
    }

    [[nodiscard]] double GetAverage() const
    {
        return m_acc / static_cast<double>(m_countAcc);
    }

private:
    double m_minValue = std::numeric_limits<double>::infinity();
    double m_maxValue = -std::numeric_limits<double>::infinity();
    double m_acc = 0;
    int m_countAcc = 0;
};

class CStatsDisplay : public IObserver<WeatherData>
{
public:
    CStatsDisplay(
            Observable<WeatherData>* m_weatherDataIn,
            Observable<WeatherData>* m_weatherDataOut
    ) : m_weatherDataIn(m_weatherDataIn), m_weatherDataOut(m_weatherDataOut)
    {}

private:
    void PrintStats(const Stats& stats)
    {
        std::cout << "Max: " << stats.GetMax() << std::endl;
        std::cout << "Min:" << stats.GetMin() << std::endl;
        std::cout << "Average:" << stats.GetAverage() << std::endl;
    }

    void Update(const WeatherData& data, const IObservable<WeatherData>* observable) override
    {
        std::string location = "Not Stated";
        if (observable == m_weatherDataIn)
        {
            location = "Inside Weather Station";
        }
        else if (observable == m_weatherDataOut)
        {
            location = "Outside Weather Station";
        }

        m_statisticsTemperature.Update(data.temperature);
        m_statisticsHumidity.Update(data.humidity);
        m_statisticsPressure.Update(data.pressure);

        std::cout << "Location " << location << std::endl;
        std::cout << "Temperature" << std::endl;
        PrintStats(m_statisticsTemperature);
        std::cout << "Humidity" << std::endl;
        PrintStats(m_statisticsHumidity);
        std::cout << "Pressure" << std::endl;
        PrintStats(m_statisticsPressure);

        std::cout << "----------------" << std::endl;
    }

    Stats m_statisticsTemperature;
    Stats m_statisticsHumidity;
    Stats m_statisticsPressure;

    const Observable<WeatherData>* m_weatherDataIn;
    const Observable<WeatherData>* m_weatherDataOut;
};
