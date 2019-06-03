/*
 * test_values.h
 *
 *  Created on: Sep 26, 2018
 *      Author: j_schauss18
 */

#ifndef TEST_VALUES_H_
#define TEST_VALUES_H_

#define TEST_1 1
#define TEST_2 2
#define TEST_3 3
#define TEST_4 4
#define TEST_5 5
#define TEST_6 6

#define TEST_CASE 6

#if (TEST_CASE == TEST_1)

const unsigned int CR 	= 0x00000000;
const unsigned int CHER = 0x00000007; // CH0, CH1, CH2 enabled
const unsigned int CHDR = 0x00000000; // no channel disabled
const unsigned int CGR1 = 0x00000001; // k_p = 1
const unsigned int CGR2 = 0x00000032; // k_i = 50
const unsigned int CGR3 = 0x00000020; // k_d = 2

#endif

#if (TEST_CASE == TEST_2)

const unsigned int CR 	= 0x00000000;
const unsigned int CHER = 0x00000003; // CH0, CH1 enabled
const unsigned int CHDR = 0x00000004; // CH2 disabled
const unsigned int CGR1 = 0x00000002; // k_p = 1
const unsigned int CGR2 = 0x00000014; // k_i = 20
const unsigned int CGR3 = 0x00000003; // k_d = 3

#endif

#if (TEST_CASE == TEST_3)

const unsigned int CR 	= 0x00000000;
const unsigned int CHER = 0x00000005; // CH0, CH2 enabled
const unsigned int CHDR = 0x00000002; // CH1 disabled
const unsigned int CGR1 = 0x00000005; // k_p = 5
const unsigned int CGR2 = 0x00000014; // k_i = 20
const unsigned int CGR3 = 0x00000010; // k_d = 16

#endif

#if (TEST_CASE == TEST_4)

const unsigned int CR 	= 0x00000000;
const unsigned int CHER = 0x00000001; // CH0 enabled
const unsigned int CHDR = 0x00000006; // CH1, CH2 disabled
const unsigned int CGR1 = 0x00000002; // k_p = 2
const unsigned int CGR2 = 0x00000014; // k_i = 20
const unsigned int CGR3 = 0x00000010; // k_d = 16

#endif

#if (TEST_CASE == TEST_5)

const unsigned int CR 	= 0x00000001; // Software Reset
const unsigned int CHER = 0x00000007; // CH0, CH1, CH2 enabled
const unsigned int CHDR = 0x00000000; // no channel disabled
const unsigned int CGR1 = 0x00000001; // k_p = 1
const unsigned int CGR2 = 0x00000032; // k_i = 50
const unsigned int CGR3 = 0x00000020; // k_d = 2

#endif

#if (TEST_CASE == TEST_6)

const unsigned int CR 	= 0x00000002; // Start configuration
const unsigned int CHER = 0x00000007; // CH0, CH1, CH2 enabled
const unsigned int CHDR = 0x00000000; // no channel disabled
const unsigned int CGR1 = 0x00000001; // k_p = 1
const unsigned int CGR2 = 0x00000032; // k_i = 50
const unsigned int CGR3 = 0x00000020; // k_d = 2

#endif

#endif /* TEST_VALUES_H_ */
