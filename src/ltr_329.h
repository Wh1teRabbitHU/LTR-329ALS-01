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

typedef struct LTR_329_measurement {
	uint16_t channel0;
	uint16_t channel1;
} LTR_329_measurement;

void LTR_329_init(TwoWire *wire);

uint8_t LTR_329_readControl(TwoWire *wire);
void LTR_329_writeControl(TwoWire *wire, uint8_t value);
uint8_t LTR_329_readMeasurementRate(TwoWire *wire);
void LTR_329_writeMeasurementRate(TwoWire *wire, uint8_t value);
uint8_t LTR_329_readPartID(TwoWire *wire);
uint8_t LTR_329_readManufacturerID(TwoWire *wire);
uint16_t LTR_329_readChannel0Data(TwoWire *wire);
uint16_t LTR_329_readChannel1Data(TwoWire *wire);
void LTR_329_readMeasurement(TwoWire *wire, LTR_329_measurement *measurement);
uint8_t LTR_329_readStatus(TwoWire *wire);

#endif /* SRC_LTR_329_H_ */
