#pragma once 

#include "Importer.hpp"
#include "../IO/FileInfo.hpp"
#include "../Core/Array.hpp"
#include "../Scene/ImGui2D.hpp"

namespace YAWN {
    class Editor : public ImGui2D {
        YAWN_OBJECT(Editor, ImGui2D);

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

