#include <gtest/gtest.h>

#include <Bell.h>

class ApplicationFicture : public ::testing::Test
{
protected:
    static void SetUpTestSuite()
    {
        Bell::Log::Init();

        Bell::WindowProps props;
        props.Title = "Test App";
        props.Width = 1080;
        props.Height = 640;

        // Unique ptr to avoid SEH exceptions from using raw ptr and delete
        app = new Bell::Application(props);
    }

    static void TearDownTestSuite()
    {
        Bell::Log::Shutdown();
        delete app;
        app = nullptr;
    }

    void SetUp() override {}

    void TearDown() override {}

    static Bell::Application *app;
};

Bell::Application* ApplicationFicture::app = nullptr;

class TestLayer : public Bell::Layer
{
public:
    TestLayer()
    {
    }

    virtual void OnUpdate(Bell::Timestep deltaTime) override
    {
        m_CurrentTimeIncrement += deltaTime;
        if (m_CurrentTimeIncrement >= EXIT_TIME)
        {
            Bell::Application::Get().Close();
        }
    }

private:
    const float EXIT_TIME = 1.0f;
    float m_CurrentTimeIncrement = 0.0f;
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

TEST_F(ApplicationFicture, LayerControl)
{
    int oldCount = app->LayerStackCount();

    app->PushLayer(new TestLayer());
    int count = app->LayerStackCount();
    EXPECT_EQ(count, oldCount + 1);
}

TEST_F(ApplicationFicture, ApplicationRun)
{
    app->PushLayer(new TestLayer());
    app->Run();
}