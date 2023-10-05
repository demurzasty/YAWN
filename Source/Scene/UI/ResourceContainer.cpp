#include <YAWN/Scene/UI/ResourceContainer.hpp>
#include <YAWN/Scene/UI/TextureRect.hpp>
#include <YAWN/Scene/UI/BoxContainer.hpp>
#include <YAWN/Scene/UI/Label.hpp>
#include <YAWN/IO/Directory.hpp>
#include <YAWN/IO/File.hpp>
#include <YAWN/Runtime/Console.hpp>
#include <YAWN/Runtime/YTXT.hpp>
#include <YAWN/Runtime/Loaders/TextureLoader.hpp>

using namespace YAWN;

ResourceContainer::ResourceContainer() {
    SetCellSize(Vector2(96.0f, 96.0f + 24.0f));
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

    Ref<Texture> thumbnail = GetThumbnail(path);

    Ref<BoxContainer> container = new BoxContainer();
    container->SetVertical(true);
    container->SetMargin(0);

    if (!thumbnail) {
        Ref<Control> control = new Control();
        control->SetMinimumSize(96.0f);
        container->AddChild(control);
    } else {
        Ref<TextureRect> textureRect = new TextureRect();
        textureRect->SetTexture(CastTo<Texture>(thumbnail));
        textureRect->SetMinimumSize(96.0f);
        container->AddChild(textureRect);
    }

    Ref<Label> label = new Label();
    label->SetText(path.GetFilename());
    label->SetMinimumSize(Vector2(96.0f, 24.0f));
    container->AddChild(label);

    AddChild(container);
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
