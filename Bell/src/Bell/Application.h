#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"

namespace Bell {

	// Base class for applications for entry point creation
	class BELL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};


	// To be defined in client
	Application* CreateApplication();

}

// Header Guard
#endif