#include "ltr_329.h"

uint8_t getBit(uint8_t binary, uint8_t pos) {
	return ((binary >> pos) & 1) == 1 ? 1 : 0;
}

void LTR_329_init(TwoWire *wire) {
	uint8_t controlValue = 0;
	uint8_t retryCount = 0;

	while (retryCount++ < 500) {
		controlValue = LTR_329_readControl(wire);

		if (!getBit(controlValue, 1)) {
			break;
		}

		delay(1);
	}

	LTR_329_setDeviceMode(wire, LTR_329_ACTIVE_MODE);
}

uint8_t LTR_329_readControl(TwoWire *wire) {
	return I2C_8Bit_readFromModule(wire, LTR_329_I2C_ADDR, LTR_329_REG_CONTR_ADDR);
}

void LTR_329_writeControl(TwoWire *wire, uint8_t value) {
	I2C_8Bit_writeToModule(wire, LTR_329_I2C_ADDR, LTR_329_REG_CONTR_ADDR, value);
}

void LTR_329_setGain(TwoWire *wire, uint8_t gain) {
	uint8_t controlValue = LTR_329_readControl(wire);

	controlValue = I2C_8Bit_setBinary(controlValue, 2, GET_BIT_VALUE(gain, 0));
	controlValue = I2C_8Bit_setBinary(controlValue, 3, GET_BIT_VALUE(gain, 1));
	controlValue = I2C_8Bit_setBinary(controlValue, 4, GET_BIT_VALUE(gain, 2));

	LTR_329_writeControl(wire, controlValue);
}

void LTR_329_setDeviceMode(TwoWire *wire, uint8_t standby) {
	uint8_t controlValue = LTR_329_readControl(wire);

	controlValue = I2C_8Bit_setBinary(controlValue, 0, standby);

	LTR_329_writeControl(wire, controlValue);
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

void LTR_329_setIntegrationTime(TwoWire *wire, uint8_t time) {
	uint8_t rateValue = LTR_329_readMeasurementRate(wire);

	rateValue = I2C_8Bit_setBinary(rateValue, 3, GET_BIT_VALUE(time, 0));
	rateValue = I2C_8Bit_setBinary(rateValue, 4, GET_BIT_VALUE(time, 1));
	rateValue = I2C_8Bit_setBinary(rateValue, 5, GET_BIT_VALUE(time, 2));

	LTR_329_writeMeasurementRate(wire, rateValue);
}

void LTR_329_setMeasurementRate(TwoWire *wire, uint8_t rate) {
	uint8_t rateValue = LTR_329_readMeasurementRate(wire);

	rateValue = I2C_8Bit_setBinary(rateValue, 0, GET_BIT_VALUE(rate, 0));
	rateValue = I2C_8Bit_setBinary(rateValue, 1, GET_BIT_VALUE(rate, 1));
	rateValue = I2C_8Bit_setBinary(rateValue, 2, GET_BIT_VALUE(rate, 2));

	LTR_329_writeMeasurementRate(wire, rateValue);
}

/**
 * The order of the read, matters! The sensor will lock the registers until it reads the last address.
 * When the code reads 0x8B (LTR_329_REG_DATA_CH0_1_ADDR), the lock will be removed from the sensor!
 */
void LTR_329_readMeasurement(TwoWire *wire, LTR_329_measurement *measurement) {
	measurement->channel1 = LTR_329_readChannel1Data(wire);
	measurement->channel0 = LTR_329_readChannel0Data(wire);
}

void LTR_329_readStatus(TwoWire *wire, LTR_329_status *status) {
	uint8_t statusValue = I2C_8Bit_readFromModule(wire, LTR_329_I2C_ADDR, LTR_329_REG_STATUS_ADDR);
	uint8_t gain = GET_BIT_VALUE(statusValue, 4);

	gain = I2C_8Bit_setBinary(gain, 1, GET_BIT_VALUE(statusValue, 5));
	gain = I2C_8Bit_setBinary(gain, 2, GET_BIT_VALUE(statusValue, 6));

	status->valid = GET_BIT_VALUE(statusValue, 7);
	status->status = GET_BIT_VALUE(statusValue, 2);
	status->gain = gain;
}
