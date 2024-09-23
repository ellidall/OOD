#pragma once

class IQuackBehavior
{
public:
    explicit IQuackBehavior(bool isMute) : m_isMute(isMute)
    {}

    virtual ~IQuackBehavior() = default;
    virtual void Quack() = 0;

    [[nodiscard]] bool IsMute() const {
        return m_isMute;
    }
private:
    bool m_isMute;
};