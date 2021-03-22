#include <gtest/gtest.h>

#include <Bell.h>

class ApplicationFicture : public ::testing::Test
{
protected:
    void SetUp() override
    {
        Bell::Log::Init();

        Bell::WindowProps props;
        props.Title = "Test App";
        props.Width = 1080;
        props.Height = 640;

        app = new Bell::Application(props);
    }

    void TearDown() override
    {
        // Delete the app here, normally EntryPoint.h would do this
        delete app;
    }

    Bell::Application *app;
};

TEST(BellTests, BellLogInit)
{
    Bell::Log::Init();
    ASSERT_TRUE(Bell::Log::GetClientLogger() != nullptr);
    ASSERT_TRUE(Bell::Log::GetCoreLogger() != nullptr);
}

TEST_F(ApplicationFicture, ApplicationCreation)
{
    Bell::ApplicationState appState = app->GetApplicationState();
    ASSERT_EQ(appState, Bell::ApplicationState::Initializing);

    // Close
    app->Close();
}