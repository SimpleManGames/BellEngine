#include <Bell.h>

class ExampleLayer : public Bell::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        if (Bell::Input::IsKeyPressed(B_KEY_TAB))
            B_INFO("Tab Pressed");
    }

    void OnEvent(Bell::Event& event) override
    {
        //B_TRACE("{0}", event);
    }
};

// Default class for entry point
class Sandbox : public Bell::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }
    ~Sandbox() { }
};

// Application side function for defining entry point
Bell::Application* Bell::CreateApplication()
{
    return new Sandbox();
}