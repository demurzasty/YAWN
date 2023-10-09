#include <YAWN/Graphics/Font.hpp>
#include <YAWN/Graphics/Renderer.hpp>
#include <YAWN/Runtime/Console.hpp>

#include <stb_rect_pack.h>
#include <stb_truetype.h>

using namespace YAWN;

struct Font::InternalData {
    stbtt_fontinfo Info;
    stbrp_context Context;
    stbrp_node Nodes[256];
};

void Font::Register(Meta<Font>& meta) {
    meta.SetName(L"Font");
    meta.SetBase<Resource>();
}

Font::Font(const Ref<Buffer>& data)
    : mId(Renderer::CreateTexture(256, 256, TextureFormat::RGBA8, TextureFilter::Nearest, TextureWrapping::ClampToEdge, 1))
    , mData(data) {
    mInternalData = new InternalData();

    stbrp_init_target(&mInternalData->Context, 256, 256, mInternalData->Nodes, 256);

    stbtt_InitFont(&mInternalData->Info, (const unsigned char*)mData->GetData(), 0);

    mPixels.Resize(256 * 256, Color::Transparent);

    Renderer::SetTextureData(mId, 0, mPixels.GetData());
}

Font::~Font() {
    delete mInternalData;

    Renderer::DestroyTexture(mId);
}

void Font::Validate() {
    if (mDirty) {
        Renderer::SetTextureData(mId, 0, mPixels.GetData());

        mDirty = false;
    }
}

const FontGlyph& Font::GetGlyph(int codepoint, int size) const {
    FontGlyph& glyph = mGlyphs.GetOrAdd((codepoint & 0xFFFFF) | ((size & 0xFFF) << 20));
    if (glyph.Rectangle.Size.X > 0 && glyph.Rectangle.Size.Y > 0) {
        return glyph;
    }

    int width, height, xoff, yoff;
    float scale = stbtt_ScaleForPixelHeight(&mInternalData->Info, float(size));
    unsigned char* bitmap = stbtt_GetCodepointBitmap(&mInternalData->Info, scale, scale, codepoint, &width, &height, &xoff, &yoff);
   
    Rectangle rect = Pack(Vector2(float(width), float(height)));

    for (int y = 0; y < Math::FastFloatToInt(rect.Size.Y); ++y) {
        for (int x = 0; x < Math::FastFloatToInt(rect.Size.X); ++x) {
            int index = (Math::FastFloatToInt(rect.Position.Y) + y) * 256 + (Math::FastFloatToInt(rect.Position.X) + x);
            mPixels[index] = Color4(255, 255, 255, int(bitmap[y * Math::FastFloatToInt(rect.Size.X) + x]));
        }
    }

    stbtt_FreeBitmap(bitmap, 0);

    mDirty = true;

    int advance, lsb;
    stbtt_GetCodepointHMetrics(&mInternalData->Info, codepoint, &advance, &lsb);

    glyph.Advance = (advance) * scale;
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

OID Font::GetTextureId() const {
    return mId;
}

Rectangle Font::Pack(const Vector2& size) const {
    stbrp_rect rect;
    rect.w = Math::FastFloatToInt(size.X + 1.0f);
    rect.h = Math::FastFloatToInt(size.Y + 1.0f);
    stbrp_pack_rects(&mInternalData->Context, &rect, 1);

    return Rectangle(rect.x + 1.0f, rect.y + 1.0f, size.X, size.Y);
}
