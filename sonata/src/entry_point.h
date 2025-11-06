#pragma once
#include "log.h"

extern Sonata::Application* CreateApplication();

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    Sonata::Log::Init();
    Sonata::Log::Warn(Sonata::LoggerType::Engine, "Initialized Log!");
    Sonata::Log::Info(Sonata::LoggerType::App, "Initialized Log!");

    Sonata::Application* app = CreateApplication();
    app->Loop();
    delete app;
}

