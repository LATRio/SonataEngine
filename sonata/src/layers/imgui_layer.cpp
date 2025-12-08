#include "imgui_layer.hpp"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#pragma GCC diagnostic pop

#include "application.hpp"

namespace Sonata {

ImGuiLayer::ImGuiLayer()
    : Layer("ImGuiLayer")
{
}

void ImGuiLayer::OnAttach()
{
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui_ImplGlfw_InitForOpenGL(Application::GetInstance()->GetWindow()->GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void ImGuiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::OnImGuiRender()
{
    static bool show{true};
    ImGui::ShowDemoWindow(&show);
}

void ImGuiLayer::OnEvent(Event& event)
{
}

void ImGuiLayer::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::End()
{
    ImGuiIO& io = ImGui::GetIO();
    const Window* window = Application::GetInstance()->GetWindow();
    io.DisplaySize = ImVec2(window->GetWidth<float>(), window->GetHeight<float>());

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* prev_context{glfwGetCurrentContext()};
        ImGui::UpdatePlatformWindows();
        glfwMakeContextCurrent(prev_context);
    }
}

}