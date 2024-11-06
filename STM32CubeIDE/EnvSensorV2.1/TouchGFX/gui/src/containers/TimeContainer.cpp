#include <gui/containers/TimeContainer.hpp>

TimeContainer::TimeContainer() {
}

void TimeContainer::initialize() {
	TimeContainerBase::initialize();
}

#ifndef SIMULATOR

void TimeContainer::setDateTime(DateTime dateTime) {
	Unicode::snprintf(timeTextAreaBuffer, TIMETEXTAREA_SIZE, "%02u:%02u:%02u", dateTime.hour, dateTime.minutes, dateTime.seconds);
	timeTextArea.invalidate();
}

#endif
