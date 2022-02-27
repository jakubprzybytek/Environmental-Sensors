#ifndef TEMPERATURECONTAINER_HPP
#define TEMPERATURECONTAINER_HPP

#include <gui_generated/containers/TemperatureContainerBase.hpp>

class TemperatureContainer : public TemperatureContainerBase
{
public:
    TemperatureContainer();
    virtual ~TemperatureContainer() {}

    virtual void initialize();
protected:
};

#endif // TEMPERATURECONTAINER_HPP
