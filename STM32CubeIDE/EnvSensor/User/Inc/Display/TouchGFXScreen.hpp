/*
 * TouchGFXScreen.hpp
 *
 *  Created on: Jan 16, 2021
 *      Author: Chipotle
 */

#ifndef INC_DISPLAY_TOUCHGFXSCREEN_HPP_
#define INC_DISPLAY_TOUCHGFXSCREEN_HPP_

class TouchGFXScreen {
public:
	void gotoMainScreen();
	void gotoFileViewerScreen();

	void refreshScreen();
	void signalRenderingDone();
};

#endif /* INC_DISPLAY_TOUCHGFXSCREEN_HPP_ */