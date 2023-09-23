#include <YAWN/YAWN.hpp>

using namespace YAWN;

void Initialize() {
    Ref<Node3D> node = new Node3D();
    node->SetLocalPosition(Vector3(0.0f, 0.0f, 10.0f));

    Ref<Node3D> node2 = new Node3D();
    node2->SetLocalPosition(Vector3(0.0f, 0.0f, 23.0f));
    node->AddChild(node2);

    Ref<Node2D> node2d = new Node2D();
    node->AddChild(node2d);

    Scene::GetRoot()->AddChild(node);
}

int Main(int argc, char* argv[]) {
    Directory::SetCurrentDirectory(YAWN_CURRENT_DIRECTORY);

    Application::Setup();

    Application::AddInitializationStep(&Initialize);

    Application::Run();
    return 0;
}
