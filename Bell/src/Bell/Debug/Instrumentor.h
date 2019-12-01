#ifndef _INSTRUMENTATION_TIMER_H
#define _INSTRUMENTATION_TIMER_H

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>
#include <mutex>

namespace Bell
{
    struct ProfileResult
    {
        std::string Name;
        long long Start, End;
        std::thread::id ThreadID;
    };

    struct InstrumentationSession
    {
        std::string Name;
    };

    class Instrumentor
    {
    public:
        Instrumentor()
            : m_CurrentSession(nullptr), m_ProfileCount(0)
        {
        }

        void BeginSession(const std::string& name, const std::string& filepath = "results.json")
        {
            if (m_CurrentSession) {
                // If there is already a current session, then close it before beginning new one.
                // Subsequent profiling output meant for the original session will end up in the
                // newly opened session instead.  That's better than having badly formatted
                // profiling output.
                if (::Bell::Log::GetCoreLogger()) { // Edge case: BeginSession() might be before Log::Init()
                    B_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, m_CurrentSession->Name);
                }
                EndSession();
            }
            B_CORE_TRACE("Beginning Session for '{0}'.", name);
            
            std::lock_guard lock(m_Mutex);
            m_OutputStream.open(filepath);
            if (m_OutputStream.is_open()) {
                m_CurrentSession = new InstrumentationSession({ name });
                WriteHeader();
            }
            else {
                B_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
            }
            
        }

        void EndSession()
        {
            B_CORE_TRACE("Ending Session for '{0}'.", m_CurrentSession->Name);
            std::lock_guard lock(m_Mutex);
            if (m_CurrentSession) {
                WriteFooter();
                m_OutputStream.close();
                delete m_CurrentSession;
                m_CurrentSession = nullptr;
                m_ProfileCount = 0;
            }
        }

        void WriteProfile(const ProfileResult& result)
        {
            std::lock_guard lock(m_Mutex);
            if (m_CurrentSession) {
                if (m_ProfileCount++ > 0)
                    m_OutputStream << ",";

                std::string name = result.Name;
                std::replace(name.begin(), name.end(), '"', '\'');

                m_OutputStream << "{";
                m_OutputStream << "\"cat\":\"function\",";
                m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
                m_OutputStream << "\"name\":\"" << name << "\",";
                m_OutputStream << "\"ph\":\"X\",";
                m_OutputStream << "\"pid\":0,";
                m_OutputStream << "\"tid\":" << result.ThreadID << ",";
                m_OutputStream << "\"ts\":" << result.Start;
                m_OutputStream << "}";

                m_OutputStream.flush();
            }
        }
        
        static Instrumentor& Get() {
            static Instrumentor instance;
            return instance;
        }

    private:
        std::mutex m_Mutex;
        InstrumentationSession* m_CurrentSession;
        std::ofstream m_OutputStream;
        int m_ProfileCount;

    private:
        void WriteHeader()
        {
            m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
            m_OutputStream.flush();
        }

        void WriteFooter()
        {
            m_OutputStream << "]}";
            m_OutputStream.flush();
        }

    };

    class InstrumentationTimer
    {
    public:
        InstrumentationTimer(const char* name)
            : m_Name(name), m_Stopped(false)
        {
            m_StartTimepoint = std::chrono::high_resolution_clock::now();
        }

        ~InstrumentationTimer()
        {
            if (!m_Stopped)
                Stop();
        }

        void Stop()
        {
            auto endTimepoint = std::chrono::high_resolution_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

            Instrumentor::Get().WriteProfile({ m_Name, start, end, std::this_thread::get_id() });

            m_Stopped = true;
        }
    private:
        const char* m_Name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
        bool m_Stopped;
    };
}

#ifdef B_ENABLE_PROFILING
/// Defining B_FUNCSIG
#if defined(__func__)
#define B_FUNCSIG __func__
#elif defined(__FUNCSIG__)
#define B_FUNCSIG __FUNCSIG__ // Visual Studio Define 
#elif defined(__PRETTY_FUNCTION__)
#define B_FUNCSIG __PRETTY_FUNCTION__ // GCC and Clank Define
#else
#define B_FUNCSIG __FUNCTION__ // Cross-compatible; Gives less information on the function though
#endif

/// Profiling Macros
#define B_PROFILE_BEGIN_SESSION(name) ::Bell::Instrumentor::Get().BeginSession(name)
#define B_PROFILE_BEGIN_SESSION(name, filePath) ::Bell::Instrumentor::Get().BeginSession(name, filePath)
#define B_PROFILE_END_SESSION() ::Bell::Instrumentor::Get().EndSession();

#define B_PROFILE_SCOPE(name) ::Bell::InstrumentationTimer timer##__LINE__(name)
/// __FUNCSIG__ should be switched to https://en.cppreference.com/w/cpp/utility/source_location With C++20
#define B_PROFILE_FUNCTION() B_PROFILE_SCOPE(B_FUNCSIG)
#else
#define B_PROFILE_BEGIN_SESSION(name)
#define B_PROFILE_BEGIN_SESSION(name, filePath)
#define B_PROFILE_END_SESSION()

#define B_PROFILE_SCOPE(name)
#define B_PROFILE_FUNCTION()
#endif // B_ENABLE_PROFILING

#endif // !_INSTRUMENTATION_TIMER_H