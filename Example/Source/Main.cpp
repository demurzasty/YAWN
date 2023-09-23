#include <YAWN/YAWN.hpp>

using namespace YAWN;

void Initialize() {
    Scene::GetRoot()->AddChild(new ImGui2D());
}

int Main(int argc, char* argv[]) {
    Directory::SetCurrentDirectory(YAWN_CURRENT_DIRECTORY);

    Application::Setup();

    Application::AddInitializationStep(&Initialize);

    Application::Run();
    return 0;
}
