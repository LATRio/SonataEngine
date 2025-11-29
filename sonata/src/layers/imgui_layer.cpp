#include "imgui_layer.hpp"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "application.hpp"

namespace Sonata {

ImGuiLayer::ImGuiLayer()
    : Layer("ImGuiLayer")
{
}

ImGuiLayer::~ImGuiLayer()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
}

void ImGuiLayer::OnAttach()
{
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(Application::GetInstance()->GetWindow()->GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void ImGuiLayer::OnDetach()
{

}

void ImGuiLayer::OnUpdate()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    Window* window = Application::GetInstance()->GetWindow();
    io.DisplaySize = ImVec2(window->GetWidth<float>(), window->GetHeight<float>());

    const float time = static_cast<float>(glfwGetTime());
    io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
    m_Time = time;

    static bool draw{true};
    ImGui::ShowDemoWindow(&draw);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnEvent(Event& event)
{
}

} // Sonata