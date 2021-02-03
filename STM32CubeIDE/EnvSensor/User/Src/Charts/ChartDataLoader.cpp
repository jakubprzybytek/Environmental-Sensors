#include <Charts/ChartDataLoader.hpp>

#include <string.h>

#include <Logger/FileSystem/FileSystem.hpp>
#include <Logger/LogFileName.hpp>
#include <Logger/LogReader.hpp>

bool ChartDataLoader::load() {
	DateTime from = DateTime(21, 1, 1, 0, 2, 0);
	DateTime to = DateTime(21, 1, 1, 0, 4, 0);

	char fileName[30];
	LogFileName::getFileName(fileName, from);

	FileReader fileReader = FileSystem::getFileReader(fileName);
	BufferedReader linesReader = BufferedReader(fileReader);
	LogReader logReader = LogReader(linesReader);

	if (!linesReader.open()) {
		return false;
	}

	if (!logReader.skipTo(from)) {
		return false;
	}

	DateTime timestamp;
	EnvState envState;

	if (!logReader.readEntry(timestamp, envState)) {
		return false;
	}

	if (!logReader.close()) {
		return false;
	}

	return true;
}
