#include <gui/containers/HumidityContainer.hpp>

HumidityContainer::HumidityContainer() {
	valueTextArea.setWildcard(buffer);
}

void HumidityContainer::initialize() {
	HumidityContainerBase::initialize();
}

void HumidityContainer::setValue(float value) {
	Unicode::snprintfFloat(buffer, TEXTAREA_SIZE, "%.1f", value);
	valueTextArea.invalidate();
}
