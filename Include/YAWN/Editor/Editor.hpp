#pragma once 

#include "Importer.hpp"
#include "../IO/FileInfo.hpp"
#include "../Core/Array.hpp"

namespace YAWN {
    class Editor {
    public:
        static void Initialize();

        static void Release();

        static void Reimport();

    private:
        static void InitializeImporter(const Type& type);

        static void EnumerateFile(const FileInfo& info);

        static void ImportFile(const FileInfo& info);

        static Ref<Importer> FindImporterForExtension(const String& extension);

    private:
        static Array<Ref<Importer>> sImporters;
    };
}
