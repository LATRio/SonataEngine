#pragma once
#include "logger/log.hpp"

extern Sonata::Application* CreateApplication();

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    Sonata::Log::Init();

    Sonata::Application* app = CreateApplication();
    // TODO: Fetch settings from config file
    constexpr Sonata::WindowProps props{
        1280,
        720,
        "Sonata Engine",
        true,
    };
    app->Init(props);
    app->Loop();

    delete app;
    return EXIT_SUCCESS;
}

