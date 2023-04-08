#include <gui/containers/TimeContainer.hpp>

TimeContainer::TimeContainer() {
	hourTextArea.setWildcard(buffer);
}

void TimeContainer::initialize() {
	TimeContainerBase::initialize();
}

void TimeContainer::setDateTime(DateTime dateTime) {
	Unicode::snprintfFloat(buffer, TEXTAREA_SIZE, "%.1f", dateTime.minutes);
	hourTextArea.invalidate();
}
