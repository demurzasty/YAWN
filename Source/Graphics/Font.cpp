#include <YAWN/Graphics/Font.hpp>
#include <YAWN/Graphics/Renderer.hpp>
#include <YAWN/Runtime/Console.hpp>

#include <stb_rect_pack.h>
#include <stb_truetype.h>

using namespace YAWN;

struct Font::InternalData {
    stbtt_fontinfo Info;
    stbrp_context Context;
    stbrp_node Nodes[512];
};

Font::Font(const Ref<Buffer>& data)
    : mId(Renderer::CreateTexture(512, 512, TextureFormat::RGBA8, TextureFilter::Nearest, TextureWrapping::ClampToEdge, 1))
    , mData(data) {
    mInternalData = new InternalData();

    stbrp_init_target(&mInternalData->Context, 512, 512, mInternalData->Nodes, 512);

    stbtt_InitFont(&mInternalData->Info, (const unsigned char*)mData->GetData(), 0);

    mPixels.Resize(512 * 512, Color::Transparent);

    Renderer::SetTextureData(mId, 0, mPixels.GetData());
}

Font::~Font() {
    delete mInternalData;

    Renderer::DestroyTexture(mId);
}

const FontGlyph& Font::GetGlyph(int codepoint, int size) const {
    FontGlyph& glyph = mGlyphs.GetOrAdd(codepoint);
    if (glyph.Rectangle.Width > 0 && glyph.Rectangle.Height > 0) {
        return glyph;
    }

    int width, height, xoff, yoff;
    float scale = stbtt_ScaleForPixelHeight(&mInternalData->Info, float(size));
    unsigned char* bitmap = stbtt_GetCodepointBitmap(&mInternalData->Info, 0.0f, scale, codepoint, &width, &height, &xoff, &yoff);

    glyph.Advance = 8.0f;
    Rectangle rect = Pack(Vector2(float(width), float(height)));

    for (int y = 0; y < Math::FastFloatToInt(rect.Height); ++y) {
        for (int x = 0; x < Math::FastFloatToInt(rect.Width); ++x) {
            int index = (Math::FastFloatToInt(rect.Top) + y) * 512 + (Math::FastFloatToInt(rect.Left) + x);
            mPixels[index] = Color4(255, 255, 255, int(bitmap[y * Math::FastFloatToInt(rect.Width) + x]));
        }
    }

    stbtt_FreeBitmap(bitmap, 0);

    Renderer::SetTextureData(mId, 0, mPixels.GetData());

    int advance, lsb;
    stbtt_GetCodepointHMetrics(&mInternalData->Info, codepoint, &advance, &lsb);

    glyph.Advance = float(advance) * scale;
    glyph.Offset = { float(xoff), float(yoff) };
    glyph.Rectangle = rect;
    return glyph;
}

float Font::GetKerning(int codepoint1, int codepoint2, int size) const {
    float scale = stbtt_ScaleForPixelHeight(&mInternalData->Info, float(size));

    return stbtt_GetCodepointKernAdvance(&mInternalData->Info, codepoint1, codepoint2) * scale;
}

Vector2 Font::GetTextSize(const String& text, int size) const {
    float scale = stbtt_ScaleForPixelHeight(&mInternalData->Info, float(size));

    Vector2 textSize = Vector2(0.0f, size * 1.2f);
    for (int i = 0; i < text.GetSize(); ++i) {
        int advance, lsb;
        stbtt_GetCodepointHMetrics(&mInternalData->Info, text[i], &advance, &lsb);

        textSize.X += advance;

        if (i + 1 < text.GetSize()) {
            textSize.X += stbtt_GetCodepointKernAdvance(&mInternalData->Info, text[i], text[i + 1]);
        }
    }

    textSize.X *= scale;

    return textSize;
}

int Font::GetTextureId() const {
    return mId;
}

Rectangle Font::Pack(const Vector2& size) const {
    stbrp_rect rect;
    rect.w = Math::FastFloatToInt(size.X + 2.0f);
    rect.h = Math::FastFloatToInt(size.Y + 2.0f);
    stbrp_pack_rects(&mInternalData->Context, &rect, 1);

    return { rect.x + 1.0f, rect.y + 1.0f, size.X, size.Y };
}
