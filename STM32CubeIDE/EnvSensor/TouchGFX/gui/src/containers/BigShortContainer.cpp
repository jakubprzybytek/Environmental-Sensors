#include <gui/containers/BigShortContainer.hpp>

BigShortContainer::BigShortContainer() {
	valueTextArea.setWildcard(buffer);
}

void BigShortContainer::setUpLabels(TEXTS label, TEXTS unit) {
	labelTextArea.setTypedText(touchgfx::TypedText(label));
	unitTextArea.setTypedText(touchgfx::TypedText(unit));
}

void BigShortContainer::initialize() {
	BigShortContainerBase::initialize();
}

void BigShortContainer::setValue(float value) {
	Unicode::snprintfFloat(buffer, TEXTAREA_SIZE, "%.1f", value);
	valueTextArea.invalidate();
}
