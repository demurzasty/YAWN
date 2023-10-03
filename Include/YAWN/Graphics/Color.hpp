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

        float R, G, B, A;
    };

    struct Color4 {
        Color4() = default;

        Color4(const Color& color);

        constexpr Color4(int r, int g, int b) : R(r), G(g), B(b), A(255) {}

        constexpr Color4(int r, int g, int b, int a) : R(r), G(g), B(b), A(a) {}

        unsigned char R, G, B, A;
    };
}
