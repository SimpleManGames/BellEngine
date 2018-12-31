#include "bpch.h"
#include "Application.h"

#include "Bell/Events/ApplicationEvent.h"
#include "Bell/Log.h"

namespace Bell {

	Application::Application() { }

	Application::~Application() { }

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		B_TRACE(e);

		while (true);
	}
}