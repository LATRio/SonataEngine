#include "layer_stack.hpp"

#include "profiler/instrumentor.hpp"

namespace Sonata {

LayerStack::~LayerStack()
{
    SN_PROFILE_FUNCTION();

    for (auto* layer : m_Layers)
    {
        layer->OnDetach();
        delete layer;
    }
}

void LayerStack::PushLayer(Layer* p_Layer)
{
    SN_PROFILE_FUNCTION();

    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, p_Layer);
    p_Layer->OnAttach();
    ++m_LayerInsertIndex;
}

void LayerStack::PopLayer(Layer* p_Layer)
{
    SN_PROFILE_FUNCTION();

    if (const auto it = std::ranges::find(m_Layers, p_Layer); it != m_Layers.end())
    {
        p_Layer->OnDetach();
        m_Layers.erase(it);
        --m_LayerInsertIndex;
    }
}

void LayerStack::PushOverlay(Layer* p_Overlay)
{
    SN_PROFILE_FUNCTION();

    m_Layers.emplace_back(p_Overlay);
    p_Overlay->OnAttach();
}

void LayerStack::PopOverlay(Layer* p_Overlay)
{
    SN_PROFILE_FUNCTION();

    if (const auto it = std::ranges::find(m_Layers, p_Overlay); it != m_Layers.end())
    {
        p_Overlay->OnDetach();
        m_Layers.erase(it);
    }
}
void LayerStack::OnImGuiRender() const
{
    SN_PROFILE_FUNCTION();

    for (auto* layer : m_Layers)
    {
        layer->OnImGuiRender();
    }
}
void LayerStack::OnUpdate(const float p_DeltaTime) const
{
    SN_PROFILE_FUNCTION();

    for (auto* layer : m_Layers)
    {
        layer->OnUpdate(p_DeltaTime);
    }
}

void LayerStack::OnEvent(Event& e)
{
    SN_PROFILE_FUNCTION();

    for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
    {
        if (e.Handled) break;
        (*it)->OnEvent(e);
    }
}

} // namespace Sonata
