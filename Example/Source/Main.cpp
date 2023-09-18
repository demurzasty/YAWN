#include <YAWN/YAWN.hpp>

using namespace YAWN;

void Initialize() {
    Ref<Node3D> actor = new Node3D();
    actor->SetLocalPosition(Vector3(0.0f, 0.0f, 10.0f));
    
    String json = JSON::Stringify(actor);
    Console::WriteLine(json);

    Scene::GetRoot()->AddChild(actor);
}

int Main(int argc, char* argv[]) {
    Directory::SetCurrentDirectory(YAWN_CURRENT_DIRECTORY);

    Application::Setup();

    Application::AddInitializationStep(&Initialize);

    Application::Run();
    return 0;
}
