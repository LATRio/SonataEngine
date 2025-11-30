#pragma once
#include "events/event.hpp"

namespace Sonata {

class Layer {
public:
    explicit Layer(const std::string& p_DebugName);
    virtual ~Layer() = default;

    virtual void OnAttach() {};
    virtual void OnDetach() {};
    virtual void OnUpdate() {};
    virtual void OnEvent(Event& p_Event) {}

    [[nodiscard]] const std::string& GetName() const { return m_DebugName; }

private:
    std::string m_DebugName;
};

}
