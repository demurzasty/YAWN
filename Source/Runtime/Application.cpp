#include <YAWN/YAWN.hpp>

using namespace YAWN;

Array<void(*)()> Application::sInitializations;
Array<void(*)()> Application::sReleases;

void Application::Setup() {
    AddService<Window>();
    AddService<Input>();
    AddService<Renderer>();
    AddService<ThreadPool>();
    AddService<ResourceManager>();
    AddService<Scene>();

#if !YAWN_PROD_BUILD
    AddService<Editor>();
#endif

    Settings::SetWindowTitle(L"YAWN");
    Settings::SetWindowWidth(1280);
    Settings::SetWindowHeight(720);

    Types::Register<TextureLoader>();

    Types::Register<Node>();
    Types::Register<Node3D>();
    Types::Register<Camera3D>();
    Types::Register<Geometry3D>();

#if !YAWN_PROD_BUILD
    Types::Register<TextureImporter>();
    Types::Register<ModelImporter>();
#endif
}

void Application::Run() {
    for (int i = 0; i < sInitializations.GetSize(); ++i) {
        sInitializations[i]();
    }

#if !YAWN_PROD_BUILD
    Editor::Reimport();
#endif

    while (Window::IsOpen()) {
        Window::PollEvents();

        Input::Refresh();

        Scene::Update(1.0f / 60.0f);

        Scene::FixedUpdate(1.0f / 60.0f);

        Scene::LateUpdate(1.0f / 60.0f);

        Renderer::Present();

        Window::SwapBuffers();
    }

    for (int i = sReleases.GetSize() - 1; i >= 0; --i) {
        sReleases[i]();
    }
}
