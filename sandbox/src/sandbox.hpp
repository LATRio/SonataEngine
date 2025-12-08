#pragma once
#include <application.hpp>

class Sandbox final : public Sonata::Application
{
public:
    Sandbox() = default;
    ~Sandbox() override = default;

    void Init(const Sonata::WindowProps& p_Props) override;
};
