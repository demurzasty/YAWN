#pragma once 

#include "Button.hpp"
#include "Popup.hpp"

namespace YAWN {
    class MenuButton : public Button {
        YAWN_OBJECT(MenuButton, Button);

    public:
        MenuButton();

        virtual ~MenuButton() = default;

        virtual void Enter() override;

        virtual void Exit() override;

        virtual void Draw() override;

        const Ref<Popup>& GetPopup() const;

    private:
        void OnClicked(Ref<Button> button);

    private:
        Ref<Popup> mPopup;
    };
}