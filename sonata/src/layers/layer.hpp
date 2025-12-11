#pragma once
#include "events/event.hpp"

namespace Sonata {

class Layer {
public:
    explicit Layer(std::string_view p_DebugName);
    virtual ~Layer() = default;

    virtual void OnAttach() {};
    virtual void OnDetach() {};
    virtual void OnUpdate(float p_DeltaTime) {};
    virtual void OnImGuiRender() {};
    virtual void OnEvent(Event& p_Event) {}

    [[nodiscard]] std::string_view GetName() const { return m_DebugName; }

private:
    std::string m_DebugName;
};

}
