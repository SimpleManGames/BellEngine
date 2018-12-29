#include <Bell.h>

class Sandbox : public Bell::Application {
public:
	Sandbox() { } 
	~Sandbox() { }
};

Bell::Application* Bell::CreateApplication()
{
	return new Sandbox();
}