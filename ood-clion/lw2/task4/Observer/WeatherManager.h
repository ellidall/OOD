#pragma once

#include "Observable.h"
#include "Data/WeatherData.h"

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

    void MeasurementsChanged()
    {
        NotifyObservers();
    }

    void SetMeasurements(double temp, double humidity, double pressure)
    {
        m_humidity = humidity;
        m_temperature = temp;
        m_pressure = pressure;
        NotifyObservers();
    }

protected:
    [[nodiscard]] WeatherData GetChangedData() const override
    {
        WeatherData info;
        info.temperature = GetTemperature();
        info.humidity = GetHumidity();
        info.pressure = GetPressure();
        return info;
    }

private:
    double m_temperature = 0.0;
    double m_humidity = 0.0;
    double m_pressure = 760.0;
};
