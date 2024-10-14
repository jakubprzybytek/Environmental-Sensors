/*
 * FileSystem.hpp
 *
 *  Created on: Jan 22, 2021
 *      Author: Chipotle
 */

#ifndef INC_LOGGER_FILESYSTEM_HPP_
#define INC_LOGGER_FILESYSTEM_HPP_

#include <Logger/FileSystem/FileAppender.hpp1>
#include <Logger/FileSystem/FileReader.hpp1>

class FileSystem {

private:
	static FRESULT ensureDirectory(const char *directoryPath);

public:
	static FRESULT format();

	static FRESULT readAvailableSpace(uint32_t *availableSpaceKilobytes);

	static FileAppender getFileAppender(const char *directory, const char *fileName);
	static FileReader getFileReader(const char *fileName);
};

#endif /* INC_LOGGER_FILESYSTEM_HPP_ */
