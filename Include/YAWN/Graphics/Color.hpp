#pragma once 

namespace YAWN {
    struct Color {
        static const Color White;

        static const Color Black;

        static const Color Red;

        static const Color Green;

        static const Color Blue;

        static const Color CornflowerBlue;

        Color() = default;

        Color(float r, float g, float b);

        Color(float r, float g, float b, float a);

        float R, G, B, A;
    };

    struct Color4 {
        Color4() = default;

        Color4(const Color& color);

        unsigned char R, G, B, A;
    };
}
