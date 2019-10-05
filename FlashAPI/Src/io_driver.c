/*
 * io_driver.c
 *
 *  Created on: 1 Oct 2019
 *      Author: Arion
 */

#include "io_driver.h"
#include "quadspi.h"
#include "flash_state.h"
#include "MT25QL128ABA.h"


QSPI_CommandTypeDef __craft_standard_command() {
	QSPI_CommandTypeDef command;

	command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	command.AddressMode = QSPI_ADDRESS_NONE;
	command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	command.DataMode = QSPI_DATA_NONE;
	command.DummyCycles = 0;
	command.DdrMode = QSPI_DDR_MODE_DISABLE;
	command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  	command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	return command;
}

QSPI_AutoPollingTypeDef __craft_standard_poller() {
	QSPI_AutoPollingTypeDef poller;

	poller.MatchMode = QSPI_MATCH_MODE_AND;
	poller.StatusBytesSize = 1;
	poller.Interval = 0x10;
	poller.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

	return poller;
}


void __check_status_bit(uint8_t bit, bool value) {
	QSPI_CommandTypeDef command = __craft_standard_command();
	QSPI_AutoPollingTypeDef polling = __craft_standard_poller();

	polling.Match = value << bit;
	polling.Mask = 1 << bit;

	command.Instruction = READ_STATUS_REGISTER;
	command.DataMode = QSPI_DATA_1_LINE;

	if(HAL_QSPI_AutoPolling(&hqspi, &command, &polling, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		flash_fatal(0b1010);
	}
}

void __write_enable_latch() {
	QSPI_CommandTypeDef command = __craft_standard_command();

	command.Instruction = WRITE_ENABLE_LATCH;

	if(HAL_QSPI_Command(&hqspi, &command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		flash_fatal(0b10);
	}

	__check_status_bit(1, true);
}

void __write_disable_latch() {
	QSPI_CommandTypeDef command = __craft_standard_command();

	command.Instruction = WRITE_DISABLE_LATCH;

	if(HAL_QSPI_Command(&hqspi, &command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
		flash_fatal(0b10);
	}
}

void flash_erase_sector(uint8_t address) {
	__write_enable_latch(&hqspi);

	QSPI_CommandTypeDef command = __craft_standard_command();

	command.Instruction = SECTOR_ERASE;
	command.Address = address;

	if(HAL_QSPI_Command_IT(&hqspi, &command) != HAL_OK) {
		flash_fatal(0b10101010);
	}
}

void flash_init_driver() {
	__write_enable_latch(&hqspi);
	__write_disable_latch(&hqspi);


	flash_success();

}
