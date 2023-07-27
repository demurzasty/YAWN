#include <YAWN/Graphics/Image.hpp>
#include <YAWN/Core/Memory.hpp>

#include <stb_image.h>
#include <stb_image_resize.h>

using namespace YAWN;

ImageInfo Image::FetchInfo(const Path& path) {
    int width, height, channels;
    if (stbi_info(path.ToString().ToUTF8().GetData(), &width, &height, &channels)) {
        return ImageInfo(width, height, channels);
    }

    return ImageInfo();
}

Ref<Image> Image::FromFile(const Path& path, int desiredChannels) {
    int width, height, channels;
    unsigned char* data = stbi_load(path.ToString().ToUTF8().GetData(), &width, &height, &channels, desiredChannels);

    if (data) {
        return new Image(data, ImageInfo(width, height, desiredChannels > 0 ? desiredChannels : channels));
    }

    return nullptr;
}

Ref<Image> Image::Resize(Ref<Image> image, int width, int height) {
    ImageInfo imageInfo(width, height, image->mInfo.GetChannels());

    unsigned char* data = (unsigned char*)Memory::Allocate(imageInfo.GetDataSize());
    if (stbir_resize_uint8(image->mData, image->mInfo.GetWidth(), image->mInfo.GetHeight(), image->mInfo.GetStride(),
        data, width, height, imageInfo.GetStride(), imageInfo.GetChannels())) {
        return new Image(data, imageInfo);
    }

    return nullptr;
}

Image::Image(unsigned char* data, const ImageInfo& info)
    : mData(data), mInfo(info) {
}

Image::~Image() {
    Memory::Deallocate(mData);
}

ArrayView<const unsigned char> Image::GetData() const {
    return ArrayView<const unsigned char>(mData, mInfo.GetDataSize());
}

const ImageInfo& Image::GetInfo() const {
    return mInfo;
}
