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

    virtual void notifySdChanged(bool sdActive, uint32_t availableSpaceKilobytes) {}

    virtual void notifyFileContentChanged(char *fileContent) {}

    virtual void notifyDateTimeChanged(DateTime dateTime) {}
    virtual void notifySettingsEditFieldChanged(SettingsEditField settingsEditField) {}

    virtual void notifyChartDataChanged(ChartData &chartData) {}

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
