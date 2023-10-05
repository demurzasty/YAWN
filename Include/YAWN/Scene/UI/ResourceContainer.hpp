#pragma once 

#include "GridContainer.hpp"
#include "../../IO/Path.hpp"
#include "../../IO/FileInfo.hpp"

namespace YAWN {
    class ResourceContainer : public GridContainer {
        YAWN_OBJECT(ResourceContainer, GridContainer);

    public:
        ResourceContainer();

        virtual ~ResourceContainer() = default;

        virtual void Enter() override;

        virtual void Update(float timeStep) override;

        void SetPath(const Path& path);

        const Path& GetPath() const;

    private:
        void AddResourceItem(const FileInfo& path);

        Ref<Texture> GetThumbnail(const Path& path) const;

    private:
        Path mPath;
        bool mDirty = true;
    };
}