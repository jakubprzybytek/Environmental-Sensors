#include <gui/containers/HumidityContainer.hpp>

HumidityContainer::HumidityContainer() {
}

void HumidityContainer::initialize() {
	HumidityContainerBase::initialize();
}

void HumidityContainer::setValue(float value) {
	Unicode::snprintfFloat(valueTextAreaBuffer, VALUETEXTAREA_SIZE, "%.1f", value);
	valueTextArea.invalidate();
}
