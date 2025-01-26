#include <gui/containers/TimeContainer.hpp>

TimeContainer::TimeContainer() {
}

void TimeContainer::initialize() {
	TimeContainerBase::initialize();
}

#ifndef SIMULATOR

void TimeContainer::setDateTime(DateTime dateTime) {
	Unicode::snprintf(dateTextAreaBuffer, DATETEXTAREA_SIZE, "%02u.%02u.%04u", dateTime.day, dateTime.month, 2000 + dateTime.year);
	Unicode::snprintf(timeTextAreaBuffer, TIMETEXTAREA_SIZE, "%02u:%02u:%02u", dateTime.hour, dateTime.minutes, dateTime.seconds);
	dateTextArea.invalidate();
	timeTextArea.invalidate();
}

#endif
