#ifndef PRESSURECONTAINER_HPP
#define PRESSURECONTAINER_HPP

#include <gui_generated/containers/PressureContainerBase.hpp>

class PressureContainer: public PressureContainerBase {

private:
	static const uint8_t TEXTAREA_SIZE = 10;
	touchgfx::Unicode::UnicodeChar buffer[TEXTAREA_SIZE];

public:
	PressureContainer();
	virtual ~PressureContainer() {
	}

	virtual void initialize();

	void setValue(float value);

protected:
};

#endif // PRESSURECONTAINER_HPP
