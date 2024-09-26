#include <gui/containers/VoltageContainer.hpp>

VoltageContainer::VoltageContainer() {
}

void VoltageContainer::initialize() {
	VoltageContainerBase::initialize();
}

void VoltageContainer::setValue(float value) {
	Unicode::snprintfFloat(valueTextAreaBuffer, VALUETEXTAREA_SIZE, "%.2f", value);
	valueTextArea.invalidate();
}
