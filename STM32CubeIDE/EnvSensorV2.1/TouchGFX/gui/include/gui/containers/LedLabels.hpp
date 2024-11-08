#ifndef LEDLABELS_HPP
#define LEDLABELS_HPP

#include <gui_generated/containers/LedLabelsBase.hpp>

class LedLabels : public LedLabelsBase
{
public:
    LedLabels();
    virtual ~LedLabels() {}

    virtual void initialize();

    void setLabels(const char *led1Label, const char *led2Label, const char *led3Label, const char *led4Label);
protected:
};

#endif // LEDLABELS_HPP
