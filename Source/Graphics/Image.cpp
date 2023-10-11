#include <YAWN/Graphics/Image.hpp>
#include <YAWN/Core/Memory.hpp>
#include <YAWN/Math/Math.hpp>

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

Ref<Image> Image::FromMemory(const ArrayView<const unsigned char>& data, int desiredChannels) {
    int width, height, channels;
    unsigned char* pixels = stbi_load_from_memory(data.GetData(), data.GetSize(), &width, &height, &channels, desiredChannels);

    if (pixels) {
        return new Image(pixels, ImageInfo(width, height, desiredChannels > 0 ? desiredChannels : channels));
    }

    return nullptr;
}

Ref<Image> Image::Resize(const Ref<Image>& image, int width, int height) {
    ImageInfo imageInfo(width, height, image->mInfo.GetChannels());

    unsigned char* data = (unsigned char*)Memory::Allocate(imageInfo.GetDataSize());
    if (stbir_resize_uint8(image->mData, image->mInfo.GetWidth(), image->mInfo.GetHeight(), image->mInfo.GetStride(),
        data, width, height, imageInfo.GetStride(), imageInfo.GetChannels())) {
        return new Image(data, imageInfo);
    }

    return nullptr;
}

Ref<Image> Image::ResizeToNextPowerOfTwo(const Ref<Image>& image) {
    return Resize(image, Math::NextPowerOfTwo(image->GetInfo().GetWidth()), Math::NextPowerOfTwo(image->GetInfo().GetHeight()));
}

Image::Image(unsigned char* data, const ImageInfo& info)
    : mData(data), mInfo(info) {
}

Image::~Image() {
    Memory::Deallocate(mData);
}

int Image::CalculateMipmapCount() const {
    // TODO: Do it much better with fast integer log2.

    int width = mInfo.GetWidth();
    int height = mInfo.GetHeight();

    int mipmapCount = 0;
    while (width > 4 && height > 4) {
        ++mipmapCount;

        width /= 2;
        height /= 2;
    }

    return mipmapCount;
}

bool Image::IsPowerOfTwo() const {
    return Math::IsPowerOfTwo(mInfo.GetWidth()) && Math::IsPowerOfTwo(mInfo.GetHeight());
}

ArrayView<unsigned char> Image::GetData() const {
    return ArrayView<unsigned char>(mData, mInfo.GetDataSize());
}

const ImageInfo& Image::GetInfo() const {
    return mInfo;
}
