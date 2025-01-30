/*
 * Settings.hpp
 *
 *  Created on: Oct 24, 2024
 *      Author: jakub
 */

#ifndef INC_UICONTROLLERS_CHARTS_HPP_
#define INC_UICONTROLLERS_CHARTS_HPP_

#include <UIControllers/UIController.hpp>
#include "cmsis_os.h"


class Charts: public virtual UIController {

private:
	void loadChartData();

	void toggleSensor();

	void toggleTimeSpan(bool ascending);

public:
	void onEnter();

	UIController* proceed();
};

#endif /* INC_UICONTROLLERS_CHARTS_HPP_ */
