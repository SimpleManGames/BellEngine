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
        Bell::Log::Shutdown();
        // Delete the app here, normally EntryPoint.h would do this
        delete app;
    }

    Bell::Application *app;
};

class TestLayer : public Bell::Layer
{
public:
    TestLayer(Bell::Application *app)
        : m_App(app)
    {
    }

    virtual void OnUpdate(Bell::Timestep deltaTime) override
    {
        m_CurrentTimeIncrement += deltaTime;
        if (m_CurrentTimeIncrement >= EXIT_TIME)
        {
            m_App->Get().Close();
        }
    }

private:
    const float EXIT_TIME = 1.0f;
    float m_CurrentTimeIncrement = 0.0f;
    Bell::Application *m_App;
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
}

TEST_F(ApplicationFicture, LayerAdd)
{
    int oldCount = app->LayerStackCount();

    app->PushLayer(new TestLayer(app));
    int count = app->LayerStackCount();
    EXPECT_EQ(count, oldCount + 1);
}

TEST_F(ApplicationFicture, ApplicationRun)
{
    //app->Run();
}