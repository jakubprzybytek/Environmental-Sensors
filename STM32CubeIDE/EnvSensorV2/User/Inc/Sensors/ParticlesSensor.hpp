/*
 * ParticlesSensor.hpp
 *
 *  Created on: Jan 30, 2022
 *      Author: Chipotle
 */

#ifndef INC_SENSORS_PARTICLESSENSOR_HPP_
#define INC_SENSORS_PARTICLESSENSOR_HPP_

void ParticlesSensor_Init();

void hpma115c0ReadoutThread(void *pvParameters);

#endif /* INC_SENSORS_PARTICLESSENSOR_HPP_ */
