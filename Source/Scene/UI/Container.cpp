#include <YAWN/Scene/UI/Container.hpp>

using namespace YAWN;

void Container::SetMargin(float margin) {
    mMargin = margin;
}

float Container::GetMargin() const {
    return mMargin;
}
