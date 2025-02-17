#include <gui/fileviewer_screen/FileViewerView.hpp>
#include <gui/fileviewer_screen/FileViewerPresenter.hpp>

FileViewerPresenter::FileViewerPresenter(FileViewerView &v) :
		view(v) {
}

void FileViewerPresenter::activate() {
	view.setFileContent(model->getFileContent());
}

void FileViewerPresenter::deactivate() {
}

void FileViewerPresenter::notifyFileContentChanged(char *fileContent) {
	view.setFileContent(fileContent);
}
