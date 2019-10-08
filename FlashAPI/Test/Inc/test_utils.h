/*
 * test_utils.h
 *
 *  Created on: 8 Oct 2019
 *      Author: Arion
 */

#ifndef TEST_UTILS_H_
#define TEST_UTILS_H_

#include <stdint.h>


void crc32(const void *data, uint32_t length, uint32_t* crc);
uint8_t random_byte();


#endif /* TEST_UTILS_H_ */
