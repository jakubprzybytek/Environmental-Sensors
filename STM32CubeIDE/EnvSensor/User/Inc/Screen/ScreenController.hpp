/*
 * ScreenProcessor.hpp
 *
 *  Created on: Jan 18, 2021
 *      Author: Chipotle
 */

#ifndef INC_SCREEN_SCREENCONTROLLER_HPP_
#define INC_SCREEN_SCREENCONTROLLER_HPP_

class ScreenController {

public:
	virtual void processFirstSwitchPressed() {}

	virtual void processSecondSwitchPressed() {}

	virtual void processThirdSwitchPressed() {}

	virtual void processFourthSwitchPressed() {}

};


#endif /* INC_SCREEN_SCREENCONTROLLER_HPP_ */
