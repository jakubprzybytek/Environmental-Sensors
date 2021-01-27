/*
 * EnvStateCsvFormat.hpp
 *
 *  Created on: Jan 27, 2021
 *      Author: Chipotle
 */

#ifndef INC_LOGGER_ENVSTATECSVFORMAT_HPP_
#define INC_LOGGER_ENVSTATECSVFORMAT_HPP_

#include <EnvState.hpp>

class EnvStateCsvFormat {

public:
	static void toCsv(char * lineBuffer, DateTime &dateTime, EnvState &envState);

};

#endif /* INC_LOGGER_ENVSTATECSVFORMAT_HPP_ */
