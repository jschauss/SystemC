/*
 * register_map.h
 *
 *  Created on: Sep 4, 2018
 *      Author: j_schauss18
 */

#ifndef REGISTER_MAP_H_
#define REGISTER_MAP_H_

#define PID_BASE_ADDRESS 	0x40038000

#define PID_CR 				PID_BASE_ADDRESS + 0x00
#define PID_CHER			PID_BASE_ADDRESS + 0x04
#define PID_CHDR			PID_BASE_ADDRESS + 0x14
#define PID_CHSR			PID_BASE_ADDRESS + 0x18
#define PID_CGR1			PID_BASE_ADDRESS + 0x48
#define PID_CGR2			PID_BASE_ADDRESS + 0x4C
#define PID_CGR3			PID_BASE_ADDRESS + 0x50

#endif /* REGISTER_MAP_H_ */
