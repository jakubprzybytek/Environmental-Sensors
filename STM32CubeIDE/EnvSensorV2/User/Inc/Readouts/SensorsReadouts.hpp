#ifndef INC_SENSORSREADOUTS_HPP_
#define INC_SENSORSREADOUTS_HPP_

enum ReadoutType {
	TemperatureAndPressure,
	CO2AndTemperature
};

struct TemperatureAndPressure {
	float temperature;
	float pressure;
};

struct CO2AndTemperature {
	float co2;
	float temperature;
};

struct ReadoutMessage {
	enum ReadoutType type;

	union {
		struct TemperatureAndPressure tp;
		struct CO2AndTemperature ct;
	};
};

class SensorsReadouts {
public:
	static void submitTemperatureAndPressure(float temperature, float pressure);
	static void submitC02AndTemperature(float co2, float temperature);
};

#endif /* INC_SENSORSREADOUTS_HPP_ */
