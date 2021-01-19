#ifndef MODEL_HPP
#define MODEL_HPP

#include "stm32l4xx_hal.h"

#include "EnvState.hpp"

class ModelListener;

class Model {
private:
	float co2;
	float pressure;
	float temperature;
	float humidity;

	float vdd;

	bool sdActive;
	uint32_t sdAvailableSpaceKilobytes;

	char *fileContent;

	SettingsEditField settingsEditField;

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
		return pressure;
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

	bool getSdActive() {
		return sdActive;
	}

	uint32_t getSdAvailableSpaceKilobytes() {
		return sdAvailableSpaceKilobytes;
	}

	char* getFileContent() {
		return fileContent;
	}

	SettingsEditField getSettingsEditField() {
		return settingsEditField;
	}

protected:
	ModelListener *modelListener;
};

#endif // MODEL_HPP
