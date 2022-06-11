#include <gui/containers/CO2Container.hpp>

CO2Container::CO2Container() {
	valueTextArea.setWildcard(buffer);
}

void CO2Container::initialize() {
	CO2ContainerBase::initialize();
}

void CO2Container::setValue(float value) {
	Unicode::snprintfFloat(buffer, TEXTAREA_SIZE, "%.1f", value);
	valueTextArea.invalidate();
}
