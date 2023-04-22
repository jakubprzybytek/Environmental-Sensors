#ifndef HUMIDITYCONTAINER_HPP
#define HUMIDITYCONTAINER_HPP

#include <gui_generated/containers/HumidityContainerBase.hpp>

class HumidityContainer: public HumidityContainerBase {

public:
	HumidityContainer();
	virtual ~HumidityContainer() {
	}

	virtual void initialize();

	void setValue(float value);

protected:
};

#endif // HUMIDITYCONTAINER_HPP
