#pragma once
#define SDL_MAIN_USE_CALLBACKS 1
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuseless-cast"
#endif
#include <SDL3/SDL_main.h>
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
#include "profiler/instrumentor.hpp"

extern Sonata::Application* CreateApplication();
inline Sonata::Application* app{};

inline SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    SN_PROFILE_SCOPE("Initialization");
    Sonata::Log::Init();

    if (!SDL_SetAppMetadata("Sonata Engine", "0.0", "com.latrio.sonataengine"))
    {
        return SDL_APP_FAILURE;
    }

    // SN_PROFILE_BEGIN_SESSION("Initialization", "SonataProfile-Initialization.json");

    app = CreateApplication();
    // TODO: Fetch settings from config file
    constexpr Sonata::WindowProps props{
        1280,
        720,
        "Sonata Engine",
        true,
    };
    app->Init(props);
    // SN_PROFILE_END_SESSION();

    // SN_PROFILE_BEGIN_SESSION("Runtime", "SonataProfile-Runtime.json");
    return SDL_APP_CONTINUE;
}

inline SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    SN_PROFILE_SCOPE("Application Event");

    ImGui_ImplSDL3_ProcessEvent(event);
    return SDL_APP_CONTINUE;
}

inline SDL_AppResult SDL_AppIterate(void*)
{
    SN_PROFILE_SCOPE("Application Loop");
    return app->Loop();
}

inline void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    SN_PROFILE_SCOPE("Shutdown");
    // SN_PROFILE_END_SESSION();

    // SN_PROFILE_BEGIN_SESSION("Shutdown", "SonataProfile-Shutdown.json");
    delete app;
    // SN_PROFILE_END_SESSION();
}
