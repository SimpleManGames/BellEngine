// ImGUI Layer
// Specific layer for ImGUI elements
// ---------------------------------

#ifndef _IMGUI_LAYER_H
#define _IMGUI_LAYER_H

#include "Bell/Base/Input/KeyCodes.h"
#include "Bell/Base/Input/MouseButtonCodes.h"
#include "Bell/Layer/Layer.h"
#include "Bell/Base/Events/KeyEvent.h"
#include "Bell/Base/Events/MouseEvent.h"
#include "Bell/Base/Events/ApplicationEvent.h"

namespace Bell
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;
        virtual void OnEvent(Event& e) override;

        void Begin();
        void End();

    private:
        float m_Time = 0.0f;
    };
}

#endif // !_IMGUI_LAYER_H