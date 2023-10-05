#include <YAWN/Editor/Editor.hpp>
#include <YAWN/IO/Directory.hpp>
#include <YAWN/Threading/ThreadPool.hpp>
#include <YAWN/Reflection/Types.hpp>
#include <YAWN/Core/Guid.hpp>
#include <YAWN/Runtime/YTXT.hpp>
#include <YAWN/IO/File.hpp>
#include <YAWN/Core/StringBuilder.hpp>
#include <YAWN/Runtime/Console.hpp>

#include <stdio.h>

// TODO: Use JSON instead of YTXT.

using namespace YAWN;

void Editor::Enter() {
    Base::Enter();

    SetName(L"$Editor");

    Types::EnumerateTypesOfBase<Importer>(Delegate<void(const Ref<Type>&)>::Bind<&Editor::InitializeImporter>(this));
    
    Reimport();
}

void Editor::Exit() {
    Base::Exit();

    sImporters.Clear();
}

void Editor::Update(float timeStep) {
    Base::Update(timeStep);
}

void Editor::Reimport() {
    Directory::Create(L"Data");
    Directory::Create(L"Package");
    Directory::Create(L"Cache");
    Directory::Create(L"Cache/Thumbnails");

    Directory::EnumerateFiles(L"Data", Delegate<void(const FileInfo&)>::Bind<&Editor::CreateMetaFiles>(this));
    Directory::EnumerateFiles(L"Data", Delegate<void(const FileInfo&)>::Bind<&Editor::EnumerateFile>(this));
}

void Editor::InitializeImporter(const Ref<Type>& type) {
    Ref<Reference> importer = type->Construct();

    YAWN_ASSERT(importer);
    YAWN_ASSERT(importer->IsInstanceOf<Importer>());

    sImporters.Add(CastTo<Importer>(importer));
}

void Editor::EnumerateFile(const FileInfo& info) {
    // TODO: Run task on thread pool.
    ImportFile(info);
}

void Editor::CreateMetaFiles(const FileInfo& info) {
    String extension = info.GetPath().GetExtension();
    if (extension == L".meta") {
        return;
    }

    if (!FindImporterForExtension(extension)) {
        return;
    }

    Path metadataPath = info.GetPath().ToString() + L".meta";
    if (!File::Exists(metadataPath)) {
        Map<String, Variant> metadata;
        metadata.Add(L"Guid", Guid::Generate().ToString());
        File::WriteAllText(metadataPath, YTXT::Stringify(metadata));
    }
}

void Editor::ImportFile(const FileInfo& info) {
    String extension = info.GetPath().GetExtension();
    if (extension == L".meta") {
        return;
    }
    
    Ref<Importer> importer = FindImporterForExtension(extension);
    if (!importer) {
        Console::WriteLine(L"Missing importer for extension: '%s'.", extension.GetData());
        return;
    }

    Path metadataPath = info.GetPath().ToString() + L".meta";

    Map<String, Variant> metadata;
    if (File::Exists(metadataPath)) {
        metadata = YTXT::Parse(File::ReadAllText(metadataPath));
    }

    if (!metadata.Contains(L"Guid")) {
        metadata.Add(L"Guid", Guid::Generate().ToString());
    }

    String guid = metadata[L"Guid"];

    bool alwaysImport = false;
    if (metadata.Contains(L"AlwaysImport")) {
        alwaysImport = metadata[L"AlwaysImport"];
    }

    Path cachePath = String(L"Cache/") + guid;

    Map<String, Variant> cache;
    if (File::Exists(cachePath)) {
        cache = YTXT::Parse(File::ReadAllText(cachePath));
    }

    long long lastWriteTime = 0;

    if (cache.Contains(L"LastWriteTime")) {
        lastWriteTime = cache[L"LastWriteTime"];
    }

    File::WriteAllText(metadataPath, YTXT::Stringify(metadata));

    if (alwaysImport || info.GetLastWriteTime() > lastWriteTime) {
        Console::WriteLine(L"Importing: %s", info.GetPath().ToString().GetData());

        importer->Import(info.GetPath(), Path(L"Package") / guid, metadata);

        cache.GetOrAdd(L"LastWriteTime") = info.GetLastWriteTime();

        File::WriteAllText(cachePath, YTXT::Stringify(cache));
    }
}

Ref<Importer> Editor::FindImporterForExtension(const String& extension) {
    for (int i = 0; i < sImporters.GetSize(); ++i) {
        if (sImporters[i]->GetSupportedExtensions().Find(extension) > -1) {
            return sImporters[i];
        }
    }

    return nullptr;
}
