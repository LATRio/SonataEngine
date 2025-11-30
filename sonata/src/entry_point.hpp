#pragma once
#include "log.hpp"

extern Sonata::Application* CreateApplication();

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    Sonata::Log::Init();

    Sonata::Application* app = CreateApplication();
    // TODO: Fetch settings from config file
    // TODO: Create a window and other systems using those settings
    app->Init(1280, 720, "Sonata Engine");
    app->Loop();
    // TODO: Do some shutdown routine if needed
    delete app;

    SN_ENGINE_INFO("Exiting main");
    return EXIT_SUCCESS;
}

