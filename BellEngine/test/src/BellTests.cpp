#include <gtest/gtest.h>

#include <Bell.h>

TEST(BellTests, BellLogInit)
{
    Bell::Log::Init();
    ASSERT_TRUE(Bell::Log::GetClientLogger() != nullptr);
    ASSERT_TRUE(Bell::Log::GetCoreLogger() != nullptr);
}

TEST(BellTests, ApplicationCreation)
{
    Bell::Log::Init();

    Bell::WindowProps props;
    props.Title = "Test App";
    props.Width = 1080;
    props.Height = 640;
    Bell::Application *app = new Bell::Application(props);

    Bell::ApplicationState appState = app->GetApplicationState();
    ASSERT_EQ(appState, Bell::ApplicationState::Initializing);

    // Close
    app->Close();
    // Delete the app here, normally EntryPoint.h would do this
    delete app;
}