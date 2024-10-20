#ifndef PRESSURECONTAINER_HPP
#define PRESSURECONTAINER_HPP

#include <gui_generated/containers/PressureContainerBase.hpp>

class PressureContainer: public PressureContainerBase {

public:
	PressureContainer();
	virtual ~PressureContainer() {
	}

	virtual void initialize();

	void setValue(float value);

protected:
};

#endif // PRESSURECONTAINER_HPP
