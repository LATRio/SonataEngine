#include "sandbox.h"

Sonata::Application* CreateApplication()
{
    return new Sandbox();
}
