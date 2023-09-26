#include <YAWN/YAWN.hpp>

using namespace YAWN;

void Initialize() {
    Ref<Font> font = ResourceManager::Load<Font>(Guid(L"f77df380-4ce3-ab24-9ba6-ef80efd64a73"));

    Scene::GetRoot()->AddChild(new Editor());

    Ref<BoxContainer> mainForm = new BoxContainer();
    mainForm->SetVertical(true);
    mainForm->SetLocalRectangle(Rectangle(0.0f, 0.0f, 1280.0f, 720.0f));
    mainForm->SetVerticalExpand(true);
    mainForm->SetHorizontalExpand(true);

    Ref<MenuBar> menuBar = new MenuBar();
    menuBar->SetHorizontalExpand(true);
    mainForm->AddChild(menuBar);

    {
        Ref<Button> button = new Button();
        button->SetText(L"File");
        menuBar->AddChild(button);

        Ref<Button> edit = new Button();
        edit->SetText(L"Edit");
        menuBar->AddChild(edit);

        Ref<Button> view = new Button();
        view->SetText(L"View");
        menuBar->AddChild(view);

        Ref<Button> project = new Button();
        project->SetText(L"Project");
        menuBar->AddChild(project);

        Ref<Button> help = new Button();
        help->SetText(L"Help");
        menuBar->AddChild(help);
    }

    Ref<BoxContainer> container = new BoxContainer();
    container->SetSplitter(true);
    container->SetVerticalExpand(true);
    container->SetHorizontalExpand(true);
    {
        Ref<BoxContainer> subContainer = new BoxContainer();
        subContainer->SetLocalSize(232.0f);
        subContainer->SetVerticalExpand(true);
        container->AddChild(subContainer);

        Ref<Section> section = new Section();
        section->SetHorizontalExpand(true);
        section->SetVerticalExpand(true);
        section->SetText(L"Hierarchy");
        subContainer->AddChild(section);

        subContainer = new BoxContainer();
        subContainer->SetLocalSize(800.0f);
        subContainer->SetVerticalExpand(true);
        subContainer->SetSplitter(true);
        subContainer->SetVertical(true);
        container->AddChild(subContainer);

        Ref<BoxContainer> subSubContainer = new BoxContainer();
        subSubContainer->SetLocalSize(500.0f);
        subSubContainer->SetHorizontalExpand(true);
        subContainer->AddChild(subSubContainer);

        section = new Section();
        section->SetHorizontalExpand(true);
        section->SetVerticalExpand(true);
        section->SetText(L"Scene");
        subSubContainer->AddChild(section);

        subSubContainer = new BoxContainer();
        subSubContainer->SetLocalSize(300.0f);
        subSubContainer->SetHorizontalExpand(true);
        subSubContainer->SetVerticalExpand(true);
        subContainer->AddChild(subSubContainer);

        section = new Section();
        section->SetHorizontalExpand(true);
        section->SetVerticalExpand(true);
        section->SetText(L"Resources");
        subSubContainer->AddChild(section);

        subContainer = new BoxContainer();
        subContainer->SetLocalSize(232.0f);
        subContainer->SetVerticalExpand(true);
        subContainer->SetHorizontalExpand(true);
        container->AddChild(subContainer);

        section = new Section();
        section->SetHorizontalExpand(true);
        section->SetVerticalExpand(true);
        section->SetText(L"Inspector");
        subContainer->AddChild(section);
    }
    mainForm->AddChild(container);

    Scene::GetRoot()->AddChild(mainForm);
}

int Main(int argc, char* argv[]) {
    Directory::SetCurrentDirectory(YAWN_CURRENT_DIRECTORY);

    Application::Setup();

    Application::AddInitializationStep(&Initialize);

    Application::Run();
    return 0;
}
