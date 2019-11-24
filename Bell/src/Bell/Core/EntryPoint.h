// Entry Point definition for application using the Bell Engine
// ------------------------------------------------------------

#ifndef _ENTRY_POINT_H
#define _ENTRY_POINT_H

#ifdef B_PLATFORM_WINDOWS

// This function definition will be defined in user applications
extern Bell::Application* Bell::CreateApplication();

int main(int argc, char** argv)
{
    B_PROFILE_BEGIN_SESSION("Startup", "BellProfile-Startup.json");
    // Initialize the logger
    Bell::Log::Init();
    B_CORE_INFO("Initialized Log!");
    B_INFO("Initialized Log!");

    // Create app using the app user's function
    auto app = Bell::CreateApplication();
    B_PROFILE_END_SESSION();

    B_PROFILE_BEGIN_SESSION("Runtime", "BellProfile-Runtime.json");
    app->Run();
    B_PROFILE_END_SESSION();

    B_PROFILE_BEGIN_SESSION("Shutdown", "BellProfile-Shutdown.json");
    delete app;
    B_PROFILE_END_SESSION();
}

#endif // !B_PLATFORM_WINDOWS

#endif // !_ENTRY_POINT_H