// Layer Stack
// Used for managing game elements in an easy queue way
// ----------------------------------------------------

#ifndef _LAYER_STACK_H
#define _LAYER_STACK_H

#include "Bell/Core/Core.h"
#include "Layer.h"

#include <vector>

namespace Bell
{
    typedef std::vector<Layer*> LayerStackVec;
    typedef  std::vector<Layer*>::iterator LayerStackIt;

    class LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        // Add a layer to the front of the stack
        // Layers get pushed to the front half of the stack
        void PushLayer(Layer* layer);
        // Add a overlay specific layer to the front of the stack
        // Overlays get pushed to the second half of the stack
        void PushOverlay(Layer* overlay);
        // Remove the passed layer off the stack
        // Does not delete the layer just takes it off this stack
        void PopLayer(Layer* layer);
        // Remove the passed overlay layer off the stack
        // Does not delete the overlay just takes it off this stack
        void PopOverlay(Layer* overlay);

        LayerStackIt begin() { return m_Layers.begin(); }
        LayerStackIt end() { return m_Layers.end(); }

    private:
        LayerStackVec m_Layers;
        // Iterator used to determine were we are placing layers onto the stack
        unsigned int m_LayerInsertIndex = 0;
    };
}

#endif // !_LAYER_STACK_H