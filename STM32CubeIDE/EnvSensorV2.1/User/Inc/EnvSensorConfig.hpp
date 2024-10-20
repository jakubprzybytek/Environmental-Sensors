/*
 * EnvSensorConfig.hpp
 *
 *  Created on: Apr 23, 2023
 *      Author: jakub.przybytek
 */

#ifndef INC_ENVSENSORCONFIG_HPP_
#define INC_ENVSENSORCONFIG_HPP_

#include <main.h>

//#define DEBUG_LOG_TRACE

#define DISPLAY_CONTROLLER_INFO
//#define DISPLAY_CONTROLLER_TRACE

#define PRESSURE_SENSOR_INFO
//#define PRESSURE_SENSOR_TRACE

#define CO2_SENSOR_INFO
//#define CO2_SENSOR_TRACE

#define PARTICLES_SENSOR_INFO
//#define PARTICLES_SENSOR_TRACE

#define VOLTAGE_SENSOR_INFO
//#define VOLTAGE_SENSOR_TRACE

#define LOGGER_INFO
#define LOGGER_TRACE

#define POWER_5V_ENABLE() HAL_GPIO_WritePin(POWER_5V_ENABLE_GPIO_Port, POWER_5V_ENABLE_Pin, GPIO_PIN_SET)
#define POWER_5V_DISABLE() HAL_GPIO_WritePin(POWER_5V_ENABLE_GPIO_Port, POWER_5V_ENABLE_Pin, GPIO_PIN_RESET)

#include <touchgfx/hal/OSWrappers.hpp>
using namespace touchgfx;
#define TRIGGER_TOUCHGFX_REFRESH() OSWrappers::signalVSync()

#endif /* INC_ENVSENSORCONFIG_HPP_ */
