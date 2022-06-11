#ifndef INC_SENSORSREADOUTSCOLLECTOR_HPP_
#define INC_SENSORSREADOUTSCOLLECTOR_HPP_

class SensorsReadoutsCollector {
public:
	static void init();

	static void startThread();
	static void thread(void *pvParameters);
};

#endif /* INC_SENSORSREADOUTSCOLLECTOR_HPP_ */
