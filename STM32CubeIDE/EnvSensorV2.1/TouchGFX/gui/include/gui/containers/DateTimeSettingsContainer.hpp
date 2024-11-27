#ifndef DATETIMESETTINGSCONTAINER_HPP
#define DATETIMESETTINGSCONTAINER_HPP

#include <gui_generated/containers/DateTimeSettingsContainerBase.hpp>

#ifndef SIMULATOR

#include <Time/DateTime.hpp>
#include <UIControllers/AppState.hpp>

#endif

class DateTimeSettingsContainer: public DateTimeSettingsContainerBase {
public:
	DateTimeSettingsContainer();
	virtual ~DateTimeSettingsContainer() {
	}

	virtual void initialize();

#ifndef SIMULATOR

	void setDateTime(DateTime time);

	void setFieldUnderEdit(SettingsField settingsField);

#endif

protected:
};

#endif // DATETIMESETTINGSCONTAINER_HPP
