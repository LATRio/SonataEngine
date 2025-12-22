#pragma once
#include "events/event.hpp"

namespace Sonata {

class Layer {
public:
    explicit Layer(const std::string_view p_DebugName)
        : m_DebugName(p_DebugName)
    {}
    virtual ~Layer() = default;

    virtual void OnAttach() {};
    virtual void OnDetach() {};
    virtual void OnUpdate([[maybe_unused]] float p_DeltaTime) {};
    virtual void OnImGuiRender() {};
    virtual void OnEvent([[maybe_unused]] Event& p_Event) {}

    [[nodiscard]] std::string_view GetName() const { return m_DebugName; }

private:
    std::string m_DebugName;
};

} // namespace Sonata
