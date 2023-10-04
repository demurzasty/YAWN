#include <YAWN/Graphics/Theme.hpp>
#include <YAWN/Graphics/Image.hpp>

#include "BuiltIn/RobotoMedium.ttf.h"
#include "BuiltIn/Icons.png.h"

using namespace YAWN;

Ref<Theme> Theme::CreateDefault() {
    Ref<Theme> theme = new Theme();
    theme->SetDefaultFont(new Font(new Buffer(RobotoMediumFontData, sizeof(RobotoMediumFontData))));

    Ref<Image> iconsImage = Image::FromMemory(ArrayView<const unsigned char>(IconsImageData, sizeof(IconsImageData)), 4);

    Ref<Texture> iconsTexture = new Texture(iconsImage->GetInfo().GetWidth(), iconsImage->GetInfo().GetHeight(), TextureFormat::RGBA8, TextureFilter::Linear, TextureWrapping::ClampToEdge, 1);
    iconsTexture->SetData(0, iconsImage->GetData().GetData());
    theme->SetIconsTexture(iconsTexture);

    return theme;
}

void Theme::SetDefaultFont(const Ref<Font>& font) {
    mDefaultFont = font;
}

const Ref<Font>& Theme::GetDefaultFont() const {
    return mDefaultFont;
}

void Theme::SetIconsTexture(const Ref<Texture>& texture) {
    mIconsTexture = texture;
}

const Ref<Texture>& Theme::GetIconsTexture() const {
    return mIconsTexture;
}

void Theme::SetContainerColor(const Color4& color) {
    mContainerColor = color;
}

const Color4& Theme::GetContainerColor() const {
    return mContainerColor;
}

void Theme::SetButtonDefaultColor(const Color4& color) {
    mButtonDefaultColor = color;
}

const Color4& Theme::GetButtonDefaultColor() const {
    return mButtonDefaultColor;
}

void Theme::SetButtonHoverColor(const Color4& color) {
    mButtonHoverColor = color;
}

const Color4& Theme::GetButtonHoverColor() const {
    return mButtonHoverColor;
}

void Theme::SetButtonActiveColor(const Color4& color) {
    mButtonActiveColor = color;
}

const Color4& Theme::GetButtonActiveColor() const {
    return mButtonActiveColor;
}

void Theme::SetButtonTextColor(const Color4& color) {
    mButtonTextColor = color;
}

const Color4& Theme::GetButtonTextColor() const {
    return mButtonTextColor;
}

void Theme::SetSplitterColor(const Color4& color) {
    mSplitterColor = color;
}

const Color4& Theme::GetSplitterColor() const {
    return mSplitterColor;
}

void Theme::SetActiveSplitterColor(const Color4& color) {
    mActiveSplitterColor = color;
}

const Color4& Theme::GetActiveSplitterColor() const {
    return mActiveSplitterColor;
}

void Theme::SetSectionIndicatorColor(const Color4& color) {
    mSectionIndicatorColor = color;
}

const Color4& Theme::GetSectionIndicatorColor() const {
    return mSectionIndicatorColor;
}

void Theme::SetSectionBarColor(const Color4& color) {
    mSectionBarColor = color;
}

const Color4& Theme::GetSectionBarColor() const {
    return mSectionBarColor;
}

void Theme::SetFrameBorderColor(const Color4& color) {
    mFrameBorderColor = color;
}

const Color4& Theme::GetFrameBorderColor() const {
    return mFrameBorderColor;
}

void Theme::SetTreeItemEvenColor(const Color4& color) {
    mTreeItemEvenColor = color;
}

const Color4& Theme::GetTreeItemEvenColor() const {
    return mTreeItemEvenColor;
}

void Theme::SetTreeItemOddColor(const Color4& color) {
    mTreeItemOddColor = color;
}

const Color4& Theme::GetTreeItemOddColor() const {
    return mTreeItemOddColor;
}

void Theme::SetTextBoxBorderColor(const Color4& color) {
    mTextBoxBorderColor = color;
}

const Color4& Theme::GetTextBoxBorderColor() const {
    return mTextBoxBorderColor;
}

