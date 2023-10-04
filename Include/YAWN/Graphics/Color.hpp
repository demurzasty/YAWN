#pragma once 

namespace YAWN {
    struct Color4;

    struct Color {
        static const Color White;

        static const Color Black;

        static const Color Red;

        static const Color Green;

        static const Color Blue;

        static const Color CornflowerBlue;

        static const Color Transparent;

        Color() = default;

        Color(float r, float g, float b);

        Color(float r, float g, float b, float a);

        Color(const Color4& color);

        explicit Color(const float color[4]);

        static Color Lerp(const Color& from, const Color& to, float factor);

        float R, G, B, A;
    };

    struct Color4 {
        Color4() = default;

        Color4(const Color& color);

        Color4(int r, int g, int b);

        Color4(int r, int g, int b, int a);

        unsigned char R, G, B, A;
    };
}
