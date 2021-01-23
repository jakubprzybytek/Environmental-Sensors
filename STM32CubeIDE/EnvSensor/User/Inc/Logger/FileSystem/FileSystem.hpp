/*
 * FileSystem.hpp
 *
 *  Created on: Jan 22, 2021
 *      Author: Chipotle
 */

#ifndef INC_LOGGER_FILESYSTEM_HPP_
#define INC_LOGGER_FILESYSTEM_HPP_

#include <Logger/FileSystem/FileAppender.hpp>

class FileSystem {

private:
	FRESULT ensureDirectory(const char *directoryPath);

public:
	FRESULT readAvailableSpace(uint32_t *availableSpaceKilobytes);

	FileAppender getFileAppender(const char *directory, const char *fileName);
};

#endif /* INC_LOGGER_FILESYSTEM_HPP_ */
