//     $Date: 2018-03-26 08:32:18 +1100 (Mon, 26 Mar 2018) $
// $Revision: 1217 $
//   $Author: Peter $

// Assignment 2 include file

#ifndef ASS_02_H_
#define ASS_02_H_

// Standard includes
#ifdef STM32F407xx
#include "stm32f4xx_hal.h"
#include "openx07v_c_lcd.h"
#include "touch_panel.h"
#else
#include <windows.h>
#endif
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

//Variables
#define LIMIT 101

typedef struct{
	int8_t *NameString;
	int8_t (*Function_p)(uint8_t ArgNum, uint8_t *ArgStrings[]);
	int8_t *HelpString;
}command_s;

// Assignment main
extern void Ass_02_Main(void);

//
// REPLACE THE EXAMPLE CODE WITH YOUR CODE 
//

// Question 1
extern int8_t Add_Function (uint8_t ArgNum, uint8_t *ArgStrings[]);
extern int8_t Sub_Function (uint8_t ArgNum, uint8_t *ArgStrings[]);
extern int8_t Mul_Function (uint8_t ArgNum, uint8_t *ArgStrings[]);
extern int8_t Div_Function (uint8_t ArgNum, uint8_t *ArgStrings[]);
extern int8_t Help_Function (uint8_t ArgNum, uint8_t *ArgStrings[]);
extern int8_t Debug_Function (uint8_t ArgNum, uint8_t *ArgStrings[]);
extern int8_t Clear_Function (uint8_t ArgNum, uint8_t *ArgStrings[]);

extern void CommandLineParserInit(void);
extern void CommandLineParserProcess(void);

extern uint8_t string_parser(char *inp, char **array_of_words_p[]);

// Question 2
extern void CalculatorInit(void);
extern void CalculatorProcess(void);

// Library functions
#ifdef STM32F407xx
extern uint8_t BSP_TP_Init(void);
extern uint8_t BSP_TP_GetDisplayPoint(Coordinate *pDisplay);
#endif

#endif /* ASS_02_H_ */
