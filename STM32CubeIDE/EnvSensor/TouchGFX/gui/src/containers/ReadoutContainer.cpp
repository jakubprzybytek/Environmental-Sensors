#include <gui/containers/ReadoutContainer.hpp>

ReadoutContainer::ReadoutContainer() {
	valueTextArea.setWildcard(buffer);
}

void ReadoutContainer::setUpLabels(TEXTS label, TEXTS unit) {
	labelTextArea.setTypedText(touchgfx::TypedText(label));
	unitTextArea.setTypedText(touchgfx::TypedText(unit));
}

void ReadoutContainer::initialize() {
	ReadoutContainerBase::initialize();
}

void ReadoutContainer::setValue(float value) {
	Unicode::snprintfFloat(buffer, TEXTAREA_SIZE, "%.2f", value);
	valueTextArea.invalidate();
}
