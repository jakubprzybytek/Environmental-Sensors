#include <gui/fileviewer_screen/FileViewerView.hpp>

FileViewerView::FileViewerView() {
	fileContentTextArea.setWildcard(fileContentBuffer);
	fileContentTextArea.setWideTextAction(WideTextAction::WIDE_TEXT_CHARWRAP);
}

void FileViewerView::setupScreen() {
	FileViewerViewBase::setupScreen();
}

void FileViewerView::tearDownScreen() {
	FileViewerViewBase::tearDownScreen();
}

void FileViewerView::setFileContent(char *fileContent) {
	Unicode::fromUTF8((uint8_t*) fileContent, fileContentBuffer, TEXTAREA_SIZE);
	fileContentTextArea.invalidate();
}
