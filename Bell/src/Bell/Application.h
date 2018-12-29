#pragma once

#include "Core.h"

namespace Bell {

	class BELL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};


	// To do defined in client
	Application* CreateApplication();

}