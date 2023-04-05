#ifndef TIMECONTAINER_HPP
#define TIMECONTAINER_HPP

#include <gui_generated/containers/TimeContainerBase.hpp>

#include <Utils/DateTime.hpp>

class TimeContainer: public TimeContainerBase {

private:
	static const uint8_t TEXTAREA_SIZE = 10;
	touchgfx::Unicode::UnicodeChar buffer[TEXTAREA_SIZE];

public:
	TimeContainer();
	virtual ~TimeContainer() {
	}

	virtual void initialize();

	void setDateTime(DateTime time);
protected:
};

#endif // TIMECONTAINER_HPP
