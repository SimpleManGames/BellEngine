#ifndef ENTRY_POINT_H
#define ENTRY_POINT_H

#ifdef B_PLATFORM_WINDOWS

extern Bell::Application* Bell::CreateApplication();

int main(int argc, char** argv)
{
    Bell::Log::Init();
    B_CORE_WARN("Initialized Log!");
    B_INFO("Initialized Log!");

    auto app = Bell::CreateApplication();
    app->Run();
    delete app;
}

#endif

#endif // !ENTRY_POINT_H