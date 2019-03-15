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

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();

    private:
        float m_Time = 0.0f;
    };
}

#endif // !IMGUI_LAYER