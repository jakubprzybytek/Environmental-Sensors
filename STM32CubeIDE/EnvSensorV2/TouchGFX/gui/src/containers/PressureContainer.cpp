#include <gui/containers/PressureContainer.hpp>

PressureContainer::PressureContainer() {
	valueTextArea.setWildcard(buffer);
}

void PressureContainer::initialize() {
	PressureContainerBase::initialize();
}

void PressureContainer::setValue(float value) {
	Unicode::snprintfFloat(buffer, TEXTAREA_SIZE, "%.1f", value);
	valueTextArea.invalidate();
}
