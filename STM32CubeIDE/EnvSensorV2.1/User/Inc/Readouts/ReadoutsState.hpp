#ifndef INC_READOUTS_STATE_HPP_
#define INC_READOUTS_STATE_HPP_

class ReadoutsState {

public:
	float voltage;

	float bmpTemperature;
	float bmpPressure;

	float bmeTemperature;
	float bmePressure;
	float bmeHumidity;

	float scdCo2;
	float scdTemperature;
	float scdHumidity;

	uint16_t pm1;
	uint16_t pm2_5;
	uint16_t pm4;
	uint16_t pm10;

};

#endif
