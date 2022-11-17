#ifndef INC_SENSORSREADOUTS_HPP_
#define INC_SENSORSREADOUTS_HPP_

class SensorsReadouts {
public:
	static void submitVoltage(float voltage);
	static void submitBmpTemperatureAndPressure(float temperature, float pressure);
	static void submitBmeTemperaturePressureHumidity(float temperature, float pressure, float humidity);
	static void submitScdCO2AndTemperature(float co2, float temperature, float humidity);
};

#endif /* INC_SENSORSREADOUTS_HPP_ */
