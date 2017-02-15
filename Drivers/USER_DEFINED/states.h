/*
 * states.h
 *
 *  Created on: 08 nov 2016
 *      Author: mat25
 */

#ifndef STATES_H_
#define STATES_H_


/****
* Definition of the states of Morbo's FSM
****/

enum states {START_MCH, INIT, IDLE, COMPUTE, RESET_MCH, CHECK_AND_SEND, S_MAX};

/****
* Definition of the signals that commands transitions of the FSM
****/

enum events {NEW_DATA, DATA_READY, CHECK_DATA_OK, PERIPH_ALIVE, NOT_PERIPH_ALIVE, NOT_DATA_OK_ERR_COUNT_OK, E_MAX};

/*******
 * Definition of the guard signals for all the states
 ******/

enum guards{BUSY, NOT_BUSY, DATA_OK, NOT_DATA_OK, ERR_COUNT_OK, NOT_ERR_COUNT_OK};

#endif /* STATES_H_ */
