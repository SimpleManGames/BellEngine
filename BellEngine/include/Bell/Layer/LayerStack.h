// Layer Stack
// Used for managing game elements in an easy queue way
// ----------------------------------------------------

#ifndef _LAYER_STACK_H
#define _LAYER_STACK_H

#include "Bell/Base/Core.h"
#include "Layer.h"

#include <vector>

namespace Bell
{
    typedef std::vector<Layer *> LayerStackVec;
    typedef std::vector<Layer *>::iterator LayerStackIt;

    class LayerStack
    {
    public:
        LayerStack() = default;
        ~LayerStack();

        /**
         * @brief Inserts a layer to the front half of the stack
         * Layers get inserted to the back of the front half of the stack
         * 
         * @param layer 
         */
        void InsertLayer(Layer *layer);
        /**
         * @brief Inserts a overlay layer to the back of the stack
         * Overlays get pushed to the second half of the stack
         * 
         * @param overlay Ptr to the overlay we are pushing
         */
        void InsertOverlay(Layer *overlay);
        /**
         * @brief Remove the passed layer off the stack
         * Does not delete the layer just takes it off this stack
         * 
         * @param layer Ptr to the layer we want to pop off
         */
        void PopLayer(Layer *layer);
        /**
         * @brief Remove the passed overlay layer off the stack
         * Does not delete the overlay just takes it off this stack
         * 
         * @param overlay Ptr to the overlay we want to pop off
         */
        void PopOverlay(Layer *overlay);

        LayerStackIt begin() { return m_Layers.begin(); }
        LayerStackIt end() { return m_Layers.end(); }

        int32_t LayerCount() const { return m_Layers.size(); }
        const LayerStackVec GetAllLayers() const { return m_Layers; }

        /**
         * @brief Clears the entire Layer Stack vector and resets the Insert Index
         * 
         */
        void ClearAllLayers();

        operator bool() const;
        
    private:
        LayerStackVec m_Layers;
        // Iterator used to determine were we are placing layers onto the stack
        unsigned int m_LayerInsertIndex = 0;
    };
}

#endif // !_LAYER_STACK_H