// Timestep Definition
// -------------------

#ifndef _TIME_H
#define _TIME_H

#include <chrono>

namespace Bell
{

    class Timestep
    {
    public:
        /**
         * @brief Construct a new Timestep object
         * 
         */
        Timestep()
            : m_Time(0.0f) {}
        /**
         * @brief Construct a new Timestep object
         * 
         * @param time Initilazes this Timestep with a value already
         * - Defaults to 0.0f
         */
        Timestep(float time = 0.0f)
            : m_Time(time) {}

        ~Timestep() = default;
        /**
         * @brief Copy Constructor for Timestep
         * 
         * @param copy Timestep object to copy
         */
        Timestep(const Timestep &copy)
            : m_Time(copy) {}

        /**
         * @brief Float operator to allow for easy casting and modification
         * 
         * @return float Current Time stored within
         */
        operator float() const { return m_Time; }

        /**
         * @brief Gets the Time in Seconds
         * 
         * @return float Time in Seconds
         */
        float GetSeconds() const { return m_Time; }
        /**
         * @brief Get the Time in Milliseconds
         * 
         * @return float Time in Milliseconds
         */
        float GetMilliseconds() const { return m_Time * 1000.0f; }

    private:
        float m_Time;
    };
} // namespace Bell

#endif // !_TIME_H
