#ifndef INC_SENSORMESSAGES_HPP_
#define INC_SENSORMESSAGES_HPP_

enum ReadoutType {
	Voltage, BMP, BME, SCD, HPMA
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

struct Particles {
	uint16_t pm1;
	uint16_t pm2_5;
	uint16_t pm4;
	uint16_t pm10;
};

typedef struct ReadoutMessage {
	enum ReadoutType type;

	union {
		struct {
			float voltage;
		} v;
		struct TemperatureAndPressure tp;
		struct TemperaturePressureAndHumidity tph;
		struct CO2TemperatureAndHumidity cth;
		struct Particles p;
	};
} ReadoutMessage_t;

#endif /* INC_SENSORMESSAGES_HPP_ */
