/*
 * SdCardInitTask.hpp
 *
 *  Created on: Oct 13, 2024
 *      Author: jakub
 */

#ifndef INC_LOGGER_THREAD_HPP_
#define INC_LOGGER_THREAD_HPP_

class LoggerThread {

public:
	static void init();

private:
	static void startThread();
	static void thread(void *pvParameters);
};

#endif /* INC_LOGGER_SDCARDINSPECTOR_HPP_ */