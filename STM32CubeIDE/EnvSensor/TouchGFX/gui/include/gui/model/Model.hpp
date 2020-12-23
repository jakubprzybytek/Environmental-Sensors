#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model {
private:
	float co2;
	float preassure;
	float temperature;
	float humidity;

public:
	Model();

	void bind(ModelListener *listener) {
		modelListener = listener;
	}

	void tick();

	float getCo2() {
		return co2;
	}

	float getPreassure() {
		return preassure;
	}

	float getTemperature() {
		return temperature;
	}

	float getHumidity() {
		return humidity;
	}

protected:
	ModelListener *modelListener;
};

#endif // MODEL_HPP
