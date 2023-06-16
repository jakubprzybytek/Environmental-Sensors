#ifndef INC_DEBUG_HPP_
#define INC_DEBUG_HPP_

#define DEBUG_LOG_MAX_LINE_LENGTH 21

class DebugLog {
public:
	static void init();
	static bool isInitialized();

	static void log(const char *message);
	static void log(const char *messagePrefix, uint32_t value);
	static void logWithStackHighWaterMark(const char *messagePrefix);

private:
	static bool initialized;
	static char messageBuffer[DEBUG_LOG_MAX_LINE_LENGTH + 1];

	static void startThread();
	static void thread(void *pvParameters);
};

#endif /* INC_DEBUG_HPP_ */
