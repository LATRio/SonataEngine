#include "layer_stack.hpp"

namespace Sonata {

LayerStack::LayerStack()
    : m_LayerIterator(m_Layers.begin())
{
}

LayerStack::~LayerStack()
{
    for (auto* layer : m_Layers)
    {
        delete layer;
    }
}

void LayerStack::PushLayer(Layer* p_Layer)
{
    m_LayerIterator = m_Layers.emplace(m_LayerIterator, p_Layer);
    p_Layer->OnAttach();
}

void LayerStack::PopLayer(Layer* p_Layer)
{
    if (const auto it = std::ranges::find(m_Layers, p_Layer); it != m_Layers.end())
    {
        m_Layers.erase(it);
        --m_LayerIterator;
    }
}

void LayerStack::PushOverlay(Layer* p_Overlay)
{
    m_Layers.emplace_back(p_Overlay);
    p_Overlay->OnAttach();
}

void LayerStack::PopOverlay(Layer* p_Overlay)
{
    if (const auto it = std::ranges::find(m_Layers, p_Overlay); it != m_Layers.end())
    {
        m_Layers.erase(it);
    }
}

} // namespace Sonata
