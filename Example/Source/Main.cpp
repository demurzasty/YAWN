﻿#include <YAWN/YAWN.hpp>

using namespace YAWN;

void Initialize() {
    Ref<Control> control = new Control();

    control->SetLocalRectangle(Rectangle(100.0f, 100.0f, 200.0f, 200.0f));
    control->SetBackgroundColor(Color::Black);

    Scene::GetRoot()->AddChild(control);
}

int Main(int argc, char* argv[]) {
    Directory::SetCurrentDirectory(YAWN_CURRENT_DIRECTORY);

    Application::Setup();

    Application::AddInitializationStep(&Initialize);

    Application::Run();
    return 0;
}
