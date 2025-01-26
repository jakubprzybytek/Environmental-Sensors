#ifndef VOLTAGECONTAINER_HPP
#define VOLTAGECONTAINER_HPP

#include <gui_generated/containers/VoltageContainerBase.hpp>
#include <UIControllers/AppState.hpp>

class VoltageContainer: public VoltageContainerBase {

public:
	VoltageContainer();
	virtual ~VoltageContainer() {
	}

	virtual void initialize();

	void setValue(float value);
	void setBatteryLevel(BatteryLevel batteryLevel);

protected:
};

#endif // VOLTAGECONTAINER_HPP
