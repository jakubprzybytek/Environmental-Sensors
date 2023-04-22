#include <gui/containers/CO2Container.hpp>

CO2Container::CO2Container() {
}

void CO2Container::initialize() {
	CO2ContainerBase::initialize();
}

void CO2Container::setValue(float value) {
	Unicode::snprintfFloat(valueTextAreaBuffer, VALUETEXTAREA_SIZE, "%.1f", value);
	valueTextArea.invalidate();
}
