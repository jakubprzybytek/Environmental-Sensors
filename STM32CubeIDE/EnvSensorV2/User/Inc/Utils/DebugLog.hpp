#ifndef INC_DEBUG_HPP_
#define INC_DEBUG_HPP_

class DebugLog {
public:
	static void init();
	static void log(char *messageBuffer);
	static bool isInitialized();

private:
	static bool initialized;

	static void startThread();
	static void thread(void *pvParameters);
};

#endif /* INC_DEBUG_HPP_ */
