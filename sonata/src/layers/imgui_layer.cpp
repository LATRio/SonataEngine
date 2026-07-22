#include "imgui_layer.hpp"
#include "imgui_wrapper.hpp"
#include "SDL3/SDL_video.h"

#include "core/application.hpp"
#include "profiler/instrumentor.hpp"
#include "rendering/renderer.hpp"

namespace Sonata {

ImGuiLayer::ImGuiLayer()
    : Layer("ImGuiLayer")
{}

void ImGuiLayer::OnAttach()
{
    SN_PROFILE_FUNCTION;

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::OpenGL: {
            ImGui_ImplSDL3_InitForOpenGL(SDL_GL_GetCurrentWindow(), SDL_GL_GetCurrentContext());
            ImGui_ImplOpenGL3_Init("#version 460");
            break;
        }
        case RendererAPI::API::Vulkan: {
            // ImGui_ImplVulkan_InitInfo vulkanInfo{
            //     .ApiVersion = ,
            //     .Instance = ,
            //     .PhysicalDevice = ,
            //     .Device = ,
            //     .QueueFamily = ,
            //     .Queue = ,
            //     .DescriptorPool = ,
            //     .DescriptorPoolSize = ,
            //     .MinImageCount = ,
            //     .ImageCount = ,
            //     .PipelineCache = ,
            //     .PipelineInfoMain = ,
            //     .PipelineInfoForViewports = ,
            //     .UseDynamicRendering = ,
            //     .Allocator = ,
            //     .CheckVkResultFn = ,
            //     .MinAllocationSize = ,
            //     .CustomShaderVertCreateInfo = ,
            //     .CustomShaderFragCreateInfo =
            // };
            // ImGui_ImplVulkan_Init(&vulkanInfo);
            break;
        }
        default:
            break;
    }
}

void ImGuiLayer::OnDetach()
{
    SN_PROFILE_FUNCTION;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::Begin() const
{
    SN_PROFILE_FUNCTION;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::End() const
{
    SN_PROFILE_FUNCTION;

    ImGuiIO& io = ImGui::GetIO();
    const Window* window = Application::GetInstance()->GetWindow();
    io.DisplaySize = ImVec2(window->GetWidth<float>(), window->GetHeight<float>());

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        SDL_GLContext prev_context{SDL_GL_GetCurrentContext()};
        ImGui::UpdatePlatformWindows();
        SDL_GL_MakeCurrent(SDL_GL_GetCurrentWindow(), prev_context);
    }
}

} // namespace Sonata
