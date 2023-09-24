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

Color4::Color4(const Color& color)
    : R(Math::FastFloatToInt(color.R * 255.0f))
    , G(Math::FastFloatToInt(color.G * 255.0f))
    , B(Math::FastFloatToInt(color.B * 255.0f))
    , A(Math::FastFloatToInt(color.A * 255.0f)) {
}
