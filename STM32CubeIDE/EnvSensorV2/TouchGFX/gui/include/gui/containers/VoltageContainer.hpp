#ifndef VOLTAGECONTAINER_HPP
#define VOLTAGECONTAINER_HPP

#include <gui_generated/containers/VoltageContainerBase.hpp>

class VoltageContainer: public VoltageContainerBase {

private:
	static const uint8_t TEXTAREA_SIZE = 10;
	touchgfx::Unicode::UnicodeChar buffer[TEXTAREA_SIZE];

public:
	VoltageContainer();
	virtual ~VoltageContainer() {
	}

	virtual void initialize();

	void setValue(float value);

protected:
};

#endif // VOLTAGECONTAINER_HPP
