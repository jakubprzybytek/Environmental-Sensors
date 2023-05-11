#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

#include <Utils/DateTime.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    virtual void notifyVoltageChanged(float newVoltage) {}

    virtual void notifyTemperatureChanged(float newTemperature) {}
    virtual void notifyPressureChanged(float newPressure) {}
    virtual void notifyCO2Changed(float newCo2) {}
    virtual void notifyHumidityChanged(float newHumidity) {}
    virtual void notifyParticlesChanged(uint16_t pm1, uint16_t pm2_5, uint16_t pm4, uint16_t pm10) {}

    virtual void notifyDateTimeChanged(DateTime newDateTime) {}

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
