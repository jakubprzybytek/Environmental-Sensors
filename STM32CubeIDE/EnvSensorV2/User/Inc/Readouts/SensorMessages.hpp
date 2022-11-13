#ifndef INC_SENSORMESSAGES_HPP_
#define INC_SENSORMESSAGES_HPP_

enum ReadoutType {
	BMP, BME, SCD
};

struct TemperatureAndPressure {
	float temperature;
	float pressure;
};

struct TemperaturePressureAndHumidity {
	float temperature;
	float pressure;
	float humidity;
};

struct CO2TemperatureAndHumidity {
	float co2;
	float temperature;
	float humidity;
};

typedef struct ReadoutMessage {
	enum ReadoutType type;

	union {
		struct TemperatureAndPressure tp;
		struct TemperaturePressureAndHumidity tph;
		struct CO2TemperatureAndHumidity cth;
	};
} ReadoutMessage_t;

#endif /* INC_SENSORMESSAGES_HPP_ */
