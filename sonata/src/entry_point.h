#pragma once
#include "log.h"

extern Sonata::Application* CreateApplication();

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    Sonata::Log::Init();

    Sonata::Application* app = CreateApplication();
    // TODO: Fetch settings from config file
    // TODO: Create a window and other systems using those settings
    app->InitWindow(1280, 720, "Sonata Engine");
    app->Loop();
    // TODO: Do some shutdown routine if needed
    delete app;
}

