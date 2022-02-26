#ifndef INC_ENVSENSORCOMMON_HPP_
#define INC_ENVSENSORCOMMON_HPP_

#include "EnvSensorV2.hpp"

extern osMutexId_t i2c1Mutex;

#define I2C1_ACQUIRE osMutexAcquire(i2c1Mutex, portMAX_DELAY);
#define I2C1_RELEASE osMutexRelease(i2c1Mutex);

#endif /* INC_ENVSENSORCOMMON_HPP_ */
