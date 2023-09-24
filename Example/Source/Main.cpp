#include <YAWN/YAWN.hpp>

using namespace YAWN;

void Initialize() {
    Scene::GetRoot()->AddChild(new Editor());

    Ref<Node3D> node = new Node3D();
    node->SetName(L"Test");
    Scene::GetRoot()->AddChild(node);

    Ref<Geometry3D> geometry = new Geometry3D();
    geometry->SetName(L"Foo");
    geometry->AddChild(geometry);
}

int Main(int argc, char* argv[]) {
    Directory::SetCurrentDirectory(YAWN_CURRENT_DIRECTORY);

    Application::Setup();

    Application::AddInitializationStep(&Initialize);

    Application::Run();
    return 0;
}
