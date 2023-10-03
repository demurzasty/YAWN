#pragma once 

#include "Importer.hpp"
#include "../IO/FileInfo.hpp"
#include "../Core/Array.hpp"
#include "../Scene/Node.hpp"

namespace YAWN {
    class Editor : public Node {
        YAWN_OBJECT(Editor, Node);

    public:
        void Enter() override;

        void Exit() override;

        void Update(float timeStep) override;

        void Reimport();

    private:
        void InitializeImporter(const Ref<Type>& type);

        void EnumerateFile(const FileInfo& info);

        void CreateMetaFiles(const FileInfo& info);

        void ImportFile(const FileInfo& info);

        Ref<Importer> FindImporterForExtension(const String& extension);

    private:
        Array<Ref<Importer>> sImporters;
    };
}

