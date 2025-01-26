#ifndef INC_SENSORSREADOUTSCOLLECTOR_HPP_
#define INC_SENSORSREADOUTSCOLLECTOR_HPP_

#include <UIControllers/AppState.hpp>

class SensorsReadoutsCollector {
public:
	static void start();

	static void startThread();
	static void thread(void *pvParameters);

private:
	static BatteryLevel determineBatteryLevel(BatteryLevel currentBatteryLevel, float batteryVoltage);
	static void checkBatteryState(AppState &appState, float batteryVoltage);
};

#endif /* INC_SENSORSREADOUTSCOLLECTOR_HPP_ */
