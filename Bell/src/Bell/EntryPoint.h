#pragma once

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