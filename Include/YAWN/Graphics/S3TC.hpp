#pragma once 

#include "Image.hpp"

#include <YAWN/Core/ArrayView.hpp>

namespace YAWN {
    class S3TC {
    public:
        static void BC1(const void* uncompressedPixels, int uncompressedSize, int stride, void* compressedPixels);

        static Array<unsigned char> BC1(const Ref<Image>& image);

        static void BC3(const void* uncompressedPixels, int uncompressedSize, int stride, void* compressedPixels);

        static Array<unsigned char> BC3(const Ref<Image>& image);

        static void BC4(const void* uncompressedPixels, int uncompressedSize, int stride, void* compressedPixels);

        static Array<unsigned char> BC4(const Ref<Image>& image);
    };
}
