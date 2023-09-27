#include <YAWN/YAWN.hpp>

using namespace YAWN;

void Initialize() {
    Scene::GetRoot()->AddChild(new Editor());

    Ref<WindowContainer> windowContainer = new WindowContainer();

    Ref<BoxContainer> boxContainer = new BoxContainer();
    boxContainer->SetSplitter(true);

    {
        Ref<Section> section = new Section();
        section->SetMinimumSize(Vector2(250.0f, 200.0f));
        section->SetText(L"Scene #1");
        boxContainer->AddChild(section);
    }

    {
        Ref<BoxContainer> centerContainer = new BoxContainer();
        centerContainer->SetVertical(true);
        centerContainer->SetSplitter(true);
        centerContainer->SetHorizontalExpand(true);

        {
            Ref<Section> section = new Section();
            section->SetMinimumSize(Vector2(100.0f, 100.0f));
            section->SetVerticalExpand(true);
            section->SetText(L"Viewport");
            centerContainer->AddChild(section);
        }

        {
            Ref<Section> section = new Section();
            section->SetMinimumSize(Vector2(100.0f, 250.0f));
            section->SetText(L"Resources");
            centerContainer->AddChild(section);
        }

        boxContainer->AddChild(centerContainer);
    }

    {
        Ref<Section> section = new Section();
        section->SetMinimumSize(Vector2(250.0f, 100.0f));
        section->SetVerticalExpand(true);
        section->SetText(L"Inspector");
        boxContainer->AddChild(section);
    }

    windowContainer->AddChild(boxContainer);

    Scene::GetRoot()->AddChild(windowContainer);



    //Ref<WindowContainer> windowContainer = new WindowContainer();

    //Ref<BoxContainer> mainForm = new BoxContainer();
    //mainForm->SetVertical(true);
    //mainForm->SetLocalRectangle(Rectangle(0.0f, 0.0f, 1280.0f, 720.0f)); 
    //mainForm->SetHorizontalExpand(true);
    //mainForm->SetVerticalExpand(true);

    //Ref<MenuBar> menuBar = new MenuBar();
    //{
    //    Ref<Button> button = new Button();
    //    button->SetText(L"File");
    //    menuBar->AddChild(button);

    //    Ref<Button> edit = new Button();
    //    edit->SetText(L"Edit");
    //    menuBar->AddChild(edit);

    //    Ref<Button> view = new Button();
    //    view->SetText(L"View");
    //    menuBar->AddChild(view);

    //    Ref<Button> project = new Button();
    //    project->SetText(L"Project");
    //    menuBar->AddChild(project);

    //    Ref<Button> help = new Button();
    //    help->SetText(L"Help");
    //    menuBar->AddChild(help);
    //}
    //mainForm->AddChild(menuBar);

    //Ref<BoxContainer> container = new BoxContainer();
    //container->SetSplitter(true);
    //container->SetVerticalExpand(true);
    //container->SetHorizontalExpand(true);
    //{
    //    Ref<BoxContainer> subContainer = new BoxContainer();
    //    subContainer->SetLocalSize(232.0f);
    //    subContainer->SetVerticalExpand(true);
    //    container->AddChild(subContainer);

    //    Ref<Section> section = new Section();
    //    section->SetHorizontalExpand(true);
    //    section->SetVerticalExpand(true);
    //    section->SetText(L"Hierarchy");
    //    subContainer->AddChild(section);

    //    subContainer = new BoxContainer();
    //    subContainer->SetLocalSize(800.0f);
    //    subContainer->SetVerticalExpand(true);
    //    subContainer->SetHorizontalExpand(true);
    //    subContainer->SetSplitter(true);
    //    subContainer->SetVertical(true);
    //    container->AddChild(subContainer);

    //    Ref<BoxContainer> subSubContainer = new BoxContainer();
    //    subSubContainer->SetLocalSize(500.0f);
    //    subSubContainer->SetHorizontalExpand(true);
    //    subContainer->AddChild(subSubContainer);

    //    section = new Section();
    //    section->SetHorizontalExpand(true);
    //    section->SetVerticalExpand(true);
    //    section->SetText(L"Scene");
    //    subSubContainer->AddChild(section);

    //    subSubContainer = new BoxContainer();
    //    subSubContainer->SetLocalSize(300.0f);
    //    subSubContainer->SetHorizontalExpand(true);
    //    subContainer->AddChild(subSubContainer);

    //    section = new Section();
    //    section->SetHorizontalExpand(true);
    //    section->SetVerticalExpand(true);
    //    section->SetText(L"Resources");
    //    subSubContainer->AddChild(section);

    //    subContainer = new BoxContainer();
    //    subContainer->SetLocalSize(232.0f);
    //    subContainer->SetVerticalExpand(true);
    //    container->AddChild(subContainer);

    //    section = new Section();
    //    section->SetHorizontalExpand(true);
    //    section->SetVerticalExpand(true);
    //    section->SetText(L"Inspector");
    //    subContainer->AddChild(section);
    //}
    //mainForm->AddChild(container);

    //windowContainer->AddChild(mainForm);

    //Scene::GetRoot()->AddChild(windowContainer);
}

int Main(int argc, char* argv[]) {
    Directory::SetCurrentDirectory(YAWN_CURRENT_DIRECTORY);

    Application::Setup();

    Application::AddInitializationStep(&Initialize);

    Application::Run();
    return 0;
}
