#include <gui/containers/SdCardContainer.hpp>

SdCardContainer::SdCardContainer() {
}

void SdCardContainer::initialize() {
	SdCardContainerBase::initialize();
}

void SdCardContainer::setValue(int16_t value) {
	Unicode::snprintfFloat(valueTextAreaBuffer, VALUETEXTAREA_SIZE, "%.2f", value);
	Unicode::snprintf(valueTextAreaBuffer, VALUETEXTAREA_SIZE, "%d", value);
	valueTextArea.invalidate();
}
