/*
 * EnvSensorConfig.hpp
 *
 *  Created on: Apr 23, 2023
 *      Author: jakub.przybytek
 */

#ifndef INC_TOUCH_GFX_HPP_
#define INC_TOUCH_GFX_HPP_

#include <touchgfx/hal/OSWrappers.hpp>
#include <gui/common/FrontendApplication.hpp>

using namespace touchgfx;
#define TRIGGER_TOUCHGFX_REFRESH() OSWrappers::signalVSync()

#define TOUCHGFX_GO_TO_READOUT_SCREEN() static_cast<FrontendApplication*>(Application::getInstance())->gotoMainReadoutsScreenNoTransition();
#define TOUCHGFX_GO_TO_SETTINGS() static_cast<FrontendApplication*>(Application::getInstance())->gotoSettingsScreenNoTransition();
#define TOUCHGFX_GO_TO_CHART() static_cast<FrontendApplication*>(Application::getInstance())->gotoChartScreenNoTransition();
#define TOUCHGFX_GO_TO_EMPTY_BATTERY() static_cast<FrontendApplication*>(Application::getInstance())->gotoEmptyBatteryScreenNoTransition();

#endif /* INC_TOUCH_GFX_HPP_ */
