#include <gtest/gtest.h>
#include "../task2/Data/WeatherData.h"
#include "../task2/Observer/IObserver.h"
#include "../task2/Observable/Observable.h"
#include "../task2/Observable/WeatherManager.h"
#include "../task2/Observer/CDisplay.h"

class ObserverWithRemovingOnUpdate : public IObserver<WeatherData>
{
public:
    explicit ObserverWithRemovingOnUpdate(Observable<WeatherData>& observable) : m_observable(observable)
    {
    }

    void Update(WeatherData const& data) override
    {
        std::cout << "ObserverWithRemovingOnUpdate::Update()" << std::endl;
        std::cout << "----------------" << std::endl;
        m_observable.RemoveObserver(*this);
    }

private:
    Observable<WeatherData>& m_observable;
};

TEST(Test2, success_observer_removing_on_update)
{
    WeatherManager weatherManager;
    CDisplay display1;
    ObserverWithRemovingOnUpdate observerWithRemovingOnUpdate(weatherManager);

    weatherManager.RegisterObserver(observerWithRemovingOnUpdate);
    weatherManager.RegisterObserver(display1);

    std::cout << "Update #1" << std::endl;
    weatherManager.SetMeasurements(5, 0.6, 761);
    std::cout << std::endl << std::endl;

    std::cout << "Update #2" << std::endl;
    weatherManager.SetMeasurements(10, 0.5, 762);
}