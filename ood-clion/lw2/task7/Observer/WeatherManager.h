#pragma once

#include "Observable.h"
#include "Data/WeatherData.h"

class WeatherManager : public Observable<WeatherData, Event>
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

    [[nodiscard]] double GetWindSpeed() const
    {
        return m_windSpeed;
    }

    [[nodiscard]] double GetWindDirection() const
    {
        return m_windDirection;
    }

    void SetTemperature(double temperature)
    {
        m_temperature = temperature;
        NotifyObservers(Event::Temperature);
    }

    void SetHumidity(double humidity)
    {
        m_humidity = humidity;
        NotifyObservers(Event::Humidity);
    }

    void SetPressure(double pressure)
    {
        m_pressure = pressure;
        NotifyObservers(Event::Pressure);
    }

    void SetWindSpeed(double windSpeed)
    {
        m_windSpeed = windSpeed;
        NotifyObservers(Event::WindSpeed);
    }

    void SetWindDirection(double windDirection)
    {
        m_windDirection = windDirection;
        NotifyObservers(Event::WindDirection);
    }

    void MeasurementsChanged(Event event)
    {
        NotifyObservers(event);
    }

    void SetMeasurements(double temperature, double humidity, double pressure, double windSpeed, double windDirection)
    {
        m_humidity = humidity;
        m_temperature = temperature;
        m_pressure = pressure;
        m_windSpeed = windSpeed;
        m_windDirection = windDirection;

        NotifyObservers(Event::Humidity);
        NotifyObservers(Event::Temperature);
        NotifyObservers(Event::Pressure);
        NotifyObservers(Event::WindSpeed);
        NotifyObservers(Event::WindDirection);
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
