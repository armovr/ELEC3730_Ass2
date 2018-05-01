

#include "Ass-02.h"

//*************Button Definitions*************
//Defines the struct index for each opperator button
#define PLUSMINUS 11
#define MODULUS 12
#define Addition 13
#define Multiplication 14
#define Equals 15
#define Clear 16
#define Subtraction 17
#define Division 18
#define All_Clear 19
#define OPP 20
#define Result 21



//Button Structure initilization
const button_s ButtonList[] = {
		//Buttons
		{(uint8_t *)"0",	{0,		64,		192, 	240},	(uint8_t *)&Font24,	LCD_COLOR_WHITE, LCD_COLOR_GRAY,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"1",	{0,		64,		144,	192},	(uint8_t *)&Font24,	LCD_COLOR_WHITE, LCD_COLOR_GRAY,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"2",	{64,	128,	144,	192},	(uint8_t *)&Font24,	LCD_COLOR_WHITE, LCD_COLOR_GRAY,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"3",	{128,	192,	144,	192},	(uint8_t *)&Font24,	LCD_COLOR_WHITE, LCD_COLOR_GRAY,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"4",	{0,		64,		96,		144},	(uint8_t *)&Font24,	LCD_COLOR_WHITE, LCD_COLOR_GRAY,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"5",	{64,	128,	96,		144},	(uint8_t *)&Font24,	LCD_COLOR_WHITE, LCD_COLOR_GRAY,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"6",	{128,	192,	96,		144},	(uint8_t *)&Font24,	LCD_COLOR_WHITE, LCD_COLOR_GRAY,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"7",	{0,		64,		48,		96},	(uint8_t *)&Font24,	LCD_COLOR_WHITE, LCD_COLOR_GRAY,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"8",	{64,	128,	48,		96},	(uint8_t *)&Font24,	LCD_COLOR_WHITE, LCD_COLOR_GRAY,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"9",	{128,	192,	48,		96},	(uint8_t *)&Font24,	LCD_COLOR_WHITE, LCD_COLOR_GRAY,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)".",	{64,	128,	192,	240},	(uint8_t *)&Font24,	LCD_COLOR_WHITE, LCD_COLOR_GRAY,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},

		//Operators
		{(uint8_t *)"+/-",	{128,	192,	192,	240},	(uint8_t *)&Font24,	LCD_COLOR_WHITE,		LCD_COLOR_GRAY,   LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"%",	{192,	256,	144,	192},	(uint8_t *)&Font24,	LCD_COLOR_GREEN, 		LCD_COLOR_GRAY ,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Mod},
		{(uint8_t *)"+",	{192,	256,	96,		144},	(uint8_t *)&Font24,	LCD_COLOR_GREEN, 		LCD_COLOR_GRAY ,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Add},
		{(uint8_t *)"X",	{192,	256,	48,		96},	(uint8_t *)&Font24,	LCD_COLOR_GREEN, 		LCD_COLOR_GRAY ,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Mul},
		{(uint8_t *)"=",	{192,	256,	192,	240},	(uint8_t *)&Font24,	LCD_COLOR_GREEN, 		LCD_COLOR_GRAY ,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"C",	{256,	320,	144,	192},	(uint8_t *)&Font24,	LCD_COLOR_GREEN, 		LCD_COLOR_GRAY ,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12}, 	&Calc_0},
		{(uint8_t *)"-",	{256,	320,	96,		144},	(uint8_t *)&Font24,	LCD_COLOR_GREEN, 		LCD_COLOR_GRAY ,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12}, 	&Calc_Sub},
		{(uint8_t *)"/",	{256,	320,	48,		96},	(uint8_t *)&Font24,	LCD_COLOR_GREEN, 		LCD_COLOR_GRAY ,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12}, 	&Calc_Div},
		{(uint8_t *)"AC",	{256,	320,	192,	240},	(uint8_t *)&Font24,	LCD_COLOR_GREEN, 		LCD_COLOR_GRAY ,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},

		//Result Field
		{(uint8_t *)"Opp",	{0,		64,	0,		48},		(uint8_t *)&Font24,	LCD_COLOR_BLACK,  LCD_COLOR_BLACK,  LCD_COLOR_WHITE,	CENTER_MODE,	{-32, 12},	&Calc_0},
		{(uint8_t *)"Res",	{64,	320,	0,		48},	(uint8_t *)&Font24,	LCD_COLOR_BLACK,  LCD_COLOR_BLACK,  LCD_COLOR_WHITE,	RIGHT_MODE,	{-120, 12},	&Calc_0},

		//Terminator
		{NULL,	{0,		0,		0,		0},		NULL,	(int32_t)NULL,	(int32_t)NULL,	(int32_t)NULL,	(Line_ModeTypdef)NULL,	{0, 0}, NULL}
};

