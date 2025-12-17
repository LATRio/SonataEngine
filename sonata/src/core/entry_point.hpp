#pragma once
#include "profiler/instrumentor.hpp"

extern Sonata::Application* CreateApplication();

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    Sonata::Log::Init();

    SN_PROFILE_BEGIN_SESSION("Initialization", "SonataProfile-Initialization.json");
    Sonata::Application* app = CreateApplication();
    // TODO: Fetch settings from config file
    constexpr Sonata::WindowProps props{
        1280,
        720,
        "Sonata Engine",
        true,
    };
    app->Init(props);
    SN_PROFILE_END_SESSION();

    SN_PROFILE_BEGIN_SESSION("Runtime", "SonataProfile-Runtime.json");
    app->Loop();
    SN_PROFILE_END_SESSION();

    SN_PROFILE_BEGIN_SESSION("Shutdown", "SonataProfile-Shutdown.json");
    delete app;
    SN_PROFILE_END_SESSION();

    return EXIT_SUCCESS;
}

