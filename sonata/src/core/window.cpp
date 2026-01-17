#include "window.hpp"
#include "SDL3/SDL.h"
#include "events/app_event.hpp"
#include "events/key_event.hpp"
#include "events/mouse_event.hpp"
#include "profiler/instrumentor.hpp"
#include "rendering/opengl/opengl_context.hpp"
#include "rendering/renderer.hpp"

namespace Sonata {

static bool sdlInitialized = false;

Window::Window(const WindowProps& p_Props)
{
    SN_PROFILE_FUNCTION();

    if (!sdlInitialized)
    {
        const int success = SDL_Init(SDL_INIT_VIDEO);
        SN_ASSERT_MSG(success, SDL_GetError());

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        sdlInitialized = true;

        int version{SDL_GetVersion()};
        SN_ENGINE_INFO("Window Initialized! (powered by SDL-{}.{})", version / 1000000, (version % 1000000) / 1000);
    }

    m_WindowData = {p_Props.m_Width, p_Props.m_Height, p_Props.m_Title, p_Props.m_VSync, m_Window};

    {
        SN_PROFILE_SCOPE("glfwCreateWindow");

        SDL_WindowFlags windowFlags{SDL_WINDOW_RESIZABLE};
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::OpenGL:
                windowFlags |= SDL_WINDOW_OPENGL;
                break;
            case RendererAPI::API::Vulkan:
                windowFlags |= SDL_WINDOW_VULKAN;
                break;
            default:
                break;
        }
        m_Window =
            SDL_CreateWindow(m_WindowData.m_Title.data(), m_WindowData.m_Width, m_WindowData.m_Height, windowFlags);
        SN_ASSERT_MSG(m_Window, std::format("Failed to create window: {}", SDL_GetError()));
    }

    m_RenderContext = RenderContext::Create(m_Window);
    m_RenderContext->Init();

    // glfwSetWindowUserPointer(m_Window, &m_WindowData);
    SetVSync(m_WindowData.m_VSync);

    SDL_ShowWindow(m_Window);

    SDL_AddEventWatch(
        [](void* p_Userdata, SDL_Event* p_Event) -> bool {
            switch (p_Event->type)
            {
                case SDL_EVENT_WINDOW_RESIZED: {
                    const WindowData& data{*static_cast<WindowData*>(p_Userdata)};

                    EventWindowResize event{p_Event->window.data1, p_Event->window.data2};
                    data.m_Callback(event);

                    return true;
                }
                case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED: {
                    const WindowData& data{*static_cast<WindowData*>(p_Userdata)};

                    int width, height;
                    SDL_GetWindowSizeInPixels(data.m_Window, &width, &height);
                    EventFramebufferResize event{width, height};
                    data.m_Callback(event);

                    return true;
                }
                case SDL_EVENT_QUIT: {
                    const WindowData& data{*static_cast<WindowData*>(p_Userdata)};

                    EventWindowClose event;
                    data.m_Callback(event);

                    return true;
                }
                case SDL_EVENT_WINDOW_MINIMIZED: {
                    const WindowData& data{*static_cast<WindowData*>(p_Userdata)};

                    EventWindowMinimize event{static_cast<bool>(p_Event->window.data1)};
                    data.m_Callback(event);

                    return true;
                }
                case SDL_EVENT_KEY_DOWN: {
                    const WindowData& data{*static_cast<WindowData*>(p_Userdata)};

                    EventKeyPressed event{static_cast<Key>(p_Event->key.key), p_Event->key.repeat};
                    data.m_Callback(event);

                    return true;
                }
                case SDL_EVENT_KEY_UP: {
                    const WindowData& data{*static_cast<WindowData*>(p_Userdata)};

                    EventKeyReleased event{static_cast<Key>(p_Event->key.key)};
                    data.m_Callback(event);

                    return true;
                }
                case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    const WindowData& data{*static_cast<WindowData*>(p_Userdata)};

                    EventMouseButtonPressed event{static_cast<MouseButton>(p_Event->button.button)};
                    data.m_Callback(event);

                    return true;
                }
                case SDL_EVENT_MOUSE_BUTTON_UP: {
                    const WindowData& data{*static_cast<WindowData*>(p_Userdata)};

                    EventMouseButtonReleased event{static_cast<MouseButton>(p_Event->button.button)};
                    data.m_Callback(event);

                    return true;
                }
                case SDL_EVENT_MOUSE_WHEEL: {
                    const WindowData& data{*static_cast<WindowData*>(p_Userdata)};

                    EventMouseScrolled event{p_Event->wheel.x, p_Event->wheel.y};
                    data.m_Callback(event);

                    return true;
                }
                case SDL_EVENT_MOUSE_MOTION: {
                    const WindowData& data{*static_cast<WindowData*>(p_Userdata)};

                    EventMouseMoved event{p_Event->motion.x, p_Event->motion.y};
                    data.m_Callback(event);

                    return true;
                }
                default:
                    return false;
            }
        },
        &m_WindowData);
}

Window::~Window()
{
    SN_PROFILE_FUNCTION();

    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Window::PollEvents() const
{
    SN_PROFILE_FUNCTION();

    SDL_PumpEvents();
}

void Window::SwapBuffers() const
{
    SN_PROFILE_FUNCTION();

    m_RenderContext->SwapBuffers();
}

void Window::SetEventCallback(const EventCallbackFn& p_Callback)
{
    m_WindowData.m_Callback = p_Callback;
}

void Window::SetVSync(const bool p_Enable)
{
    SN_PROFILE_FUNCTION();

    SDL_GL_SetSwapInterval(p_Enable);
    m_WindowData.m_VSync = p_Enable;
}

bool Window::IsVSync() const
{
    return m_WindowData.m_VSync;
}

} // namespace Sonata
