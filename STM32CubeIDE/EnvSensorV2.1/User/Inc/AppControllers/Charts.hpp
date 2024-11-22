/*
 * Settings.hpp
 *
 *  Created on: Oct 24, 2024
 *      Author: jakub
 */

#ifndef INC_APPCONTROLLERS_CHARTS_HPP_
#define INC_APPCONTROLLERS_CHARTS_HPP_

#include "cmsis_os.h"

#include <AppControllers/Controller.hpp>

class Charts: public virtual Controller {

private:
	void loadChartData();

	void toggleSensor();

	void toggleTimeSpan(bool ascending);

public:
	void onEnter();

	Controller* proceed();
};

#endif /* INC_APPCONTROLLERS_CHARTS_HPP_ */
