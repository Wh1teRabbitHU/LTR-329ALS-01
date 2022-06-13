#include <Arduino.h>
#include "Wire.h"

#include "ltr_329.h"

#define I2C_SDA 21
#define I2C_SCL 22

static TwoWire wire = TwoWire(0);
static LTR_329_status status = { 0 };

void setup() {
  Serial.begin(9600);
  wire.begin((int)I2C_SDA, (int)I2C_SCL, (uint32_t)10000);

  LTR_329_init(&wire);
  LTR_329_setGain(&wire, LTR_329_GAIN_4X);
}

void loop() {
	LTR_329_readStatus(&wire, &status);

	Serial.print("Data is ");
	Serial.print(status.valid == LTR_329_DATA_VALID ? "valid" : "invalid");
	Serial.print(" and ");
	Serial.println(status.status == LTR_329_DATA_STATUS_NEW ? "new" : "old");
	Serial.print("Current gain: ");

	switch(status.gain) {
		case LTR_329_GAIN_1X:
			Serial.println("1X");
			break;
		case LTR_329_GAIN_2X:
			Serial.println("2X");
			break;
		case LTR_329_GAIN_4X:
			Serial.println("4X");
			break;
		case LTR_329_GAIN_8X:
			Serial.println("8X");
			break;
		case LTR_329_GAIN_48X:
			Serial.println("48X");
			break;
		case LTR_329_GAIN_96X:
			Serial.println("96X");
			break;
	}

	delay(10000);
}