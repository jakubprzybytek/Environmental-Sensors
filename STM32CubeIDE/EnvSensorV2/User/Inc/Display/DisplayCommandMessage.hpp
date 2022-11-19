#ifndef INC_SCREEN_DISPLAYCOMMANDMESSAGE_HPP_
#define INC_SCREEN_DISPLAYCOMMANDMESSAGE_HPP_

enum DisplayCommand {
	Clear, Flush
};

typedef struct DisplayCommandMessage {
	enum DisplayCommand command;
	uint8_t *frameBuffer;
} DisplayCommandMessage_t;

#endif /* INC_SCREEN_DISPLAYCOMMANDMESSAGE_HPP_ */
