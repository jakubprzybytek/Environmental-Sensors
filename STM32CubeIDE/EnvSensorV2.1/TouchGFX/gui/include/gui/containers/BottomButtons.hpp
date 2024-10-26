#ifndef BOTTOMBUTTONS_HPP
#define BOTTOMBUTTONS_HPP

#include <gui_generated/containers/BottomButtonsBase.hpp>

class BottomButtons : public BottomButtonsBase
{
public:
    BottomButtons();
    virtual ~BottomButtons() {}

    virtual void initialize();

    void setLabels(const char *button1Label, const char *button2Label, const char *button3Label, const char *button4Label);
protected:
};

#endif // BOTTOMBUTTONS_HPP
