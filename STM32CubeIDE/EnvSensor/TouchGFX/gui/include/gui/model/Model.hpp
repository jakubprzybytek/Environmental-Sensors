#ifndef MODEL_HPP
#define MODEL_HPP

#include "stm32l4xx_hal.h"

class ModelListener;

class Model {
private:
	float co2;
	float preassure;
	float temperature;
	float humidity;

	float vdd;
	uint32_t availableSpaceKilobytes;

public:
	Model();

	void bind(ModelListener *listener) {
		modelListener = listener;
	}

	void tick();

	float getCo2() {
		return co2;
	}

	float getPreassure() {
		return preassure;
	}

	float getTemperature() {
		return temperature;
	}

	float getHumidity() {
		return humidity;
	}

	float getVdd() {
		return vdd;
	}

	uint32_t getAvailableSpaceKilobytes() {
		return availableSpaceKilobytes;
	}

protected:
	ModelListener *modelListener;
};

#endif // MODEL_HPP
