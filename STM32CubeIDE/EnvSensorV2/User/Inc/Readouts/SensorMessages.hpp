#ifndef INC_SENSORMESSAGES_HPP_
#define INC_SENSORMESSAGES_HPP_

enum ReadoutType {
	TemperatureAndPressure, CO2AndTemperature
};

struct TemperatureAndPressure {
	float temperature;
	float pressure;
};

struct CO2AndTemperature {
	float co2;
	float temperature;
};

typedef struct ReadoutMessage {
	enum ReadoutType type;

	union {
		struct TemperatureAndPressure tp;
		struct CO2AndTemperature ct;
	};
} ReadoutMessage_t;

#endif /* INC_SENSORMESSAGES_HPP_ */