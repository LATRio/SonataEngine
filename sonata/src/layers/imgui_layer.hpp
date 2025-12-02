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
    void OnImGuiRender() override;
    void OnEvent(Event& event) override;
    void Begin();
    void End();

private:
    float m_Time{};
};

}
