#ifndef BIGREADOUTCONTAINER_HPP
#define BIGREADOUTCONTAINER_HPP

#include <gui_generated/containers/BigReadoutContainerBase.hpp>

class BigReadoutContainer : public BigReadoutContainerBase
{
public:
    BigReadoutContainer();
    virtual ~BigReadoutContainer() {}

    virtual void initialize();
protected:
};

#endif // BIGREADOUTCONTAINER_HPP
