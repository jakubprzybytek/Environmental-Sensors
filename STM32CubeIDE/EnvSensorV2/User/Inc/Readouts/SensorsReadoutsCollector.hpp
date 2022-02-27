#ifndef INC_SENSORSREADOUTSCOLLECTOR_HPP_
#define INC_SENSORSREADOUTSCOLLECTOR_HPP_

enum ReadoutType {
	TemperatureAndPressure
};

struct TemperatureAndPressure {
	float temperature;
	float pressure;
};

struct ReadoutMessage {
	enum ReadoutType type;

	union {
		struct TemperatureAndPressure tp;
	};
};

class SensorsReadoutsCollector {
public:
	static void init();

	static void startThread();
	static void thread(void *pvParameters);
};

#endif /* INC_SENSORSREADOUTSCOLLECTOR_HPP_ */
