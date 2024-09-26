#ifndef PARTICLESCONTAINER_HPP
#define PARTICLESCONTAINER_HPP

#include <gui_generated/containers/ParticlesContainerBase.hpp>

class ParticlesContainer : public ParticlesContainerBase
{
public:
    ParticlesContainer();
    virtual ~ParticlesContainer() {}

    virtual void initialize();

	void setValues(uint16_t pm1, uint16_t pm2_5, uint16_t pm4, uint16_t pm10);
protected:
};

#endif // PARTICLESCONTAINER_HPP
