#ifndef ENTRY_POINT_H
#define ENTRY_POINT_H

#ifdef BZ_PLATFORM_WINDOWS

extern Bell::Application* Bell::CreateApplication();

int main(int argc, char** argv)
{
	Bell::Log::Init();
	BZ_CORE_WARN("Initialized Log!");
	BZ_INFO("Initialized Log!");

	auto app = Bell::CreateApplication();
	app->Run();
	delete app;
}

#endif

// Header Guard
#endif