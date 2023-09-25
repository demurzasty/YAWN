#include <YAWN/Graphics/Theme.hpp>

#include "BuiltIn/RobotoMedium.ttf.h"

using namespace YAWN;

Ref<Theme> Theme::CreateDefault() {
    Ref<Theme> theme = new Theme();
    theme->SetDefaultFont(new Font(new Buffer(roboto_medium, sizeof(roboto_medium))));
    return theme;
}

void Theme::SetDefaultFont(const Ref<Font>& font) {
    mDefaultFont = font;
}

const Ref<Font>& Theme::GetDefaultFont() const {
    return mDefaultFont;
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

