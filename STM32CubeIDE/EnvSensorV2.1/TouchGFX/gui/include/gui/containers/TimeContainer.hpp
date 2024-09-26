#ifndef TIMECONTAINER_HPP
#define TIMECONTAINER_HPP

#include <gui_generated/containers/TimeContainerBase.hpp>

#include <Utils/DateTime.hpp>

class TimeContainer: public TimeContainerBase {

public:
	TimeContainer();
	virtual ~TimeContainer() {
	}

	virtual void initialize();

	void setDateTime(DateTime time);
protected:
};

#endif // TIMECONTAINER_HPP
