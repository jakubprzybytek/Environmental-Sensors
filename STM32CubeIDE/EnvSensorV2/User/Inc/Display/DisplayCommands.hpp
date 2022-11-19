#ifndef INC_SCREEN_DISPLAYCOMMANDS_HPP_
#define INC_SCREEN_DISPLAYCOMMANDS_HPP_

#include <Display/DisplayCommandMessage.hpp>

class DisplayCommands {

public:
	static void submitDisplayClear();
	static void submitFlushFrameBuffer(uint8_t* frameBuffer);
};

#endif /* INC_SCREEN_DISPLAYCOMMANDS_HPP_ */
