#pragma once

extern Sonata::Application* CreateApplication();

int main(int argc, char *argv[])
{
    Sonata::Application* app = CreateApplication();
    app->Loop();
    delete app;
}

