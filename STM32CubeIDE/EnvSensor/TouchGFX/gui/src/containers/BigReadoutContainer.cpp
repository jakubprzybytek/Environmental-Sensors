#include <gui/containers/BigReadoutContainer.hpp>

BigReadoutContainer::BigReadoutContainer() {
	valueTextArea.setWildcard(buffer);
}

void BigReadoutContainer::setUpLabels(TEXTS label, TEXTS unit) {
	labelTextArea.setTypedText(touchgfx::TypedText(label));
	unitTextArea.setTypedText(touchgfx::TypedText(unit));
}

void BigReadoutContainer::initialize() {
	BigReadoutContainerBase::initialize();
}

void BigReadoutContainer::setValue(float value) {
	Unicode::snprintfFloat(buffer, TEXTAREA_SIZE, "%.2f", value);
	valueTextArea.invalidate();
}
