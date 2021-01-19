#ifndef FILEVIEWERPRESENTER_HPP
#define FILEVIEWERPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class FileViewerView;

class FileViewerPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    FileViewerPresenter(FileViewerView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~FileViewerPresenter() {};

    void notifyFileContentChanged(char *fileContent);

private:
    FileViewerPresenter();

    FileViewerView& view;
};

#endif // FILEVIEWERPRESENTER_HPP
