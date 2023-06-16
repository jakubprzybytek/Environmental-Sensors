#ifndef INC_ENVSENSORCOMMON_HPP_
#define INC_ENVSENSORCOMMON_HPP_

#include "EnvSensorV2.hpp"

extern osMutexId_t i2c1MutexHandle;

//#define I2C1_ACQUIRE osMutexAcquire(i2c1MutexHandle, portMAX_DELAY);
//#define I2C1_RELEASE osMutexRelease(i2c1MutexHandle);
#define I2C1_ACQUIRE
#define I2C1_RELEASE

#endif /* INC_ENVSENSORCOMMON_HPP_ */
