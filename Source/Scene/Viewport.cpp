#include <YAWN/Scene/Viewport.hpp>
#include <YAWN/Graphics/Renderer.hpp>
#include <YAWN/Platform/Window.hpp>
#include <YAWN/Runtime/Console.hpp>

using namespace YAWN;

void Viewport::Enter() {
	Base::Enter();

	mViewportId = Renderer::CreateViewport(Math::FastFloatToInt(mSize.X), Math::FastFloatToInt(mSize.Y), mDirectToScreen);
}

void Viewport::Exit() {
	Base::Exit();

	Renderer::DestroyViewport(mViewportId);
}

void Viewport::Update(float timeStep) {
	Base::Update(timeStep);

	if (mDirty && mViewportId) {
		Renderer::SetViewportSize(mViewportId, Math::FastFloatToInt(mSize.X), Math::FastFloatToInt(mSize.Y));
		
		mDirty = false;
	}
}

void Viewport::SetSize(const Vector2& size) {
	if (mSize.X != size.X || mSize.Y != size.Y) {
		mSize = size;

		mDirty = true;
	}
}

const Vector2& Viewport::GetSize() const {
	return mSize;
}

void Viewport::SetRenderDirectToScreen(bool directToScreen) {
	mDirectToScreen = directToScreen;
}

bool Viewport::IsRenderDirectToScreen() const {
	return mDirectToScreen;
}

int Viewport::GetId() const {
	return mViewportId;
}