/*
 * Function: Calc_0
 * ----------------------------
 *   Returns float = 0
 *
 * Function that returns 0 and changes nothing
 *
 *
 */
float Calc_0(uint8_t *arg1, uint8_t *arg2)
{
	return 0;
};


/*
 *
 * Function: Calc_Mod
 * ----------------------------
 *   Returns int8_t
 *
 * Function executed for Modulous opperation
 * Returns arg1 % arg 2
 *
 */
float Calc_Mod(uint8_t *arg1, uint8_t *arg2)
{
	uint8_t a, b;
	a = atof((char*)arg1);
	b = atof((char*)arg2);
	 return a%b;
};

/*
 *
 * Function: Calc_Add
 * ----------------------------
 *   Returns int8_t
 *
 * Function executed for Addition opperation
 * Returns arg1 + arg2
 *
 */
float Calc_Add(uint8_t *arg1, uint8_t *arg2)
{
	float a, b;
	a = atof((char*)arg1);
	b = atof((char*)arg2);
	return a+b;
};

/*
 *
 * Function: Calc_Sub
 * ----------------------------
 *   Returns int8_t
 *
 * Function executed for Subtraction opperation
 * Returns arg1 - arg2
 *
 */
float Calc_Sub(uint8_t *arg1, uint8_t *arg2)
{
	float a, b;
	a = atof((char*)arg1);
	b = atof((char*)arg2);
	return a - b;
};

/*
 *
 * Function: Calc_Mul
 * ----------------------------
 *   Returns int8_t
 *
 * Function executed for Multiplication opperation
 * Returns arg1 x arg2
 *
 */
float Calc_Mul(uint8_t *arg1, uint8_t *arg2)
{
	float a, b;
	a = atof((char*)arg1);
	b = atof((char*)arg2);
	return a * b;
};

/*
 *
 * Function: Calc_Div
 * ----------------------------
 *   Returns int8_t
 *
 * Function executed for Division opperation
 * Returns arg1 / arg2
 *
 */
float Calc_Div(uint8_t *arg1, uint8_t *arg2)
{

	float a, b;
	a = atof((char*)arg1);
	b = atof((char*)arg2);
	return a / b;
};

/*
 *
 * Function: CalculatorInit
 * ----------------------------
 *   Returns NOTHING
 *
 * Function Initializes The calculator screen ready for use
 *
 *
 */
void CalculatorInit(void)
{
  uint8_t i;
  uint16_t a = 10000;
  // Initialize and turn on LCD and calibrate the touch panel
  BSP_LCD_Init();
  BSP_LCD_DisplayOn();
  BSP_TP_Init();
  BSP_LCD_Clear(LCD_COLOR_BLACK);

	//Display Welcome Message to avoid a false press from calibration
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_SetFont((sFONT*)&Font24);
	BSP_LCD_DisplayStringAt(160, 100, (uint8_t *)"LIFT YOU'RE", CENTER_MODE);
	BSP_LCD_DisplayStringAt(160, 140, (uint8_t *)"BLOODY FINGER", CENTER_MODE);
	while(a > 0)
	{
		while(BSP_TP_GetDisplayPoint(&display) == 0)
		{
			a = 1000;//while the touch screen is being pressed it never leaves the for loop
		}
		a--;
	}

  //Draw the calculator screen
  for(i=0; ButtonList[i].Character_String != NULL; i++)
  {
	  DrawButton(i,0);
  }
}

/*
 *
 * Function: CalculatorProcess
 * ----------------------------
 *   Returns NOTHING
 *	 Recieves uint8_t Debug_p(Debug status)
 *
 * Function Carries out calculation processes based on touch input
 *
 *
 */
