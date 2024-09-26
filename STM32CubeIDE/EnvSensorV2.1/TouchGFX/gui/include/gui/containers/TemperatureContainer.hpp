#ifndef TEMPERATURECONTAINER_HPP
#define TEMPERATURECONTAINER_HPP

#include <gui_generated/containers/TemperatureContainerBase.hpp>

class TemperatureContainer: public TemperatureContainerBase {

public:
	TemperatureContainer();
	virtual ~TemperatureContainer() {
	}

	virtual void initialize();

	void setValue(float value);

protected:
};

#endif // TEMPERATURECONTAINER_HPP
