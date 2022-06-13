# LTR-329ALS-01

- [LTR-329ALS-01](#ltr-329als-01)
	- [Description](#description)
	- [Minimal code](#minimal-code)
	- [Methods](#methods)
	- [Macros](#macros)
		- [Register addresses](#register-addresses)
		- [Measurement gain values](#measurement-gain-values)
		- [Sensor modes](#sensor-modes)
		- [Integration times](#integration-times)
		- [Measurement rates](#measurement-rates)
		- [Sensor statuses](#sensor-statuses)
		- [Data validity](#data-validity)

## Description

LTR-329ALS-01 is a low voltage, I2C digital light sensor and this library is an Arduino based driver for this device.  You can find the documentation [here](https://eu.mouser.com/datasheet/2/239/liteon_LTR-329ALS-01-1175539.pdf). When you design a circuit for this sensor, just like with any other I2C device, don't forget to put pull-up resistors on the two data line! (I2C SDA, SCL)

To start using the sensor, you have to switch it's state to active on power up. For that you can use the ```LTR_329_init();``` function in the library! Each method in this driver has an identical pair with an extra ```TwoWire``` parameter, in case you need to modify the I2C Wire instance. (for example if you need to change the default I2C pins, like in the ESP MCUs)

## Minimal code

The following code is a bare minimal setup to start reading your light measurements. (all configurations are kept on their default value)

```cpp
#include <Arduino.h>

#include "ltr_329.h"

static LTR_329_measurement measurement = { 0 };

void setup() {
  Serial.begin(9600);

  LTR_329_init();
}

void loop() {
  LTR_329_readMeasurement(&measurement);

  Serial.print("LTR-329 channel 0 data: ");
  Serial.println(measurement.channel0);
  Serial.print("LTR-329 channel 1 data: ");
  Serial.println(measurement.channel1);

  delay(1000);
}
```

As I mentioned in the intro, the ```LTR_329_init()``` function is necessary, because it waits for the end of the the turn on cycle and switches the corresponding flag in the registry to activate the module.

## Methods

- ```void LTR_329_init();```: This method waits until the sensor boots up and activates it
- ```uint8_t LTR_329_readControl();``` This method reads the control register and returns the raw content of it
- ```void LTR_329_writeControl(uint8_t value);```: This method writes directly to the control register and overwrites the flags in it. If you want to only manipulate certain parts of this register, just use the other methods.
- ```uint8_t LTR_329_readMeasurementRate();```: A method which reads the measurement rate register. This register contains two configuration segments: integration time and measurement rate.
- ```void LTR_329_writeMeasurementRate(uint8_t value);```: This method writes into the measurement rate register and overwrites both the integration time and measurement rate segments with the given value. To update these values separately, use the other two methods below (LTR_329_setIntegrationTime, LTR_329_setMeasurementRate)
- ```uint8_t LTR_329_readPartID();``` This reads a read only register, which stores the Part and revision ID.
- ```uint8_t LTR_329_readManufacturerID();``` This reads a read only register, which stores the manufacturer ID.
- ```uint16_t LTR_329_readChannel0Data();```
- ```uint16_t LTR_329_readChannel1Data();```
- ```void LTR_329_setGain(uint8_t gain);```
- ```void LTR_329_setDeviceMode(uint8_t standby);```
- ```void LTR_329_setIntegrationTime(uint8_t time);```
- ```void LTR_329_setMeasurementRate(uint8_t rate);```
- ```void LTR_329_readMeasurement(LTR_329_measurement *measurement);```
- ```void LTR_329_readStatus(LTR_329_status *status);```

## Macros

The followng macros are available to help interfacing the sensor more easily:

- LTR_329_I2C_ADDR

### Register addresses

- LTR_329_REG_CONTR_ADDR
- LTR_329_REG_MEAS_RATE_ADDR
- LTR_329_REG_PART_ID_ADDR
- LTR_329_REG_MANUFACTURER_ID_ADDR
- LTR_329_REG_DATA_CH1_0_ADDR
- LTR_329_REG_DATA_CH1_1_ADDR
- LTR_329_REG_DATA_CH0_0_ADDR
- LTR_329_REG_DATA_CH0_1_ADDR
- LTR_329_REG_STATUS_ADDR

### Measurement gain values

- LTR_329_GAIN_1X
- LTR_329_GAIN_2X
- LTR_329_GAIN_4X
- LTR_329_GAIN_8X
- LTR_329_GAIN_48X
- LTR_329_GAIN_96X

### Sensor modes

- LTR_329_STANDBY_MODE
- LTR_329_ACTIVE_MODE

### Integration times

- LTR_329_INTEGRATION_TIME_50MS
- LTR_329_INTEGRATION_TIME_100MS
- LTR_329_INTEGRATION_TIME_150MS
- LTR_329_INTEGRATION_TIME_200MS
- LTR_329_INTEGRATION_TIME_250MS
- LTR_329_INTEGRATION_TIME_300MS
- LTR_329_INTEGRATION_TIME_350MS
- LTR_329_INTEGRATION_TIME_400MS

### Measurement rates

- LTR_329_MEASUREMENT_RATE_50MS
- LTR_329_MEASUREMENT_RATE_100MS
- LTR_329_MEASUREMENT_RATE_200MS
- LTR_329_MEASUREMENT_RATE_500MS
- LTR_329_MEASUREMENT_RATE_1000MS
- LTR_329_MEASUREMENT_RATE_2000MS

### Sensor statuses

- LTR_329_DATA_STATUS_OLD
- LTR_329_DATA_STATUS_NEW

### Data validity

- LTR_329_DATA_VALID
- LTR_329_DATA_INVALID
