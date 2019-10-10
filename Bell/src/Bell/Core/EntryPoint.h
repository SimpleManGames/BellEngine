// Entry Point definition for application using the Bell Engine
// ------------------------------------------------------------

#ifndef _ENTRY_POINT_H
#define _ENTRY_POINT_H

#ifdef B_PLATFORM_WINDOWS

// This function definition will be defined in user applications
extern Bell::Application* Bell::CreateApplication();

int main(int argc, char** argv)
{
    // Initialize the logger
    Bell::Log::Init();
    B_CORE_INFO("Initialized Log!");
    B_INFO("Initialized Log!");

    // Create app using the app user's function
    auto app = Bell::CreateApplication();
    app->Run();
    delete app;
}

#endif // !B_PLATFORM_WINDOWS

#endif // !_ENTRY_POINT_H