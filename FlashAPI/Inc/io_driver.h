/*
 * io_driver.h
 *
 *  Created on: 1 Oct 2019
 *      Author: Arion
 */

#ifndef IO_DRIVER_H_
#define IO_DRIVER_H_

#include <stdbool.h>

#include "quadspi.h"


QSPI_CommandTypeDef __craft_standard_command();
QSPI_AutoPollingTypeDef __craft_standard_poller();

void __check_status_bit(uint8_t bit, bool value);
void __write_enable_latch();
void __write_disable_latch();


void flash_init_driver();

#endif /* IO_DRIVER_H_ */
