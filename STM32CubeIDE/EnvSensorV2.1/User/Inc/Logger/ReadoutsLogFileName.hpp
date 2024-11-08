/*
 * ReadoutsLogFileName.hpp
 *
 *  Created on: Nov 7, 2024
 *      Author: jakub
 */

#ifndef INC_LOGGER_READOUTSLOGFILENAME_HPP_
#define INC_LOGGER_READOUTSLOGFILENAME_HPP_

#include <Time/DateTime.hpp>

class ReadoutsLogFileName {

public:
	static void getLogFileName(char *buffer, const char *directory, DateTime dateTime);

	static bool isSameLogFile(DateTime first, DateTime second);
};

#endif /* INC_LOGGER_READOUTSLOGFILENAME_HPP_ */
