#ifndef CO2CONTAINER_HPP
#define CO2CONTAINER_HPP

#include <gui_generated/containers/CO2ContainerBase.hpp>

class CO2Container: public CO2ContainerBase {

private:
	static const uint8_t TEXTAREA_SIZE = 10;
	touchgfx::Unicode::UnicodeChar buffer[TEXTAREA_SIZE];

public:
	CO2Container();
	virtual ~CO2Container() {
	}

	virtual void initialize();

	void setValue(float value);

protected:
};

#endif // CO2CONTAINER_HPP
