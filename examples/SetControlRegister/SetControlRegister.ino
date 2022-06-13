#include <Arduino.h>
#include "Wire.h"

#include "ltr_329.h"

#define I2C_SDA 21
#define I2C_SCL 22

static TwoWire wire = TwoWire(0);
static LTR_329_measurement measurement = { 0 };

void setup() {
  Serial.begin(9600);
  wire.begin((int)I2C_SDA, (int)I2C_SCL, (uint32_t)10000);

  LTR_329_init(&wire);

  LTR_329_setGain(&wire, LTR_329_GAIN_4X);
  LTR_329_setDeviceMode(&wire, LTR_329_ACTIVE_MODE);
  LTR_329_setIntegrationTime(&wire, LTR_329_INTEGRATION_TIME_100MS);
  LTR_329_setMeasurementRate(&wire, LTR_329_MEASUREMENT_RATE_100MS);
}

void loop() {
  LTR_329_readMeasurement(&wire, &measurement);

  Serial.print("LTR-329 channel 0 data: ");
  Serial.println(measurement.channel0);
  Serial.print("LTR-329 channel 1 data: ");
  Serial.println(measurement.channel1);

  delay(1000);
}