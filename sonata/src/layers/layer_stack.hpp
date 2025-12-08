#pragma once
#include "layer.hpp"

namespace Sonata {

class LayerStack {
public:
    LayerStack();
    ~LayerStack();

    void PushLayer(Layer* p_Layer);
    void PopLayer(Layer* p_Layer);
    void PushOverlay(Layer* p_Overlay);
    void PopOverlay(Layer* p_Overlay);

    void OnImGuiRender() const;
    void OnUpdate(float p_DeltaTime) const;
    void OnEvent(Event& e);

    // [[nodiscard]] std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
    // [[nodiscard]] std::vector<Layer*>::iterator end() { return m_Layers.end(); }
    // [[nodiscard]] std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
    // [[nodiscard]] std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }
    //
    // [[nodiscard]] std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
    // [[nodiscard]] std::vector<Layer*>::const_iterator end() const { return m_Layers.end(); }
    // [[nodiscard]] std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
    // [[nodiscard]] std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }


private:
    std::vector<Layer*> m_Layers;
    unsigned int m_LayerInsertIndex{};
};

}
