#include <YAWN/Scene/UI/MenuButton.hpp>
#include <YAWN/Scene/Scene.hpp>
#include <YAWN/Runtime/Console.hpp>

using namespace YAWN;

MenuButton::MenuButton() {
    mPopup = new Popup();
    mPopup->SetVertical(true);
    mPopup->SetMinimumSize(200.0f);
    mPopup->SetPadding(4.0f);

    GetClickedSignal().Connect<&MenuButton::OnClicked>(this);
}

void MenuButton::Enter() {
    Base::Enter();

    //Scene::GetRoot()->AddChild(mPopup);
}

void MenuButton::Exit() {
    Base::Exit();

    if (mPopup->GetParent()) {
        Scene::GetRoot()->RemoveChild(mPopup);
    }
}

void MenuButton::Draw() {
    Base::Draw();

    if (const Ref<Theme>& theme = GetTheme(); theme) {
        //  DrawRect(GetGlobalRectangle(), theme->GetFrameBorderColor());
    }
}

const Ref<Popup>& MenuButton::GetPopup() const {
    return mPopup;
}

void MenuButton::OnClicked(Ref<Button> button) {
    if (!mPopup->GetParent()) {
        Scene::GetRoot()->AddChild(mPopup);

        mPopup->SetGlobalTransform(Matrix3::CreateTranslation2D(GetGlobalPosition() + Vector2(0.0f, GetLocalSize().Y)));
    }
}
