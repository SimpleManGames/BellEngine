#pragma once

#ifdef BZ_PLATFORM_WINDOWS

extern Bell::Application* Bell::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Bell::CreateApplication();
	app->Run();
	delete app;
}

#endif