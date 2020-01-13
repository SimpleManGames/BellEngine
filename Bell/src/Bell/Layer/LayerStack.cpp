#include "bpch.h"
#include "LayerStack.h"

namespace Bell
{

    LayerStack::~LayerStack()
    {
        // Delete all of the pointers from m_Layers
        for (Layer* layer : m_Layers)
        {
            B_CORE_INFO("Detaching {0} layer", layer->GetName());
            layer->OnDetach();
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        // Set the new point of m_LayerInsert while creating
        // a placing the layer of the stack at the old insert
        B_CORE_INFO("Pushing {0} layer", layer->GetName());
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
        m_LayerInsertIndex++;
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        // Add the overlay to the back half so they are
        // rendered last to be on top of everything
        B_CORE_INFO("Pushing {0} overlay", overlay->GetName());
        m_Layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        // Gets the layer we are asking for
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if (it != m_Layers.end())
        {
            // Remove it from the stack
            B_CORE_INFO("Popping {0} layer", layer->GetName());
            m_Layers.erase(it);
            m_LayerInsertIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        // Gets the overlay we are asking for
        auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
        if (it != m_Layers.end())
        {
            // Remove it from the stack
            B_CORE_INFO("Popping {0} overlay", overlay->GetName());
            m_Layers.erase(it);
        }
    }
    LayerStack::operator bool() const
    {
        return m_Layers.empty();
    }
}