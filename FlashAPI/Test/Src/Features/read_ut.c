/*
 * read_ut.c
 *
 *  Created on: 7 Oct 2019
 *      Author: Arion
 */

#include "read_ut.h"
#include "flash.h"
#include "test_utils.h"


#define GENTLE_TEST_BUFFER_SIZE 4096

#define WRITE_ONCE_CRC_RESULT 0xa1765d5a


void __write_once() {
	uint8_t buffer[GENTLE_TEST_BUFFER_SIZE];

	for(uint32_t i = 0; i < GENTLE_TEST_BUFFER_SIZE; i++) {
		buffer[i] = random_byte();
	}

	uint32_t crc;

	crc32(buffer, GENTLE_TEST_BUFFER_SIZE, &crc);



	flash_erase_subsector(TEST_GENTLE_ADDR);
	//flash_write(TEST_GENTLE_ADDR, buffer, GENTLE_TEST_BUFFER_SIZE);
}

uint8_t test_read() {
	__write_once();

	uint8_t buffer[256];

	flash_read(TEST_GENTLE_ADDR, buffer, 256);

	return 0;
}
