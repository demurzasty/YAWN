#include <YAWN/Graphics/ImageInfo.hpp>

using namespace YAWN;

ImageInfo::ImageInfo(int width, int height, int channels)
    : mWidth(width), mHeight(height), mChannels(channels) {
}

ImageInfo::operator bool() const {
    return GetDataSize() > 0;
}

int ImageInfo::GetStride() const {
    return mWidth * mChannels;
}

int ImageInfo::GetWidth() const {
    return mWidth;
}

int ImageInfo::GetHeight() const {
    return mHeight;
}

int ImageInfo::GetChannels() const {
    return mChannels;
}

int ImageInfo::GetDataSize() const {
    return mWidth * mHeight * mChannels;
}
