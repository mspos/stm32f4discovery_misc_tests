/*
 * functions.h
 *
 *  Created on: 08 nov 2016
 *      Author: mat25
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_


/**********
 * INCLUDES
 *********/

#include "states.h"

#include "stdint.h"
/******
 * TYPEDEFS
 ******/

typedef void (* const voidFunc)(void);
typedef enum { FALSE, TRUE } bool;

/********
 * VARIABLES
 ********/

uint8_t MAX_ERRORS; //inizializzato in Instate di INIT
uint8_t ERR_COUNT;		//inizializzato in Instate di INIT

voidFunc Morbo_Upon_Enter[S_MAX];
voidFunc Morbo_Action_While_In_State[S_MAX];
voidFunc Morbo_Upon_Exit[S_MAX];



/******
* PROTOTYPES
******/
enum states StateMachine(enum events event, enum guards guard, enum states Current_State);
//enum states StateMachine(enum events event, enum states Current_State);

void State_Enter_START(void); void State_InState_START(void); void State_Exit_START(void);
void State_Enter_INIT(void);   void State_Enter_IDLE(void);   void State_Enter_COMPUTE(void);
void State_InState_INIT(void); void State_InState_IDLE(void); void State_InState_COMPUTE(void);
void State_Exit_INIT(void);    void State_Exit_IDLE(void);    void State_Exit_COMPUTE(void);

void State_Enter_RESET(void);   void State_Enter_CHECK_AND_SEND_DATA(void);
void State_InState_RESET(void); void State_InState_CHECK_AND_SEND_DATA(void);
void State_Exit_RESET(void);    void State_Exit_CHECK_AND_SEND_DATA(void);

enum guards Check_Errors(void);



#endif /* FUNCTIONS_H_ */


