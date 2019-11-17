// Timestep Definition
// -------------------

#ifndef _TIME_H
#define _TIME_H

#include <chrono>

namespace Bell {

    class Timestep
    {
    public:
        Timestep(float time = 0.0f)
            : m_Time(time)
        {

        }

        operator float() const { return m_Time; }

        float GetSeconds() const { return m_Time; }
        float GetMilliseconds() const { return m_Time * 1000.0f; }
    private:
        float m_Time;
    };
}

#endif // !_TIME_H
