#ifndef SRC_SENSORS_VOLTAGESENSOR_H_
#define SRC_SENSORS_VOLTAGESENSOR_H_

class VoltageSensor {

public:
	static void init();

private:
	static void startThread();

	static void printf(char *buffer, uint32_t adc, float voltage);
	static void thread(void *pvParameters);
};

#endif /* SRC_SENSORS_VOLTAGESENSOR_H_ */
