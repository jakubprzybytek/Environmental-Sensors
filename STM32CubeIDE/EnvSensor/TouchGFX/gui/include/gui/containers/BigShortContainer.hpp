#ifndef BIGSHORTCONTAINER_HPP
#define BIGSHORTCONTAINER_HPP

#include <gui_generated/containers/BigShortContainerBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class BigShortContainer: public BigShortContainerBase {

private:
	static const uint8_t TEXTAREA_SIZE = 10;
	touchgfx::Unicode::UnicodeChar buffer[TEXTAREA_SIZE];

public:
	BigShortContainer();
	virtual ~BigShortContainer() {
	}

	virtual void initialize();

	void setUpLabels(TEXTS label, TEXTS unit);
	void setValue(float value);

protected:
};

#endif // BIGSHORTCONTAINER_HPP
