#pragma once

namespace Sonata {

class Timestep {
public:
    explicit Timestep(const double p_Time = 0.0f)
        : m_Time(p_Time) {}

    [[nodiscard]] double GetSeconds() const { return m_Time; }
    [[nodiscard]] double GetMilliseconds() const { return m_Time * 1000.0; }

private:
    double m_Time{};
};

}
