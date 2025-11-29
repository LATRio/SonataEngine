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

    std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
    std::vector<Layer*>::iterator end() { return m_Layers.end(); }

private:
    std::vector<Layer*> m_Layers;
    std::vector<Layer*>::iterator m_LayerIterator;
};

}
