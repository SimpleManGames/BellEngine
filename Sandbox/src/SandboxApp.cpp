#include <Bell.h>

#include <Bell/Netcode/Server.h>

class ExampleLayer : public Bell::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        //B_INFO("Example Layer::Update");
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
        PushOverlay(new Bell::ImGuiLayer());

        Bell::Server server = Bell::Server();
        server.Start();
    }
    ~Sandbox() { }
};

// Application side function for defining entry point
Bell::Application* Bell::CreateApplication()
{
    return new Sandbox();
}