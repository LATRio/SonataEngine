#pragma once
#include <sonata.hpp>

class Sandbox final : public Sonata::Application
{
public:
    Sandbox() = default;
    ~Sandbox() override = default;

    void Init(int p_Width, int p_Height, std::string_view p_Title) override;
};
