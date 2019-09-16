// Layer
// Single layer for the Layer Stack
// --------------------------------

#ifndef _LAYER_H
#define _LAYER_H

#include "Bell/Core.h"
#include "Bell/Core/Timestep.h"
#include "Bell/Events/Event.h"

namespace Bell
{
    class BELL_API Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        // Acts when pushed to a stack
        virtual void OnAttach() {}
        // Acts when removed from a stack
        virtual void OnDetach() {}
        // Calls when the stack needs to be updated
        virtual void OnUpdate(Timestep deltaTime) {}
        virtual void OnImGuiRender() {}
        // Used for when the layer has an event to be handled
        virtual void OnEvent(Event& e) {}

        inline const std::string& GetName() const { return m_DebugName; }
    protected:
        // Debug name should only be used for such
        // Might macro to remove this during dist builds
        std::string m_DebugName;
    };

}

#endif // !_LAYER_H