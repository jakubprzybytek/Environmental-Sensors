/*
 * FileName.hpp
 *
 *  Created on: Jan 22, 2021
 *      Author: Chipotle
 */

#ifndef INC_LOGGER_LOGFILENAME_HPP_
#define INC_LOGGER_LOGFILENAME_HPP_

#include <EnvState.hpp>

class LogFileName {

public:
	static void getDirectory(char *buffer, DateTime dateTime);
	static void getFileName(char *buffer, DateTime dateTime);
};

#endif /* INC_LOGGER_LOGFILENAME_HPP_ */
