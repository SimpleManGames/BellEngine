#ifndef _TESTLAYER_H
#define _TESTLAYER_H

#include <Bell.h>

class TestLayer : public Bell::Layer
{
public:
    TestLayer(const std::string &name = "Layer")
        : Layer(name)
    {
    }

    virtual void OnUpdate(Bell::Timestep deltaTime) override
    {
        m_CurrentTimeIncrement += deltaTime;
        if (m_CurrentTimeIncrement >= EXIT_TIME)
        {
            Bell::Application::Get().Close();
        }
    }

private:
    const float EXIT_TIME = 1.0f;
    float m_CurrentTimeIncrement = 0.0f;

    bool m_Attached = false;
};

#endif // !_TESTLAYER_H