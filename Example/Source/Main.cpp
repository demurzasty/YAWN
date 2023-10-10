#include <YAWN/YAWN.hpp>

using namespace YAWN;

void BuildTree(const Ref<Tree>& tree, const Ref<Node>& node, Ref<TreeItem> item) {
    item->SetText(node->GetTypeName());

    for (const Ref<Node>& child : node->GetChildren()) {
        BuildTree(tree, child, tree->CreateItem(item));
    }
};

void Initialize() {
    Scene::GetRoot()->AddChild(new Editor());

#if 1
    Ref<Viewport> subViewport = new Viewport();

    Ref<Node3D> node3d = new Node3D();
    node3d->SetName(L"TestNode");
    node3d->SetLocalPosition(Vector3(0.4124f, 1.3452f, 312.455f));

    Ref<Prefab> prefab = ResourceManager::Load<Prefab>(Guid(L"97b9dcf3-1894-cc03-e0d7-f4c4d2c9e800"));

    {
        subViewport->AddChild(prefab->Instantiate());

        subViewport->AddChild(node3d);

        Ref<Camera3D> camera = new FreeLookCamera3D();

        camera->SetLocalPosition(Vector3(0.0f, 0.25f, 1.0f));

        subViewport->AddChild(camera);
    }

    Ref<WindowContainer> windowContainer = new WindowContainer();
    windowContainer->SetName(L"WindowContainer");
 
    Ref<BoxContainer> mainContainer = new BoxContainer();
    mainContainer->SetName(L"BoxContainer");
    mainContainer->SetVertical(true);
    mainContainer->SetVerticalExpand(true);
    mainContainer->SetHorizontalExpand(true);
    mainContainer->SetMargin(0.0f);

    {
        Ref<MenuBar> menuBar = new MenuBar();
        menuBar->SetName(L"MenuBar");

        {
            Ref<MenuButton> menu = new MenuButton();
            menu->SetName(L"MenuButton");
            menu->SetText(L"Project");

            Ref<Button> vsyncButton = new Button();
            vsyncButton->SetText(L"VSync");
            vsyncButton->SetMinimumSize(24.0f);
            menu->GetPopup()->AddChild(vsyncButton);

            menuBar->AddChild(menu);
        }

        {
            Ref<MenuButton> button = new MenuButton();
            button->SetName(L"MenuButton");
            button->SetText(L"Debug");
            menuBar->AddChild(button);
        }

        {
            Ref<MenuButton> button = new MenuButton();
            button->SetName(L"MenuButton");
            button->SetText(L"Tools");
            menuBar->AddChild(button);
        }

        {
            Ref<MenuButton> button = new MenuButton();
            button->SetName(L"MenuButton");
            button->SetText(L"Help");
            menuBar->AddChild(button);
        }

        mainContainer->AddChild(menuBar);
    }

    Ref<Tree> tree = new Tree();
    tree->SetName(L"Tree");

    {
        Ref<BoxContainer> boxContainer = new BoxContainer();
        boxContainer->SetName(L"BoxContainer");
        boxContainer->SetSplitter(true);
        boxContainer->SetVerticalExpand(true);
        boxContainer->SetHorizontalExpand(true);

        {
            Ref<Section> section = new Section();
            section->SetName(L"Section");
            section->SetMinimumSize(Vector2(250.0f, 200.0f));
            section->SetText(L"Scene");
            boxContainer->AddChild(section); 

            tree->SetLocalPosition(Vector2(0.0f, 32.0f));
            tree->SetMinimumSize(Vector2(20.0f, 20.0f));
            tree->SetVerticalExpand(true);
            section->AddChild(tree);
        }

        {
            Ref<BoxContainer> centerContainer = new BoxContainer();
            centerContainer->SetName(L"BoxContainer");
            centerContainer->SetVertical(true);
            centerContainer->SetSplitter(true);
            centerContainer->SetHorizontalExpand(true);

            {
                Ref<Section> section = new Section();
                section->SetName(L"Section");
                section->SetMinimumSize(Vector2(100.0f, 100.0f));
                section->SetVerticalExpand(true);
                section->SetText(L"Viewport");

                Ref<ViewportContainer> viewportContainer = new ViewportContainer();
                viewportContainer->AddChild(subViewport);
                section->AddChild(viewportContainer);

                centerContainer->AddChild(section);
            }

            {
                Ref<Section> section = new Section();
                section->SetName(L"Section");
                section->SetMinimumSize(Vector2(100.0f, 250.0f));
                section->SetText(L"Resources");

                Ref<ResourceContainer> resourceContainer = new ResourceContainer();
                resourceContainer->SetPath(L"Data/FlightHelmet");
                section->AddChild(resourceContainer);

                centerContainer->AddChild(section);
            }

            boxContainer->AddChild(centerContainer);
        }

        {
            Ref<Section> section = new Section();
            section->SetName(L"Section");
            section->SetMinimumSize(Vector2(250.0f, 100.0f));
            section->SetVerticalExpand(true);
            section->SetText(L"Inspector");

            Ref<Inspector> inspector = new Inspector();
            inspector->SetEditedObject(node3d);
            section->AddChild(inspector);

            boxContainer->AddChild(section);
        }

        mainContainer->AddChild(boxContainer);
    }

    windowContainer->AddChild(mainContainer);

    Scene::GetRoot()->AddChild(windowContainer);

    Ref<TreeItem> item = tree->CreateItem();
    item->SetText(L"Root");
    BuildTree(tree, subViewport, item);
#endif
}

int Main(int argc, char* argv[]) {
    Directory::SetCurrentDirectory(YAWN_CURRENT_DIRECTORY);

    Application::Setup();

    Application::AddInitializationStep(&Initialize);

    Application::Run();
    return 0;
}
