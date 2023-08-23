#include <YAWN/YAWN.hpp>

using namespace YAWN;

void Initialize() {
    Ref<Actor> actor = new Actor();
    actor->SetLocalPosition(Vector3(0.0f, 0.0f, 10.0f));

    Ref<Geometry> geometry = actor->AddComponent<Geometry>();
    
    Ref<Camera> camera = actor->AddComponent<Camera>();
    
    Scene::GetRoot()->AddChild(actor);
}

int Main(int argc, char* argv[]) {
    Directory::SetCurrentDirectory(YAWN_CURRENT_DIRECTORY);

    Application::Setup();

    Application::AddInitializationStep(&Initialize);

    Application::Run();
    return 0;
}
