/*
 * unit_tests.c
 *
 *  Created on: 1 Oct 2019
 *      Author: Arion
 */


#include "flash_tests.h"
#include "read_ut.h"

test_result test_features(uint8_t features) {
	test_result result;

	result.status = TEST_RUNNING;
	result.score = 0;

	if(features & FEATURE_READ) {
		if(test_read()) {
			result.score |= FEATURE_READ;
		}
	}

	result.status = TEST_FINISHED;

	return result;
}

uint8_t is_test_result_satisfying(test_result result, uint64_t standard) {
	return (result.score & standard) == standard;
}
