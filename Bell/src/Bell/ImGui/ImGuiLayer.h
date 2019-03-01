#ifndef IMGUI_LAYER
#define IMGUI_LAYER

#include "Bell/KeyCodes.h"
#include "Bell/MouseButtonCodes.h"
#include "Bell/Layer/Layer.h"
#include "Bell/Events/KeyEvent.h"
#include "Bell/Events/MouseEvent.h"
#include "Bell/Events/ApplicationEvent.h"

namespace Bell
{
    class BELL_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();

        void OnUpdate();
        void OnEvent(Event& event);

    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);
        bool OnWindowResizedEvent(WindowResizeEvent& e);
    private:
        float m_Time = 0.0f;
    };
}

#endif // !IMGUI_LAYER