#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

#ifndef SIMULATOR
#include <Time/DateTime.hpp>
#endif

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    virtual void notifyBottomButtonLabelsChanged(const char *button1Label, const char *button2Label, const char *button3Label, const char *button4Label) {}

    virtual void notifyVoltageChanged(float newVoltage) {}

    virtual void notifyTemperatureChanged(float newTemperature) {}
    virtual void notifyPressureChanged(float newPressure) {}
    virtual void notifyCO2Changed(float newCo2) {}
    virtual void notifyHumidityChanged(float newHumidity) {}
    virtual void notifyParticlesChanged(uint16_t pm1, uint16_t pm2_5, uint16_t pm4, uint16_t pm10) {}

#ifndef SIMULATOR
    virtual void notifyDateTimeChanged(DateTime newDateTime) {}
#endif

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
