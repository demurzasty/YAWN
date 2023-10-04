#include <YAWN/Graphics/Color.hpp>
#include <YAWN/Math/Math.hpp>

using namespace YAWN;

const Color Color::White = Color(1.0f, 1.0f, 1.0f);

const Color Color::Black = Color(0.0f, 0.0f, 0.0f);

const Color Color::Red = Color(1.0f, 0.0f, 0.0f);

const Color Color::Green = Color(0.0f, 1.0f, 0.0f);

const Color Color::Blue = Color(0.0f, 0.0f, 1.0f);

const Color Color::CornflowerBlue = Color(100.0f / 255.0f, 149.0f / 255.0f, 237.0f / 255.0f);

const Color Color::Transparent = Color(0.0f, 0.0f, 0.0f, 0.0f);

Color::Color(float r, float g, float b)
    : R(r), G(g), B(b), A(1.0f) {
}

Color::Color(float r, float g, float b, float a)
    : R(r), G(g), B(b), A(a) {
}

Color::Color(const Color4& color)
    : R(color.R / 255.0f), G(color.G / 255.0f), B(color.B / 255.0f), A(color.A / 255.0f) {
}

Color::Color(const float color[4])
    : R(color[0]), G(color[1]), B(color[2]), A(color[3]) {
}

Color Color::Lerp(const Color& from, const Color& to, float factor) {
    return Color(
        from.R + (to.R - from.R) * factor,
        from.G + (to.G - from.G) * factor,
        from.B + (to.B - from.B) * factor,
        from.A + (to.A - from.A) * factor
    );
}

Color4::Color4(int r, int g, int b)
    : R(r), G(g), B(b), A(255) {
}

Color4::Color4(int r, int g, int b, int a)
    : R(r), G(g), B(b), A(a) {
}

Color4::Color4(const Color& color)
    : R(Math::FastFloatToInt(color.R * 255.0f))
    , G(Math::FastFloatToInt(color.G * 255.0f))
    , B(Math::FastFloatToInt(color.B * 255.0f))
    , A(Math::FastFloatToInt(color.A * 255.0f)) {
}