void CalculatorProcess(void)
{
	int8_t Button = -1;
	static uint8_t decFlag =  0;
	static uint8_t preCo = 0;
	static uint8_t val_1[LIMIT]; //Stores the second String for calculation
	static uint8_t Calculation[LIMIT];
	static uint8_t strCounter = 0;
	static uint8_t Command = -1;
	static uint8_t State =0;
	float Toggle;
	if (BSP_TP_GetDisplayPoint(&display) == 0)
	{
		 Button = FindPress(display.x,display.y);
		 switch(State)
		 {
		 	 case 0://No arguments have been input yet

		 		 if(Button <=10)
				 {
					 //Debugging
			 		 if(Debug == 1)
					 {
						 printf("Button Press: %s\n\r", ButtonList[Button].Character_String);
					 }

		 			 if(decFlag == 1 && Button == 10)
		 			 {
		 				 //Do NOTHING
		 			 }
		 			 else if(Button == 10)
		 			 {
		 				 decFlag = 1;
						 //if number is pressed update argument 1
						 val_1[strCounter] = ButtonList[Button].Character_String[0];
						 Print_To_Screen(val_1, Result);//*function* print in result pannel
						 strCounter++;
		 			 }
		 			 else
		 			 {
						 //if number is pressed update argument 1
						 val_1[strCounter] = ButtonList[Button].Character_String[0];
						 Print_To_Screen(val_1, Result);//*function* print in result pannel
						 strCounter++;
		 			 }
		 			State = 0; // remain in arg1 update case
				 }
				 else if(Button >= 11 && Button < 20)
				 {
					 //Debugging
			 		 if(Debug == 1)
					 {
						 printf("Button Press: %s\n\r", ButtonList[Button].Character_String);
					 }

					 if(Button != PLUSMINUS)
					 {
						 decFlag = 0;
					 }
					//Can only leave State 0 if a operator is pressed (X / + - %) and Arguments have been entered in val_1
					 if(strCounter != 0 && Button != Equals && Button != All_Clear && Button != Clear && Button != PLUSMINUS){

					 //Terimate the input string with a null and reset the counter before leaving
						 //Debugging
				 		 if(Debug == 1)
						 {
				 			 printf("Case 0: Operator has been pressed\n\r");
						 }
						 val_1[strCounter] = '\0';
						 strCounter =0;
						 //Update Result Argument before leaving
						 strcpy((char*)Calculation,(char*)val_1);
						 //Value has been copied to Calculation argument, clear the  val_1er
						 Clear_Array(val_1);
						 Command = Button;
						 Print_To_Screen(ButtonList[Command].Character_String, OPP);
						 State = 1;
					 }
					 else if(Button == PLUSMINUS)
					 {
						//Toggle the input String
						 Toggle = -1*atof((char *)val_1);
						 sprintf((char *)val_1, "%g", Toggle);
						 Print_To_Screen(val_1, Result);
						 strCounter++;
						 State = 0;
					 }
					 //No argument has been entered therefore wait before leaving initial state
					else if( Button != All_Clear || Button != Clear){

						strCounter = 0;
						Clear_Array(val_1);
						Print_To_Screen(val_1, Result);
						Clear_Button(OPP);
						decFlag = 0;
						State = 0;
					}
					 //No argument has been entered therefore wait before leaving initial state
					else{
						State = 0;
					}
				 }
				 else//result area was pressed do nothing no button was found
				 {
					 //printf("PRESSED IN RESULT\n\r");//debug
					 State = 0;
				 }
		 		 break;
		 	 case 1://Result holds an argument

				 if(Button < 11)
				 {
					 //Debugging
			 		 if(Debug == 1)
					 {
						 printf("Button Press: %s\n\r", ButtonList[Button].Character_String);
					 }

					 if(preCo == 1)
					 {
						 Clear_Array(val_1);
						 strCounter = 0;
						 preCo = 0;
					 }
					 //if number is pressed update argument 1
					 if(decFlag == 1 && Button == 10)
					 {
						 //do nothing
					 }
					 else if(Button == 10)
					 {
						 val_1[strCounter] = ButtonList[Button].Character_String[0];
						 Print_To_Screen(val_1, Result);//*function* print in result pannel
						 Print_To_Screen(ButtonList[Command].Character_String, OPP);//*function* print in result pannel
						 decFlag = 1;
						 strCounter++;
					 }
					 else
					 {
						 val_1[strCounter] = ButtonList[Button].Character_String[0];
						 Print_To_Screen(val_1, Result);//*function* print in result pannel
						 Print_To_Screen(ButtonList[Command].Character_String, OPP);//*function* print in result pannel
						 strCounter++;
					 }
				 	 State = 1; // remain in arg1 update case
				 }
				 else if(Button >= 11 && Button < 20)
				 {
					 //Debugging
			 		 if(Debug == 1)
					 {
						 printf("Button Press: %s\n\r", ButtonList[Button].Character_String);
					 }

					 if(Button != PLUSMINUS)
					 {
						 decFlag = 0;
					 }
						//Can only leave State 1 if a operator is pressed (X / + - %) and Arguments have been entered in val_1
						 if(strCounter != 0 && Button != Equals && Button != All_Clear && Button != Clear && Button != PLUSMINUS){
						 //Terimate the input string with a null and reset the counter before leaving
							 //Debugging
					 		 if(Debug == 1)
							 {
					 			 printf("Case 1: Operator has been pressed\n\r");
							 }
							 val_1[strCounter] = '\0';
							 strCounter =0;
							 //Update Result Before updating commmand
							 //Calculation completed
							 if(preCo == 0){ //do a normal calculation
								 //Debugging
						 		 if(Debug == 1)
								 {
						 			printf("%s %s %s = ",Calculation,ButtonList[Command].Character_String, val_1);
								 }

								 sprintf((char *)Calculation, "%g", (float)(*ButtonList[Command].Opperation_p)(Calculation, val_1));

								 //Debugging
						 		 if(Debug == 1)
								 {
									 printf("%s\n\r", Calculation);
								 }
							 }
							 else{
								//Because we are coming back from the repeated equals operator, dont do another calculation but clear string instead
								Clear_Array(val_1);
								strCounter = 0;
								preCo = 0; //Set the equals flag to zero so next return does a normal calculation
							 }
							 //Update command entered
							 Command = Button;
							 Print_To_Screen(ButtonList[Command].Character_String, OPP);
							 //Clear the previous value
							 Clear_Array(val_1);
							 Print_To_Screen(Calculation, Result);
							 State = 1;
						 }
						 else if(Button == PLUSMINUS)
						 {
							//Toggle the input String
							 Toggle = -1*atof((char *)Calculation);
							 sprintf((char *)Calculation, "%g", Toggle);
							 Print_To_Screen(Calculation, Result);
							 State = 1;
						 }
						 //All_Clear has been pressed
						 else if(Button == Equals){


							 //Debugging
					 		 if(Debug == 1)
							 {
					 			 //Calculation String
					 			 printf("%s %s %s = ",Calculation,ButtonList[Command].Character_String, val_1);
							 }

					 		 //Repeat the previous calculation
							 sprintf((char *)Calculation, "%g", (float)(*ButtonList[Command].Opperation_p)(Calculation, val_1));

							 //Debugging
					 		 if(Debug == 1)
							 {
								 printf("%s\n\r", Calculation);
							 }
							 Print_To_Screen(Calculation, Result);
							 decFlag = 0;
							 preCo = 1;
							 State = 1;
						 }
						else if( Button == All_Clear){

							strCounter = 0;
							Clear_Array(val_1);
							Clear_Array(Calculation);
							Print_To_Screen(val_1, Result);
							Clear_Button(OPP);
							decFlag = 0;
							State = 0;
						}
						//Clear Button have been pressed
						else if(Button == Clear){
							 //Debugging
					 		 if(Debug == 1)
							 {
								 printf("Case 1: Clear has been pressed\n\r");
							 }
							Clear_Array(val_1);
							Print_To_Screen(val_1, Result);
							strCounter = 0;
							decFlag = 0;
							State = 1;
						}
						 //No argument has been entered therefore wait before leaving initial state
						else{
							State = 1;
						}
				 }
				 else//result area was pressed do nothing no button was found
				 {
					State = 1;
				 }
				 break;

			  default:
				 //Do nothing
				 break;
		 }
	}

}



