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
        void InitializeImporter(const Type& type);

        void EnumerateFile(const FileInfo& info);

        void ImportFile(const FileInfo& info);

        Ref<Importer> FindImporterForExtension(const String& extension);

    private:
        void Hierarchy();

        void Hierarchy(const Ref<Node>& node);

    private:
        Array<Ref<Importer>> sImporters;
    };
}

