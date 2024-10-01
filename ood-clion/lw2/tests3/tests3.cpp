#include <gtest/gtest.h>
#include "../task3/Data/WeatherData.h"
#include "../task3/Observable/WeatherManager.h"

class PriorityObserver : public IObserver<WeatherData>
{
public:
    PriorityObserver(int id, std::vector<int>& callOrder)
            : m_id(id), m_callOrder(callOrder)
    {
    }

    void Update(WeatherData const& data) override
    {
        m_callOrder.push_back(m_id);
    }

private:
    int m_id;
    std::vector<int>& m_callOrder;
};

TEST(Teast3, success_priority)
{
    WeatherManager weatherManager;

    std::vector<int> callOrder;

    PriorityObserver highPriority(1, callOrder);
    PriorityObserver lowPriority(2, callOrder);

    weatherManager.RegisterObserver(highPriority, 5);
    weatherManager.RegisterObserver(lowPriority, 1);

    weatherManager.SetMeasurements(30, 70, 800);

    ASSERT_EQ(callOrder.size(), 2);

    EXPECT_TRUE(callOrder[0] < callOrder[1]);
}