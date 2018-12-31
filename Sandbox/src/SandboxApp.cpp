#include <Bell.h>

// Default class for entry point
class Sandbox : public Bell::Application {
public:
    Sandbox() { }
    ~Sandbox() { }
};

// Application side function for defining entry point
Bell::Application* Bell::CreateApplication()
{
    return new Sandbox();
}