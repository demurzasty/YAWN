#pragma once 

#include "../Core/ArrayView.hpp"
#include "../Runtime/Reference.hpp"
#include "../IO/Path.hpp"

#include "ImageInfo.hpp"

namespace YAWN {
    class Image : public Reference {
        YAWN_OBJECT(Image, Reference);

    public:
        static ImageInfo FetchInfo(const Path& path);

        static Ref<Image> FromFile(const Path& path, int desiredChannels = 0);

        static Ref<Image> FromMemory(const ArrayView<const unsigned char>& data, int desiredChannels = 0);

        static Ref<Image> Resize(Ref<Image> image, int width, int height);

        ~Image();

        ArrayView<unsigned char> GetData() const;

        const ImageInfo& GetInfo() const;

    private:
        Image(unsigned char* data, const ImageInfo& info);

    private:
        unsigned char* mData = nullptr;
        ImageInfo mInfo;
    };
}
