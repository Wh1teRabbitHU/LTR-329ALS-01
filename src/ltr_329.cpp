#include "ltr_329.h"

uint8_t getBit(uint8_t binary, uint8_t pos) {
	return ((binary >> pos) & 1) == 1 ? 1 : 0;
}

void LTR_329_init(TwoWire *wire) {
	uint8_t retryCount = 0;

	while (retryCount++ < 500) {
		uint8_t controlValue = LTR_329_readControl(wire);

		if (!getBit(controlValue, 1)) {
			break;
		}

		delay(1);
	}

	LTR_329_writeControl(wire, 0b00011001);
}

uint8_t LTR_329_readControl(TwoWire *wire) {
	return I2C_8Bit_readFromModule(wire, LTR_329_I2C_ADDR, LTR_329_REG_CONTR_ADDR);
}

void LTR_329_writeControl(TwoWire *wire, uint8_t value) {
	I2C_8Bit_writeToModule(wire, LTR_329_I2C_ADDR, LTR_329_REG_CONTR_ADDR, value);
}

uint8_t LTR_329_readMeasurementRate(TwoWire *wire) {
	return I2C_8Bit_readFromModule(wire, LTR_329_I2C_ADDR, LTR_329_REG_MEAS_RATE_ADDR);
}

void LTR_329_writeMeasurementRate(TwoWire *wire, uint8_t value) {
	I2C_8Bit_writeToModule(wire, LTR_329_I2C_ADDR, LTR_329_REG_MEAS_RATE_ADDR, value);
}

uint8_t LTR_329_readPartID(TwoWire *wire) {
	return I2C_8Bit_readFromModule(wire, LTR_329_I2C_ADDR, LTR_329_REG_PART_ID_ADDR);
}

uint8_t LTR_329_readManufacturerID(TwoWire *wire) {
	return I2C_8Bit_readFromModule(wire, LTR_329_I2C_ADDR, LTR_329_REG_MANUFACTURER_ID_ADDR);
}

uint16_t LTR_329_readChannel0Data(TwoWire *wire) {
	uint16_t ch00Data = I2C_8Bit_readFromModule(wire, LTR_329_I2C_ADDR, LTR_329_REG_DATA_CH0_0_ADDR);
	uint16_t ch01Data = I2C_8Bit_readFromModule(wire, LTR_329_I2C_ADDR, LTR_329_REG_DATA_CH0_1_ADDR);

	return ch00Data + (ch01Data << 8);
}

uint16_t LTR_329_readChannel1Data(TwoWire *wire) {
	uint16_t ch10Data = I2C_8Bit_readFromModule(wire, LTR_329_I2C_ADDR, LTR_329_REG_DATA_CH1_0_ADDR);
	uint16_t ch11Data = I2C_8Bit_readFromModule(wire, LTR_329_I2C_ADDR, LTR_329_REG_DATA_CH1_1_ADDR);

	return ch10Data + (ch11Data << 8);
}

/**
 * The order of the read, matters! The sensor will lock the registers until it reads the last address.
 * When the code reads 0x8B (LTR_329_REG_DATA_CH0_1_ADDR), the lock will be removed from the sensor!
 */
void LTR_329_readMeasurement(TwoWire *wire, LTR_329_measurement *measurement) {
	measurement->channel1 = LTR_329_readChannel1Data(wire);
	measurement->channel0 = LTR_329_readChannel0Data(wire);
}

uint8_t LTR_329_readStatus(TwoWire *wire) {
	return I2C_8Bit_readFromModule(wire, LTR_329_I2C_ADDR, LTR_329_REG_STATUS_ADDR);
}
