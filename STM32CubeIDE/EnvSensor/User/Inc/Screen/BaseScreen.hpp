/*
 * ScreenProcessor.hpp
 *
 *  Created on: Jan 18, 2021
 *      Author: Chipotle
 */

#ifndef INC_SCREEN_BASESCREEN_HPP_
#define INC_SCREEN_BASESCREEN_HPP_

class BaseScreen {

public:

	void requestDisplayRefresh();
	void signalRenderingDone();

	void switchTo(BaseScreen *newScreen);

	virtual void handleScreenEnter() {}

	virtual void handleFirstSwitchPressed() {}

	virtual void handleSecondSwitchPressed() {}

	virtual void handleThirdSwitchPressed() {}

	virtual void handleFourthSwitchPressed() {}
};

#endif /* INC_SCREEN_BASESCREEN_HPP_ */
