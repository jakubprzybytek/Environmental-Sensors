#include <gui/containers/ParticlesContainer.hpp>

ParticlesContainer::ParticlesContainer()
{

}

void ParticlesContainer::initialize()
{
    ParticlesContainerBase::initialize();
}

void ParticlesContainer::setValues(uint16_t pm1, uint16_t pm2_5, uint16_t pm4, uint16_t pm10) {
	Unicode::snprintf(pm1ValueTextAreaBuffer, PM1VALUETEXTAREA_SIZE, "%u", pm1);
	Unicode::snprintf(pm2_5ValueTextAreaBuffer, PM2_5VALUETEXTAREA_SIZE, "%u", pm2_5);
	Unicode::snprintf(pm4ValueTextAreaBuffer, PM4VALUETEXTAREA_SIZE, "%u", pm4);
	Unicode::snprintf(pm10ValueTextAreaBuffer, PM10VALUETEXTAREA_SIZE, "%u", pm10);
	pm1ValueTextArea.invalidate();
	pm2_5ValueTextArea.invalidate();
	pm4ValueTextArea.invalidate();
	pm10ValueTextArea.invalidate();
}