/*//FIXME
 * Function: FindPress
 * ----------------------------
 * Returns int corespinding to button struct index
 *
 *
 *
 *
 */
int8_t FindPress(uint16_t X_Pos, uint16_t Y_Pos){
	uint8_t j, i = 0;
	uint8_t x = 100;

	for(i=0; ButtonList[i].Character_String != NULL; i++){
		if((X_Pos >= ButtonList[i].Loc[0]) && (X_Pos <= ButtonList[i].Loc[1]) && (Y_Pos >= ButtonList[i].Loc[2]) && (Y_Pos <= ButtonList[i].Loc[3]))
		{

			DrawButton(i,1);

			while(x > 0)
			{

				if(BSP_TP_GetDisplayPoint(&display) == 0)
				{
					x = 100;
				}
				x--;
				//Toggle the pressed button

			}
			break;
		}
	}
	for(j=0; ButtonList[j].Character_String != NULL; j++)
	{
		DrawButton(j,0);
	}
	return i;
}



/*
 * Function: DrawButton
 * ----------------------------
 *   Returns void
 *
 * Draws Button from button_s
 *
 *
 */
void DrawButton(uint8_t DrawButton, uint8_t Toggle){

	//Fill Rectangle
	if(Toggle){
		BSP_LCD_SetTextColor(ButtonList[DrawButton].ToggleColour);
	}
	else{
		BSP_LCD_SetTextColor(ButtonList[DrawButton].BackColour);
	}
	BSP_LCD_FillRect(ButtonList[DrawButton].Loc[0],ButtonList[DrawButton].Loc[2],
			ButtonList[DrawButton].Loc[1]-ButtonList[DrawButton].Loc[0],ButtonList[DrawButton].Loc[3]-ButtonList[DrawButton].Loc[2]);

	//Draw outlines
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawRect(ButtonList[DrawButton].Loc[0],ButtonList[DrawButton].Loc[2],
			ButtonList[DrawButton].Loc[1]-ButtonList[DrawButton].Loc[0],ButtonList[DrawButton].Loc[3]-ButtonList[DrawButton].Loc[2]);
	//Print debug message for the location of rectangle center

	//debug

	//printf("Button %s\n\r",ButtonList[DrawButton].Character_String);
	//printf("X center location of button is %d\n\r",(((ButtonList[DrawButton].Loc[1]-ButtonList[DrawButton].Loc[0])/2)+ButtonList[DrawButton].Loc[0]));
	//printf("Y center location of button is %d\n\r",(((ButtonList[DrawButton].Loc[3]-ButtonList[DrawButton].Loc[2])/2)+ButtonList[DrawButton].Loc[2]));


	//Insert String
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

	if(Toggle){
		BSP_LCD_SetBackColor(ButtonList[DrawButton].ToggleColour);
	}
	else{
		BSP_LCD_SetBackColor(ButtonList[DrawButton].BackColour);
	}

	BSP_LCD_SetFont((sFONT*)ButtonList[DrawButton].Font);
	BSP_LCD_DisplayStringAt((((ButtonList[DrawButton].Loc[1]-ButtonList[DrawButton].Loc[0])/2)+ButtonList[DrawButton].Loc[0]),
			ButtonList[DrawButton].Loc[2]+(0.3*(ButtonList[DrawButton].Loc[3]-ButtonList[DrawButton].Loc[2])),
			ButtonList[DrawButton].Character_String, CENTER_MODE);

}

