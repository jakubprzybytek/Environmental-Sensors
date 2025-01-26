#include <gui/containers/VoltageContainer.hpp>

VoltageContainer::VoltageContainer() {
}

void VoltageContainer::initialize() {
	VoltageContainerBase::initialize();
}

void VoltageContainer::setValue(float value) {
	Unicode::snprintfFloat(valueTextAreaBuffer, VALUETEXTAREA_SIZE, "%.2f", value);
	valueTextArea.invalidate();
}

void VoltageContainer::setBatteryLevel(BatteryLevel batteryLevel) {
	battLevel1Image.setVisible(batteryLevel == Level1);
	battLevel2Image.setVisible(batteryLevel == Level2);
	battLevel3Image.setVisible(batteryLevel == Level3);
	battLevel4Image.setVisible(batteryLevel == Level4);
	battLevel1Image.invalidate();
	battLevel2Image.invalidate();
	battLevel3Image.invalidate();
	battLevel4Image.invalidate();
}
