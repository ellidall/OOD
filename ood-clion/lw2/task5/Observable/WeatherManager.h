#pragma once

#include "Observable.h"
#include "../Data/WeatherData.h"

class WeatherManager : public Observable<WeatherData>
{
public:
    WeatherManager() = default;

    [[nodiscard]] double GetTemperature() const
    {
        return m_temperature;
    }

    [[nodiscard]] double GetHumidity() const
    {
        return m_humidity;
    }

    [[nodiscard]] double GetPressure() const
    {
        return m_pressure;
    }

    [[nodiscard]] double GetWindSpeed()const
    {
        return m_windSpeed;
    }

    [[nodiscard]] double GetWindDirection()const
    {
        return m_windDirection;
    }

    void MeasurementsChanged()
    {
        NotifyObservers();
    }

    void SetMeasurements(double temp, double humidity, double pressure, double windSpeed = 0, double windDirection = 0)
    {
        m_humidity = humidity;
        m_temperature = temp;
        m_pressure = pressure;
        m_windSpeed = windSpeed;
        m_windDirection = windDirection;

        NotifyObservers();
    }

protected:
    [[nodiscard]] WeatherData GetChangedData() const override
    {
        WeatherData info;
        info.temperature = GetTemperature();
        info.humidity = GetHumidity();
        info.pressure = GetPressure();
        info.windSpeed = GetWindSpeed();
        info.windDirection = GetWindDirection();
        return info;
    }

private:
    double m_temperature = 0.0;
    double m_humidity = 0.0;
    double m_pressure = 760.0;
    double m_windSpeed = 0.0;
    double m_windDirection = 0.0;
};