/*
 *
 * Function: Print_To_Screen
 * ----------------------------
 *   Returns void
 *
 * Prints a string inside a button boundary
 *
 *
 */
void Print_To_Screen(uint8_t *String_p, uint8_t Button)
{
	Clear_Button(Button);
	BSP_LCD_SetTextColor(ButtonList[Button].TextColour);
	BSP_LCD_SetBackColor(ButtonList[Button].BackColour);
	BSP_LCD_SetFont((sFONT *)ButtonList[Button].Font);
	BSP_LCD_DisplayStringAt(ButtonList[Button].Loc[1]+ButtonList[Button].OffSet[0], ButtonList[Button].Loc[2]+ButtonList[Button].OffSet[1],(uint8_t *)String_p,  ButtonList[Button].MODE);//change to location of button
}

/*
 *
 * Function: Clear_Button
 * ----------------------------
 *   Returns void
 *
 * Draws Empty Button on top of previous button to clear
 *
 *
 */
void Clear_Button(uint8_t DrawButton)
{
	BSP_LCD_SetTextColor(ButtonList[DrawButton].BackColour);
	BSP_LCD_FillRect(ButtonList[DrawButton].Loc[0],ButtonList[DrawButton].Loc[2],
				ButtonList[DrawButton].Loc[1]-ButtonList[DrawButton].Loc[0],ButtonList[DrawButton].Loc[3]-ButtonList[DrawButton].Loc[2]);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawRect(ButtonList[DrawButton].Loc[0],ButtonList[DrawButton].Loc[2],
				ButtonList[DrawButton].Loc[1]-ButtonList[DrawButton].Loc[0],ButtonList[DrawButton].Loc[3]-ButtonList[DrawButton].Loc[2]);
}


/*
 * Function: Clear Array
 * ----------------------------
 *   Returns Void
 *
 *		Replaces values in array with all NULL characters
 *
 *
 */
void Clear_Array(uint8_t *Array_p)
{
	uint8_t i;
	for(i =0; i<LIMIT;i++){
		Array_p[i]= (uint8_t)'\0';
	}
};
