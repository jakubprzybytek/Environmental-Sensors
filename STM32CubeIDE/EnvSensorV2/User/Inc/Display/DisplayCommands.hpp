#ifndef INC_SCREEN_DISPLAYCOMMANDS_HPP_
#define INC_SCREEN_DISPLAYCOMMANDS_HPP_

enum DisplayCommand {
	Clear
};

typedef struct DisplayCommandMessage {
	enum DisplayCommand command;
} DisplayCommandMessage_t;

class DisplayCommands {

public:
	static void submitDisplayClear();
};

#endif /* INC_SCREEN_DISPLAYCOMMANDS_HPP_ */
