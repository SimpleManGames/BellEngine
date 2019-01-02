#include "bpch.h"
#include "LayerStack.h"

namespace Bell
{
    LayerStack::LayerStack()
    {
        // Sets the pointer for the front of the stack
        m_LayerInsert = m_Layers.begin();
    }

    LayerStack::~LayerStack()
    {
        // Delete all of the pointers from m_Layers
        for (Layer* layer : m_Layers)
            delete layer;
    }

    void LayerStack::PushLayer(Layer * layer)
    {
        // Set the new point of m_LayerInsert while creating
        // a placing the layer of the stack at the old insert
        m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
    }

    void LayerStack::PushOverlay(Layer * overlay)
    {
        // Add the overlay to the back half so they are
        // rendered last to be on top of everything
        m_Layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer * layer)
    {
        // Gets the layer we are asking for
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if (it != m_Layers.end())
        {
            // Remove it from the stack
            m_Layers.erase(it);
            m_LayerInsert--;
        }
    }

    void LayerStack::PopOverlay(Layer * overlay)
    {
        // Gets the overlay we are asking for
        auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
        if (it != m_Layers.end())
            // Remove it from the stack
            m_Layers.erase(it);
    }
}