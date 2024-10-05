#pragma once

#include <iostream>
#include <limits>
#include <algorithm>
#include <cmath>
#include "Data/WeatherData.h"
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

class WindStats
{
public:
    void Update(double speed, double direction)
    {
        if (m_minSpeed > speed)
        {
            m_minSpeed = speed;
        }
        if (m_maxSpeed < speed)
        {
            m_maxSpeed = speed;
        }
        m_totalSpeed += speed;

        double radianDirection = direction * M_PI / 180.0;
        m_sumX += speed * cos(radianDirection);
        m_sumY += speed * sin(radianDirection);

        m_acc++;
    }

    [[nodiscard]] double GetMaxSpeed() const
    {
        return m_maxSpeed;
    }

    [[nodiscard]] double GetMinSpeed() const
    {
        return m_minSpeed;
    }

    [[nodiscard]] double GetAverageSpeed() const
    {
        if (m_acc == 0)
        {
            return 0;
        }

        return m_totalSpeed / m_acc;
    }

    [[nodiscard]] double GetAverageDirection() const
    {
        if (m_acc == 0)
        {
            return 0;
        }

        double averageDegreeDirection = atan2(m_sumY, m_sumX) * 180.0 / M_PI;
        return fmod(averageDegreeDirection + 360.0, 360.0);
    }

private:
    double m_totalSpeed = 0;
    double m_minSpeed = std::numeric_limits<double>::infinity();
    double m_maxSpeed = -std::numeric_limits<double>::infinity();
    double m_sumX = 0;
    double m_sumY = 0;
    unsigned m_acc = 0;
};

class StatsDisplay : public IObserver<WeatherData>
{
public:
    StatsDisplay(
            Observable<WeatherData>* m_weatherDataIn,
            Observable<WeatherData>* m_weatherDataOut
    ) : m_weatherDataIn(m_weatherDataIn), m_weatherDataOut(m_weatherDataOut)
    {}

private:
    static void PrintStats(const Stats& stats)
    {
        std::cout << "Max: " << stats.GetMax() << std::endl;
        std::cout << "Min:" << stats.GetMin() << std::endl;
        std::cout << "Average:" << stats.GetAverage() << std::endl;
    }
    // сделать два объекта станции и даты

    void Update(const WeatherData& data, const IObservable<WeatherData>* observable) override
    {
        m_statisticsTemperature.Update(data.temperature);
        m_statisticsHumidity.Update(data.humidity);
        m_statisticsPressure.Update(data.pressure);

        if (observable == m_weatherDataIn)
        {
            std::cout << "Location: inside" << std::endl;
            std::cout << "Temperature" << std::endl;
            PrintStats(m_statisticsTemperature);
            std::cout << "Humidity" << std::endl;
            PrintStats(m_statisticsHumidity);
            std::cout << "Pressure" << std::endl;
            PrintStats(m_statisticsPressure);
        }
        else if (observable == m_weatherDataOut)
        {
            m_windStats.Update(data.windSpeed, data.windDirection);

            std::cout << "Location: outside" << std::endl;
            std::cout << "Temperature" << std::endl;
            PrintStats(m_statisticsTemperature);
            std::cout << "Humidity" << std::endl;
            PrintStats(m_statisticsHumidity);
            std::cout << "Pressure" << std::endl;
            PrintStats(m_statisticsPressure);
            std::cout << "Max wind speed " << m_windStats.GetMaxSpeed() << std::endl;
            std::cout << "Min wind speed " << m_windStats.GetMinSpeed() << std::endl;
            std::cout << "Average wind speed " << m_windStats.GetAverageSpeed() << std::endl;
            std::cout << "Wind Direction " << m_windStats.GetAverageDirection() << std::endl;
        }
        else
        {
            std::cout << "Weather Station is unknown" << std::endl;
        }

        std::cout << "----------------" << std::endl;
    }

    Stats m_statisticsTemperature;
    Stats m_statisticsHumidity;
    Stats m_statisticsPressure;
    WindStats m_windStats;

    const Observable<WeatherData>* m_weatherDataIn;
    const Observable<WeatherData>* m_weatherDataOut;
};
