#include <YAWN/YAWN.hpp>

#include <duktape.h>

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

    Settings::SetWindowTitle(L"YAWN");
    Settings::SetWindowWidth(1280);
    Settings::SetWindowHeight(720);

    Types::Register<FontLoader>();
    Types::Register<TextureLoader>();

    Types::Register<Node>();
    Types::Register<Node3D>();
    Types::Register<Camera3D>();
    Types::Register<Geometry3D>();
    //Types::Register<BoxContainer>();
    //Types::Register<Button>();
    //Types::Register<Control>();
    //Types::Register<MenuBar>();

#if !YAWN_PROD_BUILD
    /// Types::Register<Editor>();
    Types::Register<FontImporter>();
    Types::Register<ModelImporter>();
    Types::Register<PrefabImporter>();
    Types::Register<TextureImporter>();
#endif
}

void Application::Run() {
    for (int i = 0; i < sInitializations.GetSize(); ++i) {
        sInitializations[i]();
    }

    while (Window::IsOpen()) {
        Input::Refresh();

        Window::PollEvents();

        Scene::Update(1.0f / 60.0f);

        Scene::FixedUpdate(1.0f / 60.0f);

        Scene::LateUpdate(1.0f / 60.0f);

        Renderer::Render();

        Scene::Redraw();

        Window::SwapBuffers();
    }

    for (int i = sReleases.GetSize() - 1; i >= 0; --i) {
        sReleases[i]();
    }
}
