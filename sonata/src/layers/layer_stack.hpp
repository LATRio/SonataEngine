#pragma once
#include "layer.hpp"

namespace Sonata {

class LayerStack {
public:
    ~LayerStack();

    void PushLayer(Layer* p_Layer);
    void PopLayer(Layer* p_Layer);
    void PushOverlay(Layer* p_Overlay);
    void PopOverlay(Layer* p_Overlay);

    void OnImGuiRender() const;
    void OnUpdate(float p_DeltaTime) const;
    void OnEvent(Event& e);

private:
    std::vector<Layer*> m_Layers;
    unsigned int m_LayerInsertIndex{};
};

} // namespace Sonata
