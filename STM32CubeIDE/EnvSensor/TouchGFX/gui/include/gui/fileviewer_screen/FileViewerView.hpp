#ifndef FILEVIEWERVIEW_HPP
#define FILEVIEWERVIEW_HPP

#include <gui_generated/fileviewer_screen/FileViewerViewBase.hpp>
#include <gui/fileviewer_screen/FileViewerPresenter.hpp>

class FileViewerView : public FileViewerViewBase
{
public:
    FileViewerView();
    virtual ~FileViewerView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // FILEVIEWERVIEW_HPP
