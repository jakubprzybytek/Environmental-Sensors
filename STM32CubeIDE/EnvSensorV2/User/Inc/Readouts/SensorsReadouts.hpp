#ifndef INC_SENSORSREADOUTS_HPP_
#define INC_SENSORSREADOUTS_HPP_

class SensorsReadouts {
public:
	static void submitTemperatureAndPressure(float temperature, float pressure);
	static void submitC02AndTemperature(float co2, float temperature);
};

#endif /* INC_SENSORSREADOUTS_HPP_ */
