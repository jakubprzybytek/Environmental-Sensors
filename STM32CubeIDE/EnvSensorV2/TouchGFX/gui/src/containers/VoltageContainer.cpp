#include <gui/containers/VoltageContainer.hpp>

VoltageContainer::VoltageContainer() {
	valueTextArea.setWildcard(buffer);
}

void VoltageContainer::initialize() {
	VoltageContainerBase::initialize();
}

void VoltageContainer::setValue(float value) {
	Unicode::snprintfFloat(buffer, TEXTAREA_SIZE, "%.2f", value);
	valueTextArea.invalidate();
}
