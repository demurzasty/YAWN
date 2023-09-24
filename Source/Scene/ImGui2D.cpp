#include <YAWN/Scene/ImGui2D.hpp>
#include <YAWN/Graphics/Renderer.hpp>
#include <YAWN/Platform/Window.hpp>
#include <YAWN/Platform/Input.hpp>

#include <imgui.h>

using namespace YAWN;

void ImGui2D::Enter() {
    Base::Enter();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;

    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    mFontTextureId = Renderer::CreateTexture(width, height, TextureFormat::RGBA8, TextureFilter::Linear, TextureWrapping::Repeat, 1);
    Renderer::SetTextureData(mFontTextureId, 0, pixels);

    io.Fonts->SetTexID(mFontTextureId);
}

void ImGui2D::Exit() {
    Base::Exit();

    Renderer::DestroyTexture(mFontTextureId);

    ImGui::DestroyContext();
}

void ImGui2D::Update(float timeStep) {
    Base::Update(timeStep);

    Vector2 windowSize = Window::GetSize();

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(windowSize.X, windowSize.Y);
    io.DisplayFramebufferScale = io.DisplaySize;
    io.DeltaTime = timeStep;

    const Vector2& mousePosition = Input::GetMousePosition();
    io.AddMousePosEvent(mousePosition.X, mousePosition.Y);

    io.AddMouseButtonEvent(ImGuiMouseButton_Left, Input::IsMouseButtonDown(MouseButton::Left));
    io.AddMouseButtonEvent(ImGuiMouseButton_Middle, Input::IsMouseButtonDown(MouseButton::Middle));
    io.AddMouseButtonEvent(ImGuiMouseButton_Right, Input::IsMouseButtonDown(MouseButton::Right));

    ImGui::NewFrame();

    if (mShowDemoWindow) {
        ImGui::ShowDemoWindow(&mShowDemoWindow);
    }
}

void ImGui2D::Draw() {
    Base::Draw();

    ImGui::Render();

    ImDrawData* drawData = ImGui::GetDrawData();
    for (int n = 0; n < drawData->CmdListsCount; ++n) {
        const ImDrawList* cmdList = drawData->CmdLists[n];

        ArrayView<const Vertex2D> vertices((const Vertex2D*)cmdList->VtxBuffer.Data, cmdList->VtxBuffer.Size);
        ArrayView<const unsigned short> indices(cmdList->IdxBuffer.Data, cmdList->IdxBuffer.Size);

        Renderer::LLSetVertexBufferData2D(vertices);
        Renderer::LLSetIndexBufferData2D(indices);

        for (int i = 0; i < cmdList->CmdBuffer.Size; ++i) {
            const ImDrawCmd& cmd = cmdList->CmdBuffer[i];

            if (cmd.UserCallback) {
                if (cmd.UserCallback != ImDrawCallback_ResetRenderState) {
                    cmd.UserCallback(cmdList, &cmd);
                }
            } else {
                Renderer::LLSetClipRect(Rectangle(cmd.ClipRect.x, cmd.ClipRect.y, cmd.ClipRect.z - cmd.ClipRect.x, cmd.ClipRect.w - cmd.ClipRect.y));

                Renderer::LLSetTexture2D(cmd.GetTexID());

                Renderer::LLDraw2D(cmd.VtxOffset, cmd.IdxOffset, cmd.ElemCount);
            }
        }
    }
}
