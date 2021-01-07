#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    virtual void notifyCo2Changed(float co2) {}
    virtual void notifyPreassureChanged(float preassure) {}
    virtual void notifyTemperatureChanged(float temperature) {}
    virtual void notifyHumidityChanged(float humidity) {}

    virtual void notifyVddChanged(float vdd) {}

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
