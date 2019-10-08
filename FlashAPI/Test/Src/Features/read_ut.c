/*
 * read_ut.c
 *
 *  Created on: 7 Oct 2019
 *      Author: Arion
 */

#include "read_ut.h"
#include "flash.h"

uint8_t test_read() {
	uint8_t buffer[256];

	flash_read(TEST_GENTLE_ADDR, buffer, 256);

	return 0;
}
