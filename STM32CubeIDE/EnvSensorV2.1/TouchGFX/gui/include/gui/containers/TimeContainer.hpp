#ifndef TIMECONTAINER_HPP
#define TIMECONTAINER_HPP

#include <gui_generated/containers/TimeContainerBase.hpp>

#ifndef SIMULATOR

#include <Time/DateTime.hpp>

#endif

class TimeContainer: public TimeContainerBase {

public:
	TimeContainer();
	virtual ~TimeContainer() {
	}

	virtual void initialize();

#ifndef SIMULATOR

	void setDateTime(DateTime time);

#endif
};

#endif // TIMECONTAINER_HPP
