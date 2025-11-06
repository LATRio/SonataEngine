#pragma once
#include <sonata.h>

class Sandbox : public Sonata::Application
{
public:
    Sandbox()
    {
        SN_APP_ERR("Initialized Sandbox!");
    }
    ~Sandbox() override {}
};
