#ifndef DATETIMESETTINGSCONTAINER_HPP
#define DATETIMESETTINGSCONTAINER_HPP

#include <gui_generated/containers/DateTimeSettingsContainerBase.hpp>

class DateTimeSettingsContainer : public DateTimeSettingsContainerBase
{
public:
    DateTimeSettingsContainer();
    virtual ~DateTimeSettingsContainer() {}

    virtual void initialize();
protected:
};

#endif // DATETIMESETTINGSCONTAINER_HPP
