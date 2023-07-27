#pragma once 

namespace YAWN {
    class ImageInfo {
    public:
        ImageInfo() = default;

        ImageInfo(int width, int height, int channels);

        operator bool() const;

        int GetStride() const;

        int GetWidth() const;

        int GetHeight() const;

        int GetChannels() const;

        int GetDataSize() const;

    private:
        int mWidth = 0;
        int mHeight = 0;
        int mChannels = 0;
    };
}