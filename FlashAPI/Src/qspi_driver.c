/*
 * qspi_driver.c
 *
 *  Created on: 7 Oct 2019
 *      Author: Arion
 */

#include "io_driver.h"





const struct Command DefaultCommand = {
	.qspi_command = {
		.InstructionMode = QSPI_INSTRUCTION_1_LINE,
		.AddressMode = QSPI_ADDRESS_NONE,
		.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE,
		.DataMode = QSPI_DATA_NONE,
		.DummyCycles = 0,
		.DdrMode = QSPI_DDR_MODE_DISABLE,
		.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY,
		.SIOOMode = QSPI_SIOO_INST_EVERY_CMD
	}
};



/*
 * The two following functions enable the programmer to build a QSPI command very easily.
 */
void with_address(Command* cmd, uint32_t address) {
	cmd->qspi_command.AddressMode = QSPI_ADDRESS_1_LINE;
	cmd->qspi_command.AddressSize = QSPI_ADDRESS_24_BITS;
	cmd->qspi_command.Address = address;
}

void with_data(Command* cmd, uint32_t length) {
	cmd->qspi_command.DataMode = QSPI_DATA_1_LINE;
	cmd->qspi_command.NbData = length;
}


/*
 * Higher-level abstraction layer for the QSPI interface.
 */
bool qspi_run(Command* cmd, uint32_t instruction) {
	cmd->qspi_command.Instruction = instruction;

	if(HAL_QSPI_Command(&hqspi, &(cmd->qspi_command), IO_TIMEOUT) != HAL_OK) {
		return false;
	} else {
		return true;
	}
}

bool qspi_poll(Command* cmd, uint32_t instruction, uint8_t bit, bool value) {
	QSPI_AutoPollingTypeDef poller;

	poller.MatchMode = QSPI_MATCH_MODE_AND;
	poller.StatusBytesSize = 1;
	poller.Interval = 0x10;
	poller.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;
	poller.Match = value << bit;
	poller.Mask = 1 << bit;

	if(HAL_QSPI_AutoPolling(&hqspi, &(cmd->qspi_command), &poller, IO_TIMEOUT) != HAL_OK) {
		return false;
	} else {
		return true;
	}
}

bool qspi_transmit(uint8_t* buffer) {
	if(HAL_QSPI_Transmit(&hqspi, buffer, IO_TIMEOUT) != HAL_OK) {
		return false;
	} else {
		return true;
	}
}

bool qspi_receive(uint8_t* buffer) {
	if(HAL_QSPI_Receive(&hqspi, buffer, IO_TIMEOUT) != HAL_OK) {
		return false;
	} else {
		return true;
	}
}
