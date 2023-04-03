#include <Utils/DateTime.hpp>

class ReadoutsState {

public:
	float voltage;
//	DateTime dateTime;

	float bmpTemperature;
	float bmpPressure;

	float bmeTemperature;
	float bmePressure;
	float bmeHumidity;

	float scdCo2;
	float scdTemperature;
	float scdHumidity;

//	ReadoutsState() : dateTime(DateTime()) {
//	}
};
