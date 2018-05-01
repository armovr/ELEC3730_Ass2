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

volatile extern uint8_t Debug;

typedef struct{
	int8_t *NameString;
	int8_t (*Function_p)(uint8_t ArgNum, uint8_t *ArgStrings[]);
	int8_t *HelpString;
}command_s;

typedef struct{
	uint8_t *Character_String;
	uint16_t Loc[4];
	uint8_t *Font;
	uint32_t BackColour;
	uint32_t ToggleColour;
	uint32_t TextColour;
	Line_ModeTypdef MODE;
	int8_t OffSet[2];
	float (*Opperation_p)(uint8_t* arg1, uint8_t* arg2);
}button_s;

// Assignment main
extern void Ass_02_Main(void);

//
// REPLACE THE EXAMPLE CODE WITH YOUR CODE 
//

// Question 1
extern int8_t AddFunc (uint8_t ArgNum, uint8_t *ArgStrings[]);
extern int8_t SubFunc (uint8_t ArgNum, uint8_t *ArgStrings[]);
extern int8_t MulFunc (uint8_t ArgNum, uint8_t *ArgStrings[]);
extern int8_t DivFunc (uint8_t ArgNum, uint8_t *ArgStrings[]);
extern int8_t HelpFunc (uint8_t ArgNum, uint8_t *ArgStrings[]);
extern int8_t DebugFunc (uint8_t ArgNum, uint8_t *ArgStrings[]);
extern int8_t ClearFunc (uint8_t ArgNum, uint8_t *ArgStrings[]);

extern void CommandLineParserInit(void);
extern void CommandLineParserProcess(void);

extern uint8_t string_parser(char *inp, char **array_of_words_p[]);

// Question 2
extern void CalculatorInit(void);
extern void CalculatorProcess(void);

//LCD Calculator Functions
void DrawButton(uint8_t DrawButton, uint8_t Toggle);
int8_t FindPress(uint16_t X_Pos, uint16_t Y_Pos);
void Print_To_Screen(uint8_t *String_p, uint8_t Button);
void Clear_Button(uint8_t Button);
void Clear_Array(uint8_t *Array_p);

float Calc_0(uint8_t *arg1, uint8_t *arg2);
float Calc_Add(uint8_t *arg1, uint8_t *arg2);
float Calc_Sub(uint8_t *arg1, uint8_t *arg2);
float Calc_Mul(uint8_t *arg1, uint8_t *arg2);
float Calc_Div(uint8_t *arg1, uint8_t *arg2);
float Calc_Mod(uint8_t *arg1, uint8_t *arg2);

// Library functions
#ifdef STM32F407xx
extern uint8_t BSP_TP_Init(void);
extern uint8_t BSP_TP_GetDisplayPoint(Coordinate *pDisplay);
#endif

#endif /* ASS_02_H_ */
