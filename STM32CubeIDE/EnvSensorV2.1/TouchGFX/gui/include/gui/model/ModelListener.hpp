#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

#include <gui/common/FrontendApplication.hpp>

#ifndef SIMULATOR

#include <AppControllers/AppState.hpp>
#include <Readouts/DataSeries/ChartData.hpp>
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

    virtual void notifyBottomButtonLabelsChanged(const char *newButton1Label, const char *newButton2Label, const char *newButton3Label, const char *newButton4Label) {}
    virtual void notifyLedLabelsChanged(const char *newLed1Label, const char *newLed2Label, const char *newLed3Label, const char *newLed4Label) {}

    virtual void notifyVoltageChanged(float newVoltage) {}
    virtual void notifySdAvailableSpaceChanged(int16_t sdAvailableSpace) {}

    virtual void notifyTemperatureChanged(float newTemperature) {}
    virtual void notifyPressureChanged(float newPressure) {}
    virtual void notifyCO2Changed(float newCo2) {}
    virtual void notifyHumidityChanged(float newHumidity) {}
    virtual void notifyParticlesChanged(uint16_t pm1, uint16_t pm2_5, uint16_t pm4, uint16_t pm10) {}

#ifndef SIMULATOR
    virtual void notifyDateTimeChanged(DateTime newDateTime) {}
    virtual void notifySettingsDateTimeChanged(DateTime settingsDateTime) {}
    virtual void notifySettingsFieldUnderTest(SettingsField fieldUnderTest) {}
#endif

    virtual void notifyChartDataChanged(ChartData &chartData, SensorName chartSensor, TimeSpan barTimeSpan) {}

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
