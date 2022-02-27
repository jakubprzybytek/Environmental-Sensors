#ifndef TEMPERATURECONTAINER_HPP
#define TEMPERATURECONTAINER_HPP

#include <gui_generated/containers/TemperatureContainerBase.hpp>

class TemperatureContainer: public TemperatureContainerBase {

private:
	static const uint8_t TEXTAREA_SIZE = 10;
	touchgfx::Unicode::UnicodeChar buffer[TEXTAREA_SIZE];

public:
	TemperatureContainer();
	virtual ~TemperatureContainer() {
	}

	virtual void initialize();

	void setValue(float value);

protected:
};

#endif // TEMPERATURECONTAINER_HPP
