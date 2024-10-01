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
private:
    void Update(const WeatherData& data) override
    {
        m_statisticsTemperature.Update(data.temperature);
        m_statisticsHumidity.Update(data.humidity);
        m_statisticsPressure.Update(data.pressure);

        std::cout << "Max Temp " << m_statisticsTemperature.GetMax() << std::endl;
        std::cout << "Min Temp " << m_statisticsTemperature.GetMin() << std::endl;
        std::cout << "Average Temp " << m_statisticsTemperature.GetAverage() << std::endl;

        std::cout << "Max Humidity " << m_statisticsHumidity.GetMax() << std::endl;
        std::cout << "Min Humidity " << m_statisticsHumidity.GetMin() << std::endl;
        std::cout << "Average Humidity " << m_statisticsHumidity.GetAverage() << std::endl;

        std::cout << "Max Pressure " << m_statisticsPressure.GetMax() << std::endl;
        std::cout << "Min Pressure " << m_statisticsPressure.GetMin() << std::endl;
        std::cout << "Average Pressure " << m_statisticsPressure.GetAverage() << std::endl;

        std::cout << "----------------" << std::endl;
    }

    Stats m_statisticsTemperature;
    Stats m_statisticsHumidity;
    Stats m_statisticsPressure;
};
