#include <gui/containers/TemperatureContainer.hpp>

TemperatureContainer::TemperatureContainer() {
}

void TemperatureContainer::initialize() {
	TemperatureContainerBase::initialize();
}

void TemperatureContainer::setValue(float value) {
	Unicode::snprintfFloat(valueTextAreaBuffer, VALUETEXTAREA_SIZE, "%.1f", value);
	valueTextArea.invalidate();
}
