/*
 * ScreenProcessor.hpp
 *
 *  Created on: Jan 18, 2021
 *      Author: Chipotle
 */

#ifndef INC_SCREEN_SCREEN_HPP_
#define INC_SCREEN_SCREEN_HPP_

class BaseScreen {

public:

	void requestDisplayRefresh();
	void signalRenderingDone();

	virtual void processFirstSwitchPressed() {}

	virtual void processSecondSwitchPressed() {}

	virtual void processThirdSwitchPressed() {}

	virtual void processFourthSwitchPressed() {}
};

#endif /* INC_SCREEN_SCREEN_HPP_ */
