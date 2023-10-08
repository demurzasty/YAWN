#include <YAWN/Scene/UI/ResourceContainer.hpp>
#include <YAWN/Scene/UI/TextureRect.hpp>
#include <YAWN/Scene/UI/BoxContainer.hpp>
#include <YAWN/Scene/UI/Label.hpp>
#include <YAWN/IO/Directory.hpp>
#include <YAWN/IO/File.hpp>
#include <YAWN/Runtime/Console.hpp>
#include <YAWN/Runtime/YTXT.hpp>
#include <YAWN/Runtime/Loaders/TextureLoader.hpp>
#include <YAWN/Platform/Input.hpp>

using namespace YAWN;

enum class ResourceItemState {
    Default,
    Hover,
    Active,
};

class ResourceItem : public BoxContainer {
    YAWN_OBJECT(ResourceItem, BoxContainer);

public:
    ResourceItem() {
        SetVertical(true);
        SetMargin(0.0f);
        SetPadding(8.0f);
    }

    virtual ~ResourceItem() = default;
    
    virtual void Update(float timeStep) override {
        Base::Update(timeStep);

        if (IsVisible()) {
            const Vector2& mousePosition = Input::GetMousePosition();
            Rectangle globalRect = GetGlobalRectangle();

            if (Rectangle::Contains(globalRect, mousePosition)) {
                if (Input::IsMouseButtonPressed(MouseButton::Left)) {
                        mState = ResourceItemState::Active;
                }

                if (mState == ResourceItemState::Default) {
                    mState = ResourceItemState::Hover;
                }
            } else {
                if (mState == ResourceItemState::Hover) {
                    mState = ResourceItemState::Default;
                }
            }

            if (Input::IsMouseButtonReleased(MouseButton::Left)) {
                if (mState == ResourceItemState::Active) {

                    if (Rectangle::Contains(globalRect, mousePosition)) {
                        // GetClickedSignal().Emit(this);

                        mState = ResourceItemState::Hover;
                    } else {
                        mState = ResourceItemState::Default;
                    }
                }
            }
        }
    }
    virtual void Draw() override {
        Base::Draw();

        if (const Ref<Theme>& theme = GetTheme(); theme) {
            switch (mState) {
            case ResourceItemState::Default:
                DrawFillRect(GetGlobalRectangle(), theme->GetButtonDefaultColor());
                break;
            case ResourceItemState::Hover:
                DrawFillRect(GetGlobalRectangle(), theme->GetButtonHoverColor());
                break;
            case ResourceItemState::Active:
                DrawFillRect(GetGlobalRectangle(), theme->GetButtonActiveColor());
                break;
            }
        //    DrawFillRect(GetGlobalRectangle(), theme->GetButtonActiveColor());
         //   DrawRect(GetGlobalRectangle(), theme->GetFrameBorderColor());
        }
    }

private:
    ResourceItemState mState = ResourceItemState::Default;
};

ResourceContainer::ResourceContainer() {
    SetPadding(0.0f);
    SetMargin(0.0f);
    SetCellSize(Vector2(96.0f, 96.0f));
}

void ResourceContainer::Enter() {
    Base::Enter();

    if (mDirty) {
        Directory::EnumerateFiles(mPath, Delegate<void(const FileInfo&)>::Bind<&ResourceContainer::AddResourceItem>(this));
        mDirty = false;
    }
}

void ResourceContainer::Update(float timeStep) {
    Base::Update(timeStep);

    if (mDirty) {
        Directory::EnumerateFiles(mPath, Delegate<void(const FileInfo&)>::Bind<&ResourceContainer::AddResourceItem>(this));
        mDirty = false;
    }
}

void ResourceContainer::SetPath(const Path& path) {
    mPath = path;
    
    mDirty = true;
}

const Path& ResourceContainer::GetPath() const {
    return mPath;
}

void ResourceContainer::AddResourceItem(const FileInfo& info) {
    const Path& path = info.GetPath();
    String extension = path.GetExtension();

    if (extension == L".meta") {
        return;
    }

    Ref<ResourceItem> resourceItem = new ResourceItem();

    Ref<BoxContainer> textureContainer = new BoxContainer();
    textureContainer->SetMinimumSize(Vector2(80.0f, 64.0f));
    textureContainer->SetPadding(Vector4(8.0f, 0.0f, 8.0f, 0.0f));

    Ref<TextureRect> textureRect = new TextureRect();
    textureRect->SetTexture(GetThumbnail(path));
    textureRect->SetVerticalExpand(true);
    textureRect->SetMinimumSize(64.0f);
    textureContainer->AddChild(textureRect);

    resourceItem->AddChild(textureContainer);


    Ref<Label> label = new Label();
    label->SetText(path.GetFilename());
    label->SetMinimumSize(Vector2(80.0f, 24.0f));
    resourceItem->AddChild(label);

    AddChild(resourceItem);
}

Ref<Texture> ResourceContainer::GetThumbnail(const Path& path) const {
    String metaPath = path.ToString() + L".meta";
    if (!File::Exists(metaPath)) {
        return nullptr;
    }

    Map<String, Variant> meta = YTXT::Parse(File::ReadAllText(metaPath));
    if (!meta.Contains(L"Guid")) {
        return nullptr;
    }

    Path thumbnailPath = Path(L"Cache/Thumbnails") / meta[L"Guid"].AsString();
    if (!File::Exists(thumbnailPath)) {
        return nullptr;
    }

    return CastTo<Texture>(TextureLoader().Load(thumbnailPath));
}
