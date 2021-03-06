#ifndef BIGREADOUTCONTAINER_HPP
#define BIGREADOUTCONTAINER_HPP

#include <gui_generated/containers/BigReadoutContainerBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class BigReadoutContainer: public BigReadoutContainerBase {

private:
	static const uint8_t TEXTAREA_SIZE = 10;
	touchgfx::Unicode::UnicodeChar buffer[TEXTAREA_SIZE];

public:
	BigReadoutContainer();
	virtual ~BigReadoutContainer() {
	}

	virtual void initialize();

	void setUpLabels(TEXTS label, TEXTS unit);
	void setValue(float value);

protected:
};

#endif // BIGREADOUTCONTAINER_HPP
