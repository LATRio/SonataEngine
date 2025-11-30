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
    SN_ENGINE_INFO("Freeing ImGui Layer");
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
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::OnUpdate()
{

    ImGuiIO& io = ImGui::GetIO();
    const Window* window = Application::GetInstance()->GetWindow();
    io.DisplaySize = ImVec2(window->GetWidth<float>(), window->GetHeight<float>());

    const float time = static_cast<float>(glfwGetTime());
    io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
    m_Time = time;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static bool show{true};
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnEvent(Event& event)
{
}

} // Sonata