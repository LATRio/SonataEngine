#include "sandbox_2d.hpp"
#include "profiler/instrumentor.hpp"

static constexpr uint32_t s_MapWidth = 24;
static auto s_MapTiles =
    "WWWWWWWWWWWWWWWWWWWWWWWW"
    "WWWWWWWDDDDDDWWWWWWWWWWW"
    "WWWWWDDDDDDDDDDDWWWWWWWW"
    "WWWWDDDDDDDDDDDDDDDWWWWW"
    "WWWDDDDDDDDDDDDDDDDDDWWW"
    "WWDDDDWWWDDDDDDDDDDDDWWW"
    "WDDDDDWWWDDDDDDDDDDDDDWW"
    "WWDDDDDDDDDDDDDDDDDDDWWW"
    "WWWWDDDDDDDDDDDDDDDDWWWW"
    "WWWWWDDDDDDDDDDDDDDWWWWW"
    "WWWWWWDDDDDDDDDDDWWWWWWW"
    "WWWWWWWDDDDDDDDDWWWWWWWW"
    "WWWWWWWWWWDDDDWWWWWWWWWW"
    "WWWWWWWWWWWWWWWWWWWWWWWW"
;

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D")
    , m_CameraController(16.0f / 9.0f)
{}

void Sandbox2D::OnAttach()
{
    SN_PROFILE_FUNCTION;

    Sonata::Renderer2D::Init();
    m_Texture = Sonata::Texture2D::Create("assets/container.jpg");
    m_Spritesheet = Sonata::Texture2D::Create("assets/RPGpack_sheet_2X.png");

    m_MapWidth = s_MapWidth;
    m_MapHeight = strlen(s_MapTiles) / m_MapWidth;

    m_TextureStairs = Sonata::SubTexture2D::CreateFromCoords(m_Spritesheet, {7, 6}, {128, 128});
    m_TextureBarrel = Sonata::SubTexture2D::CreateFromCoords(m_Spritesheet, {8, 2}, {128, 128});
    m_TextureTree = Sonata::SubTexture2D::CreateFromCoords(m_Spritesheet, {2, 1}, {128, 128}, {1.0f, 2.0f});

    m_TextureMap['W'] = Sonata::SubTexture2D::CreateFromCoords(m_Spritesheet, {11, 11}, {128, 128});
    m_TextureMap['D'] = Sonata::SubTexture2D::CreateFromCoords(m_Spritesheet, {6, 11}, {128, 128});

    m_CameraController.SetZoomLevel(5.0f);
}

void Sandbox2D::OnDetach()
{
    SN_PROFILE_FUNCTION;

    Sonata::Renderer2D::Shutdown();
}

void Sandbox2D::OnUpdate(const float p_DeltaTime)
{
    SN_PROFILE_FUNCTION;

    m_CameraController.OnUpdate(p_DeltaTime);

    Sonata::Renderer2D::ResetStats();

    SN_PROFILE_GPU_ZONE("RenderFrame");

    Sonata::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Sonata::RenderCommand::Clear();

    static float rotation{0.0f};
    rotation += 50.0f * p_DeltaTime;

    Sonata::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Sonata::Renderer2D::DrawRotatedQuad({1.0f, 0.0f}, {0.8f, 0.8f}, 45.0f, m_SquareColor);
    Sonata::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, m_SquareColor);
    Sonata::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});
    Sonata::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {20.0f, 20.0f}, m_Texture, 20.0f);
    Sonata::Renderer2D::DrawRotatedQuad({-2.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, rotation, m_Texture, 20.0f);
    Sonata::Renderer2D::EndScene();

    Sonata::Renderer2D::BeginScene(m_CameraController.GetCamera());
    for (float y = -5.0f; y < 5.0f; y += 0.5f)
    {
        for (float x = -5.0f; x < 5.0f; x += 0.5f)
        {
            glm::vec4 color{(x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f};
            Sonata::Renderer2D::DrawQuad({x, y}, {0.45f, 0.45f}, color);
        }
    }
    Sonata::Renderer2D::EndScene();

    Sonata::Renderer2D::BeginScene(m_CameraController.GetCamera());

    // Sonata::Renderer2D::DrawQuad({0.0f, 0.0f, 0.5f}, {1.0f, 1.0f}, m_TextureStairs);
    // Sonata::Renderer2D::DrawQuad({1.0f, 0.0f, 0.5f}, {1.0f, 1.0f}, m_TextureBarrel);
    // Sonata::Renderer2D::DrawQuad({-1.0f, 0.5f, 0.5f}, {1.0f, 2.0f}, m_TextureTree);

    for (uint32_t y = 0; y < m_MapHeight; y++)
    {
        for (uint32_t x = 0; x < m_MapWidth; x++)
        {
            char tileType = s_MapTiles[x + y * m_MapWidth];
            Sonata::Ref<Sonata::SubTexture2D> texture;
            if (m_TextureMap.contains(tileType))
            {
                texture = m_TextureMap[tileType];
            }
            else
            {
                texture = m_TextureBarrel;
            }
            Sonata::Renderer2D::DrawQuad({static_cast<float>(x) - m_MapWidth / 2.0f, static_cast<float>(y) - m_MapHeight / 2.0f, 1.0f}, {1.0f, 1.0f}, texture);
        }
    }
    Sonata::Renderer2D::EndScene();

    SN_PROFILE_GPU_COLLECT;
}

void Sandbox2D::OnEvent(Sonata::Event& p_Event)
{
    SN_PROFILE_FUNCTION;

    m_CameraController.OnEvent(p_Event);
}

void Sandbox2D::OnImGuiRender()
{
    SN_PROFILE_FUNCTION;

    using namespace ImGui;

    const auto stats = Sonata::Renderer2D::GetStats();

    bool p_open = true;

    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &p_open, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    // REMINDER: THIS IS A DEMO FOR ADVANCED USAGE OF DockSpace()!
    // MOST REGULAR APPLICATIONS WILL SIMPLY WANT TO CALL DockSpaceOverViewport(). READ COMMENTS ABOVE.
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    // Show demo options and help
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Close")) { Sonata::Application::GetInstance()->Close(); }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    {
        Begin("Settings", nullptr, ImGuiChildFlags_AlwaysAutoResize);

        Text("Renderer2D Stats:");
        Text("Draw Calls: %d", stats.DrawCalls);
        Text("Quads: %d", stats.QuadCount);
        Text("Vertices: %d", stats.GetTotalVertexCount());
        Text("Indices: %d", stats.GetTotalIndexCount());

        ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

        Image(m_Texture->GetTextureID(), ImVec2{256.0f, 256.0f});

        End();
    }

    End();
}
