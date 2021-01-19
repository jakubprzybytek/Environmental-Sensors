#ifndef FILEVIEWERVIEW_HPP
#define FILEVIEWERVIEW_HPP

#include <gui_generated/fileviewer_screen/FileViewerViewBase.hpp>
#include <gui/fileviewer_screen/FileViewerPresenter.hpp>

class FileViewerView: public FileViewerViewBase {
private:
	static const uint16_t TEXTAREA_SIZE = 400;
	touchgfx::Unicode::UnicodeChar fileContentBuffer[TEXTAREA_SIZE];

public:
	FileViewerView();
	virtual ~FileViewerView() {
	}
	virtual void setupScreen();
	virtual void tearDownScreen();

	void setFileContent(char *fileContent);

protected:
};

#endif // FILEVIEWERVIEW_HPP
