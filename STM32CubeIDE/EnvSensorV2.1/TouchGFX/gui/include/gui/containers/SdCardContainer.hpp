#ifndef SDCARDCONTAINER_HPP
#define SDCARDCONTAINER_HPP

#include <gui_generated/containers/SdCardContainerBase.hpp>

class SdCardContainer: public SdCardContainerBase {
public:
	SdCardContainer();
	virtual ~SdCardContainer() {
	}

	virtual void initialize();

	void setValue(int16_t value);
protected:
};

#endif // SDCARDCONTAINER_HPP
