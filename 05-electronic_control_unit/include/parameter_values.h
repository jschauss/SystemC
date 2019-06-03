/*
 * paramter_values.h
 *
 *  Created on: Sep 1, 2018
 *      Author: j_schauss18
 */

#ifndef SRC_PARAMETER_VALUES_H_
#define SRC_PARAMETER_VALUES_H_

// Time step
const sca_core::sca_time T_STEP 	= 	sca_core::sca_time(0.01, sc_core::SC_MS);

// PWM modulator
const sca_core::sca_time T_PERIOD	= 	sca_core::sca_time(5.0,sc_core::SC_MS);
const sca_core::sca_time T_RAMP 	= 	sca_core::sca_time(0.05, sc_core::SC_MS);

// PID controller
//const unsigned int K_P = 0;
//const unsigned int K_I = 12;
//const unsigned int K_D = 2;

// DC Motor
const double H_0 = 15.0;
const double W_0 = 20 * M_PI;

#endif /* SRC_PARAMTER_VALUES_H_ */
