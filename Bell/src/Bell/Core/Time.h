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

    template<typename Fn>
    class Timer
    {
    public:
        Timer(const char* name, Fn&& func)
            : m_Name(name), m_Func(func), m_Stopped(false)
        {
            m_StartTimepoint = std::chrono::high_resolution_clock::now();
        }

        ~Timer()
        {
            if (!m_Stopped)
                Stop();
        }

        void Stop()
        {
            auto endTimepoint = std::chrono::high_resolution_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

            m_Stopped = true;

            // Micro to milliseconds for better decimal values
            float duration = (end - start) * 0.001f;
            std::cout << m_Name << ": " << duration << "ms" << std::endl;
            m_Func({ m_Name, duration });
        }

    private:
        // Storing as a char* to avoid stack alloc
        const char* m_Name;
        Fn m_Func;
        std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
        bool m_Stopped;
    };

#define PROFILE_SCOPE(name) Bell::Timer timer##__LINE__(name, [&](ProfileResult profileResult){m_ProfileResults.push_back(profileResult); })
}

#endif // !_TIME_H
