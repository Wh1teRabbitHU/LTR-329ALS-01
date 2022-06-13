#ifndef SRC_LTR_329_H_
#define SRC_LTR_329_H_

#include "I2C_8Bit.h"
#include "stdint.h"

#define LTR_329_I2C_ADDR						0x29

#define LTR_329_REG_CONTR_ADDR					0x80
#define LTR_329_REG_MEAS_RATE_ADDR				0x85
#define LTR_329_REG_PART_ID_ADDR				0x86
#define LTR_329_REG_MANUFACTURER_ID_ADDR		0x87
#define LTR_329_REG_DATA_CH1_0_ADDR				0x88
#define LTR_329_REG_DATA_CH1_1_ADDR				0x89
#define LTR_329_REG_DATA_CH0_0_ADDR				0x8A
#define LTR_329_REG_DATA_CH0_1_ADDR				0x8B
#define LTR_329_REG_STATUS_ADDR					0x8C

#define LTR_329_GAIN_1X							0b000
#define LTR_329_GAIN_2X							0b001
#define LTR_329_GAIN_4X							0b010
#define LTR_329_GAIN_8X							0b011
#define LTR_329_GAIN_48X						0b110
#define LTR_329_GAIN_96X						0b111

#define LTR_329_STANDBY_MODE					0b10
#define LTR_329_ACTIVE_MODE						0b1

#define LTR_329_INTEGRATION_TIME_50MS			0b001
#define LTR_329_INTEGRATION_TIME_100MS			0b000
#define LTR_329_INTEGRATION_TIME_150MS			0b100
#define LTR_329_INTEGRATION_TIME_200MS			0b010
#define LTR_329_INTEGRATION_TIME_250MS			0b101
#define LTR_329_INTEGRATION_TIME_300MS			0b110
#define LTR_329_INTEGRATION_TIME_350MS			0b111
#define LTR_329_INTEGRATION_TIME_400MS			0b011

#define LTR_329_MEASUREMENT_RATE_50MS			0b000
#define LTR_329_MEASUREMENT_RATE_100MS			0b001
#define LTR_329_MEASUREMENT_RATE_200MS			0b010
#define LTR_329_MEASUREMENT_RATE_500MS			0b011
#define LTR_329_MEASUREMENT_RATE_1000MS			0b100
#define LTR_329_MEASUREMENT_RATE_2000MS			0b101

typedef struct LTR_329_measurement {
	uint16_t channel0;
	uint16_t channel1;
} LTR_329_measurement;

typedef struct LTR_329_status {
	uint8_t status;
	uint8_t valid;
	uint8_t gain;
} LTR_329_status;

void LTR_329_init(TwoWire *wire);

uint8_t LTR_329_readControl(TwoWire *wire);
void LTR_329_writeControl(TwoWire *wire, uint8_t value);
uint8_t LTR_329_readMeasurementRate(TwoWire *wire);
void LTR_329_writeMeasurementRate(TwoWire *wire, uint8_t value);
uint8_t LTR_329_readPartID(TwoWire *wire);
uint8_t LTR_329_readManufacturerID(TwoWire *wire);
uint16_t LTR_329_readChannel0Data(TwoWire *wire);
uint16_t LTR_329_readChannel1Data(TwoWire *wire);
void LTR_329_readStatus(TwoWire *wire, LTR_329_status *status);

void LTR_329_setGain(TwoWire *wire, uint8_t gain);
void LTR_329_setDeviceMode(TwoWire *wire, uint8_t standby);
void LTR_329_setIntegrationTime(TwoWire *wire, uint8_t time);
void LTR_329_setMeasurementRate(TwoWire *wire, uint8_t rate);
void LTR_329_readMeasurement(TwoWire *wire, LTR_329_measurement *measurement);

#endif /* SRC_LTR_329_H_ */
