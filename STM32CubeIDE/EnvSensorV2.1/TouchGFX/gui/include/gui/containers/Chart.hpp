#ifndef CHART_HPP
#define CHART_HPP

#include <gui_generated/containers/ChartBase.hpp>

class Chart : public ChartBase
{
public:
    Chart();
    virtual ~Chart() {}

    virtual void initialize();
protected:
};

#endif // CHART_HPP
