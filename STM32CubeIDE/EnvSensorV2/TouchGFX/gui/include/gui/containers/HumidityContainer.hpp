#ifndef HUMIDITYCONTAINER_HPP
#define HUMIDITYCONTAINER_HPP

#include <gui_generated/containers/HumidityContainerBase.hpp>

class HumidityContainer: public HumidityContainerBase {

private:
	static const uint8_t TEXTAREA_SIZE = 10;
	touchgfx::Unicode::UnicodeChar buffer[TEXTAREA_SIZE];

public:
	HumidityContainer();
	virtual ~HumidityContainer() {
	}

	virtual void initialize();

	void setValue(float value);

protected:
};

#endif // HUMIDITYCONTAINER_HPP
