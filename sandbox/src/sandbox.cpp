#include "sandbox.hpp"

Sonata::Application* CreateApplication()
{
    return new Sandbox();
}
