#ifndef CO2CONTAINER_HPP
#define CO2CONTAINER_HPP

#include <gui_generated/containers/CO2ContainerBase.hpp>

class CO2Container: public CO2ContainerBase {

public:
	CO2Container();
	virtual ~CO2Container() {
	}

	virtual void initialize();

	void setValue(float value);

protected:
};

#endif // CO2CONTAINER_HPP
