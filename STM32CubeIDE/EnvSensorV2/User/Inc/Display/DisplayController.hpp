#ifndef INC_SCREEN_DISPLAYCONTROLLER_HPP_
#define INC_SCREEN_DISPLAY_HPP_

class DisplayController {

public:
	static void init();
	static void displayReadyInterrupHandler();

private:
	static void startThread();

	static void thread(void *pvParameters);
};

#endif /* INC_SCREEN_DISPLAYCONTROLLER_HPP_ */
