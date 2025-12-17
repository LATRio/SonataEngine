#pragma once
#include "layer.hpp"

namespace Sonata {

class Window;

class ImGuiLayer final : public Layer {
public:
    ImGuiLayer();
    ~ImGuiLayer() override = default;

    void OnAttach() override;
    void OnDetach() override;
    void OnEvent(Event& event) override;
    void Begin() const;
    void End() const;

private:
    float m_Time{};
};

}
