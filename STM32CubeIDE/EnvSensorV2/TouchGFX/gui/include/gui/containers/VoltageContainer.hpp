#ifndef VOLTAGECONTAINER_HPP
#define VOLTAGECONTAINER_HPP

#include <gui_generated/containers/VoltageContainerBase.hpp>

class VoltageContainer: public VoltageContainerBase {

public:
	VoltageContainer();
	virtual ~VoltageContainer() {
	}

	virtual void initialize();

	void setValue(float value);

protected:
};

#endif // VOLTAGECONTAINER_HPP
