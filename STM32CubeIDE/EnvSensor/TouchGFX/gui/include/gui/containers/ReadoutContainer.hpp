#ifndef READOUTCONTAINER_HPP
#define READOUTCONTAINER_HPP

#include <gui_generated/containers/ReadoutContainerBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class ReadoutContainer: public ReadoutContainerBase {

private:
	static const uint8_t TEXTAREA_SIZE = 10;
	touchgfx::Unicode::UnicodeChar buffer[TEXTAREA_SIZE];

public:
	ReadoutContainer();
	virtual ~ReadoutContainer() {
	}

	virtual void initialize();

	void setUpLabels(TEXTS label, TEXTS unit);
	void setValue(float value);
protected:
};

#endif // READOUTCONTAINER_HPP
