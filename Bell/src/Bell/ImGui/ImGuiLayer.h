#ifndef IMGUI_LAYER
#define IMGUI_LAYER

#include "Bell/Layer/Layer.h"

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
        float m_Time = 0.0f;
    };
}

#endif // !IMGUI_LAYER