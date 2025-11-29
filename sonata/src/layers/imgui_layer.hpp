#pragma once
#include "layer.hpp"

namespace Sonata {

class Window;

class ImGuiLayer : public Layer {
public:
    ImGuiLayer();
    ~ImGuiLayer() override;

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate() override;
    void OnEvent(Event& event) override;

private:
    float m_Time{};
};

}
