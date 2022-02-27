#include <gui/containers/TemperatureContainer.hpp>

TemperatureContainer::TemperatureContainer() {
	valueTextArea.setWildcard(buffer);
}

void TemperatureContainer::initialize() {
	TemperatureContainerBase::initialize();
}

void TemperatureContainer::setValue(float value) {
	Unicode::snprintfFloat(buffer, TEXTAREA_SIZE, "%.1f", value);
	valueTextArea.invalidate();
}
