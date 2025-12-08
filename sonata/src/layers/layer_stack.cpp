#include "layer_stack.hpp"

namespace Sonata {

LayerStack::LayerStack()
{
}

LayerStack::~LayerStack()
{
    for (auto* layer : m_Layers)
    {
        layer->OnDetach();
        delete layer;
    }
}

void LayerStack::PushLayer(Layer* p_Layer)
{
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, p_Layer);
    ++m_LayerInsertIndex;
}

void LayerStack::PopLayer(Layer* p_Layer)
{
    if (const auto it = std::ranges::find(m_Layers, p_Layer); it != m_Layers.end())
    {
        p_Layer->OnDetach();
        m_Layers.erase(it);
        --m_LayerInsertIndex;
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
        p_Overlay->OnDetach();
        m_Layers.erase(it);
    }
}
void LayerStack::OnImGuiRender() const
{
    for (auto* layer : m_Layers)
    {
        layer->OnImGuiRender();
    }
}
void LayerStack::OnUpdate(const float p_DeltaTime) const
{
    for (auto* layer : m_Layers)
    {
        layer->OnUpdate(p_DeltaTime);
    }
}

void LayerStack::OnEvent(Event& e)
{
    for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
    {
        if (e.Handled) break;
        (*it)->OnEvent(e);
    }
}

} // namespace Sonata
