#include <gui/containers/PressureContainer.hpp>

PressureContainer::PressureContainer() {
}

void PressureContainer::initialize() {
	PressureContainerBase::initialize();
}

void PressureContainer::setValue(float value) {
	Unicode::snprintfFloat(valueTextAreaBuffer, VALUETEXTAREA_SIZE, "%.1f", value);
	valueTextArea.invalidate();
}
