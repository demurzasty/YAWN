#include <YAWN/Editor/Editor.hpp>
#include <YAWN/Scene/Scene.hpp>

#include <imgui.h>

using namespace YAWN;

void Editor::Hierarchy() {
    if (ImGui::Begin("Hierarchy")) {
        Hierarchy(Scene::GetRoot());
    }
    ImGui::End();
}

void Editor::Hierarchy(const Ref<Node>& node) {
    ImGui::Text("asdsad");

    if (ImGui::TreeNodeEx("Test", ImGuiTreeNodeFlags_Framed)) {
        if (ImGui::TreeNodeEx("Test", ImGuiTreeNodeFlags_Framed)) {
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }

}