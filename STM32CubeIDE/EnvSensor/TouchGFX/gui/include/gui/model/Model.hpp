#ifndef MODEL_HPP
#define MODEL_HPP

#include <stm32l4xx_hal.h>

class ModelListener;

class Model
{
private:
	uint32_t preassure;
	int16_t temperature;

public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    uint32_t getPreassure() {
    	return preassure;
    }

    int16_t getTemperature() {
    	return temperature;
    }

protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
