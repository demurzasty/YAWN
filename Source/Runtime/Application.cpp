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

    Types::Register<Texture>();
    Types::Register<Font>();
    Types::Register<Mesh>();
    Types::Register<Prefab>();

    Types::Register<FontLoader>();
    Types::Register<MeshLoader>();
    Types::Register<PrefabLoader>();
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

    double lastTime = Window::GetTime();
    double accTime = 0.0;

    while (Window::IsOpen()) {
        Input::Refresh();

        Window::PollEvents();

        double currTime = Window::GetTime();
        double elapsedTime = currTime - lastTime;
        lastTime = currTime;

        Scene::Update(float(elapsedTime));

        accTime += elapsedTime;
        while (accTime >= 1.0 / 60.0) {
            Scene::FixedUpdate(1.0f / 60.0f);

            accTime -= 1.0 / 60.0;
        }

        Scene::LateUpdate(elapsedTime);

        Renderer::Render();

        Scene::Redraw();

        Window::SwapBuffers();
    }

    for (int i = sReleases.GetSize() - 1; i >= 0; --i) {
        sReleases[i]();
    }
}
