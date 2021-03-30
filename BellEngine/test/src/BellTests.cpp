#include <gtest/gtest.h>

#include <Bell.h>

#include "TestLayer.h"

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

Bell::Application *ApplicationFicture::app = nullptr;

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

    app->InsertLayer(new TestLayer("Layer"));
    int count = app->LayerStackCount();
    EXPECT_EQ(count, oldCount + 1);
}

TEST_F(ApplicationFicture, Application_InsertLayer_Calls_OnAttach)
{
    TestLayer *layer = new TestLayer();
    app->InsertLayer(layer);

    ASSERT_TRUE(layer->Attached());
}

TEST_F(ApplicationFicture, Application_PopLayer_Calls_OnDetach)
{
    TestLayer *layer = new TestLayer();
    app->InsertLayer(layer);

    ASSERT_TRUE(layer->Attached());

    
}

TEST_F(ApplicationFicture, ApplicationRun)
{
    app->InsertLayer(new TestLayer("Layer"));
    app->Run();
}