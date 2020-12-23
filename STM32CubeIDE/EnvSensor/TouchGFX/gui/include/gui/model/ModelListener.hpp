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

    virtual void notifyPreassureChanged(uint32_t preassure) {}
    virtual void notifyTemperatureChanged(int16_t temperature) {}

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
