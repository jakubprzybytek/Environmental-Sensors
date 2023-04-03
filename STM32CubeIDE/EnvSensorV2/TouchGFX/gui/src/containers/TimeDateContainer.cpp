#include <gui/containers/TimeDateContainer.hpp>

TimeDateContainer::TimeDateContainer() {
	valueTextArea.setWildcard(buffer);
}

void TimeDateContainer::initialize() {
	TimeDateContainerBase::initialize();
}

void TimeDateContainer::setValue(DateTime value) {
	Unicode::snprintf(buffer, TEXTAREA_SIZE, "%u", value.seconds);
	valueTextArea.invalidate();
}
