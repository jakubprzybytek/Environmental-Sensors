/*
 * AppState.hpp
 *
 *  Created on: Oct 26, 2024
 *      Author: jakub
 */

#ifndef INC_APPCONTROLLERS_APPSTATE_HPP_
#define INC_APPCONTROLLERS_APPSTATE_HPP_

#include <Time/DateTime.hpp>

typedef enum {
	None, Year, Month, Day, Hours, Minutes, Seconds
} SettingsField;

class AppState {
private:
	DateTime settingsDateTime;
	SettingsField settingsFieldUnderEdit;

	const char *button1Label;
	const char *button2Label;
	const char *button3Label;
	const char *button4Label;

public:
	AppState() :
			settingsDateTime(0, 0, 0, 0, 0, 0), settingsFieldUnderEdit(None), button1Label(NULL), button2Label(NULL), button3Label(NULL), button4Label(NULL) {
	}

	void setSettingsDateTime(DateTime &settingsDateTime) {
		this->settingsDateTime = settingsDateTime;
	}

	DateTime& getSettingsDateTime() {
		return settingsDateTime;
	}

	SettingsField getSettingsFieldUnderEdit() {
		return settingsFieldUnderEdit;
	}

	void setSettingsFieldUnderEdit(SettingsField settingsFieldUnderEdit) {
		this->settingsFieldUnderEdit = settingsFieldUnderEdit;
	}

	void setButtonLabels(const char *button1Label, const char *button2Label, const char *button3Label, const char *button4Label) {
		this->button1Label = button1Label;
		this->button2Label = button2Label;
		this->button3Label = button3Label;
		this->button4Label = button4Label;
	}

	const char* getButton1Label() const {
		return this->button1Label;
	}

	const char* getButton2Label() const {
		return this->button2Label;
	}

	const char* getButton3Label() const {
		return this->button3Label;
	}

	const char* getButton4Label() const {
		return this->button4Label;
	}

};

#endif /* INC_APPCONTROLLERS_APPSTATE_HPP_ */
