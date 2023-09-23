#include <YAWN/Scene/ImGui2D.hpp>
#include <YAWN/Graphics/Renderer.hpp>

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
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);   // Load as RGBA 32-bit (75% of the memory is wasted, but default font is so small) because it is more likely to be compatible with user's existing shaders. If your ImTextureId represent a higher-level concept than just a GL texture id, consider calling GetTexDataAsAlpha8() instead to save on GPU memory.
}

void ImGui2D::Exit() {
    Base::Exit();

    ImGui::DestroyContext();
}

void ImGui2D::Update(float timeStep) {
    Base::Update(timeStep);

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(1280.0f, 720.0f);
    io.DisplayFramebufferScale = io.DisplaySize;
    io.DeltaTime = 1.0f / 60.0f;

    static bool show_demo_window = true;
    static bool show_another_window = false;
    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui::NewFrame();

    if (show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }

}

void ImGui2D::Draw() {
    Base::Draw();

    ImGui::Render();

    ImDrawData* drawData = ImGui::GetDrawData();
    for (int n = 0; n < drawData->CmdListsCount; ++n) {
        const ImDrawList* cmdList = drawData->CmdLists[n];

        ArrayView<const Vertex2D> vertices((const Vertex2D*)cmdList->VtxBuffer.Data, cmdList->VtxBuffer.Size);
        ArrayView<const int> indices(cmdList->IdxBuffer.Data, cmdList->IdxBuffer.Size);

        Renderer::LLSetVertexBufferData2D(vertices);
        Renderer::LLSetIndexBufferData2D(indices);

        for (int i = 0; i < cmdList->CmdBuffer.Size; ++i) {
            const ImDrawCmd& cmd = cmdList->CmdBuffer[i];

            if (cmd.UserCallback) {
                if (cmd.UserCallback != ImDrawCallback_ResetRenderState) {
                    cmd.UserCallback(cmdList, &cmd);
                }
            } else {
                // TODO: Scissor testing.

                Renderer::LLDraw2D(cmd.VtxOffset, cmd.IdxOffset, cmd.ElemCount);
            }
        }
    }
}
