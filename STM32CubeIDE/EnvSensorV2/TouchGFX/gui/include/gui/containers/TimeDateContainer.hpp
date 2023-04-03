#ifndef TIMEDATECONTAINER_HPP
#define TIMEDATECONTAINER_HPP

#include <gui_generated/containers/TimeDateContainerBase.hpp>

#include <Utils/DateTime.hpp>

class TimeDateContainer: public TimeDateContainerBase {

private:
	static const uint8_t TEXTAREA_SIZE = 20;
	touchgfx::Unicode::UnicodeChar buffer[TEXTAREA_SIZE];

public:
	TimeDateContainer();
	virtual ~TimeDateContainer() {
	}

	virtual void initialize();

	void setValue(DateTime value);

protected:
};

#endif // TIMEDATECONTAINER_HPP
