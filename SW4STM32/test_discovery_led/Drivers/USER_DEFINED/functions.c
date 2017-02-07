/*

 * functions.c
 *
 *  Created on: 08 nov 2016
 *      Author: mat25
 */

#include "functions.h"
#include "main.h"

#include "stm32f4xx_hal.h"
#include "gpio.h"




/********
 * Variable definition
 *******/

voidFunc Morbo_Upon_Enter[S_MAX] = {State_Enter_INIT, State_Enter_IDLE, State_Enter_COMPUTE, State_Enter_RESET,State_Enter_CHECK_AND_SEND_DATA};
voidFunc Morbo_Action_While_In_State[S_MAX] = {State_InState_INIT, State_InState_IDLE, State_InState_COMPUTE, State_InState_RESET,State_InState_CHECK_AND_SEND_DATA};
voidFunc Morbo_Upon_Exit[S_MAX] = {State_Exit_INIT, State_Exit_IDLE, State_Exit_COMPUTE, State_Exit_RESET,State_Exit_CHECK_AND_SEND_DATA};


/*******
 * Functions
 *******/
enum guards Check_Errors(void){

	if(ERR_COUNT < MAX_ERRORS) return ERR_COUNT_OK;
	else if(ERR_COUNT == MAX_ERRORS) return NOT_ERR_COUNT_OK;
	else return NOT_ERR_COUNT_OK;

}

/********
 * State machine main function
 *******/

enum states StateMachine(enum events event, enum guards guard, enum states Current_State)
{
    int Next_State = Current_State;

    switch ( Current_State )
    {
    case INIT:
           switch (event )
           {

               case (PERIPH_ALIVE):
                  if(guard == NOT_BUSY) Next_State = IDLE;
                   	break;
               default:
            	   break;
           }
    break;
    case IDLE:
           switch (event )
           {
               case (NOT_PERIPH_ALIVE):
               	if (guard == NOT_ERR_COUNT_OK) Next_State = RESET_MCH;
                   break;
               case (NEW_DATA):
                Next_State = COMPUTE;
                	break;

               default:
            	   break;
           }
    break;
    case COMPUTE:
           switch (event )
           {
               case (NOT_DATA_OK):
               	if(guard == NOT_ERR_COUNT_OK) Next_State = RESET_MCH;
                   break;
               case (DATA_READY):
                if (guard == NOT_BUSY) Next_State = CHECK_AND_SEND;
                	break;
               default:
            	   break;
           }
    break;
    case RESET_MCH:
           switch (event )
           {
               case (PERIPH_ALIVE):
               	if (guard == NOT_BUSY)Next_State = IDLE;
                   break;
               default:
            	   break;
           }
    break;
    case CHECK_AND_SEND:
           switch (event )
           {
               case (DATA_OK):
               	if(guard == NOT_BUSY)Next_State = IDLE;
                   break;
               case (NOT_DATA_OK_ERR_COUNT_OK):
                if (guard == NOT_BUSY) Next_State = COMPUTE;
               default:
            	   break;
           }
    break;



       default:
           break;
    }




    if (Next_State != Current_State)
    {
        // Function call for Upon Exit function, it can be omitted but allows extra functionality
        Morbo_Upon_Exit[Current_State]();
        // Function call for Upon Enter function, it can be omitted but allows extra functionality
        if (Next_State != S_MAX) Morbo_Upon_Enter[Next_State]();
    }
    else // ActionWhileInState is only be called when NOT doing a transition
     {
        if ( event != E_MAX) Morbo_Action_While_In_State[Current_State]();
    }
    return Next_State;
}


/*******
 * States related functions
 ******/

void State_Enter_INIT(void){
	current_guard = BUSY;
}
void State_InState_INIT(void){
	MAX_ERRORS = 6;
	ERR_COUNT = 0;
	HAL_GPIO_WritePin(USER_LED_GREEN_GPIO_Port, USER_LED_GREEN_Pin | USER_LED_RED_Pin | USER_LED_ORANGE_Pin | USER_LED_BLUE_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(USER_LED_GREEN_GPIO_Port, USER_LED_GREEN_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	current_signal = PERIPH_ALIVE;
	current_guard = NOT_BUSY;
}
void State_Exit_INIT(void){

}

void State_Enter_IDLE(void){
	current_guard = BUSY;
}
void State_InState_IDLE(void){
	HAL_GPIO_WritePin(USER_LED_GREEN_GPIO_Port, USER_LED_GREEN_Pin | USER_LED_RED_Pin | USER_LED_ORANGE_Pin | USER_LED_BLUE_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(USER_LED_GREEN_GPIO_Port, USER_LED_BLUE_Pin,GPIO_PIN_SET);
	HAL_Delay(100);
	current_signal = NEW_DATA;
	current_guard = NOT_BUSY;
}
void State_Exit_IDLE(void){

}

void State_Enter_COMPUTE(void){
	current_guard = BUSY;
}
void State_InState_COMPUTE(void){
	HAL_GPIO_WritePin(USER_LED_GREEN_GPIO_Port, USER_LED_GREEN_Pin | USER_LED_RED_Pin | USER_LED_ORANGE_Pin | USER_LED_BLUE_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(USER_LED_GREEN_GPIO_Port, USER_LED_ORANGE_Pin,GPIO_PIN_SET);
	HAL_Delay(100);
	current_signal = DATA_READY;
	current_guard = NOT_BUSY;
}
void State_Exit_COMPUTE(void){

}

void State_Enter_RESET(void){
	current_guard = BUSY;
}
void State_InState_RESET(void){
	HAL_GPIO_WritePin(USER_LED_GREEN_GPIO_Port, USER_LED_GREEN_Pin | USER_LED_RED_Pin | USER_LED_ORANGE_Pin | USER_LED_BLUE_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_TogglePin(USER_LED_GREEN_GPIO_Port, USER_LED_GREEN_Pin | USER_LED_RED_Pin | USER_LED_ORANGE_Pin | USER_LED_BLUE_Pin);
	HAL_Delay(100);
	current_guard = NOT_BUSY;
}
void State_Exit_RESET(void){

}

void State_Enter_CHECK_AND_SEND_DATA(void){
	current_guard = BUSY;
}
void State_InState_CHECK_AND_SEND_DATA(void){
	HAL_GPIO_WritePin(USER_LED_GREEN_GPIO_Port, USER_LED_GREEN_Pin | USER_LED_RED_Pin | USER_LED_ORANGE_Pin | USER_LED_BLUE_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(USER_LED_GREEN_GPIO_Port, USER_LED_RED_Pin,GPIO_PIN_SET);
	HAL_Delay(100);
	current_signal = DATA_OK;
	current_guard = NOT_BUSY;
}
void State_Exit_CHECK_AND_SEND_DATA(void){

}


