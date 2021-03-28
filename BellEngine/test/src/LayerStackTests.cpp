#include <gtest/gtest.h>

#include <Bell/Layer/LayerStack.h>
#include <Bell/Layer/Layer.h>

class LayerStackFixture : public ::testing::Test
{
protected:
    static void SetUpTestSuite()
    {
        Bell::Log::Init("LayerStack Tests", "Dummy");

        s_layerStack = new Bell::LayerStack();
    }

    static void TearDownTestSuite()
    {
        delete s_layerStack;
        s_layerStack = nullptr;

        Bell::Log::Shutdown();
    }

    void SetUp() override
    {
    }

    void TearDown() override
    {
        s_layerStack->ClearAllLayers();
    }

    static Bell::LayerStack *s_layerStack;
};

Bell::LayerStack *LayerStackFixture::s_layerStack = nullptr;

class TestLayer : public Bell::Layer
{
public:
    TestLayer(const std::string &name)
        : Layer(name)
    {
    }

    virtual void OnUpdate(Bell::Timestep deltaTime) override
    {
        m_CurrentTimeIncrement += deltaTime;
        if (m_CurrentTimeIncrement >= EXIT_TIME)
        {
        }
    }

private:
    const float EXIT_TIME = 1.0f;
    float m_CurrentTimeIncrement = 0.0f;
};

TEST_F(LayerStackFixture, LayerStack_PushLayer)
{
    int oldCount = s_layerStack->LayerCount();

    s_layerStack->InsertLayer(new TestLayer("Layer"));

    int count = s_layerStack->LayerCount();
    EXPECT_EQ(count, oldCount + 1);
}

TEST_F(LayerStackFixture, LayerStack_PushOverlay)
{
    int oldCount = s_layerStack->LayerCount();

    s_layerStack->InsertOverlay(new TestLayer("Overlay"));

    int count = s_layerStack->LayerCount();
    EXPECT_EQ(count, oldCount + 1);
}

TEST_F(LayerStackFixture, LayerStack_ClearAllLayers)
{
    // Add a bunch of layers
    s_layerStack->InsertLayer(new Bell::Layer());
    s_layerStack->InsertLayer(new Bell::Layer());
    s_layerStack->InsertLayer(new Bell::Layer());
    s_layerStack->InsertOverlay(new Bell::Layer());
    s_layerStack->InsertLayer(new Bell::Layer());

    s_layerStack->ClearAllLayers();

    ASSERT_EQ(s_layerStack->LayerCount(), 0);

    // Check if the stack is still usable after clear
    s_layerStack->InsertLayer(new Bell::Layer());
}

TEST_F(LayerStackFixture, LayerStack_ValidatePlacement)
{
    TestLayer *layer = new TestLayer("Layer");
    TestLayer *inbetween = new TestLayer("Inbetween");
    TestLayer *overlay = new TestLayer("Overlay");


    // Test regular layer first
    s_layerStack->InsertLayer(layer);
    s_layerStack->InsertLayer(inbetween);
    s_layerStack->InsertOverlay(overlay);

    EXPECT_TRUE(s_layerStack->GetAllLayers().front() == layer);
    EXPECT_TRUE(s_layerStack->GetAllLayers().back() == overlay);

    s_layerStack->ClearAllLayers();

    // Test overlay first
    s_layerStack->InsertOverlay(overlay);
    s_layerStack->InsertLayer(layer);
    s_layerStack->InsertLayer(inbetween);

    EXPECT_TRUE(s_layerStack->GetAllLayers().front() == layer);
    EXPECT_TRUE(s_layerStack->GetAllLayers().back() == overlay);
}