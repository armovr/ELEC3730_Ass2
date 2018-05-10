#include "Ass-02.h"

//*************Button Definitions*************
//Names for button order
#define DECIMALPOINT 	10
#define NEGATE 			11

#define PLUS 			12
#define SUBTRACT 		13
#define MULTIPLY 		14
#define DIVIDE 			15
#define SINE 		    16
#define EQUALS 			17
#define CLEAR 			18
#define ALLCLEAR 		19

#define OPERATOR 		20
#define ResultField 	21

#define DEBUG 			22

extern volatile uint8_t Debug;
//extern const command_s CommandList[];



//Button Structure initialisation
const button_s button[] = {
		//Buttons
		{(uint8_t *)"0",	{0,		64,		192, 	240},	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Zero},
		{(uint8_t *)"1",	{0,		64,		144,	192},	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Zero},
		{(uint8_t *)"2",	{64,	128,	144,	192},	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Zero},
		{(uint8_t *)"3",	{128,	192,	144,	192},	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Zero},
		{(uint8_t *)"4",	{0,		64,		96,		144},	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Zero},
		{(uint8_t *)"5",	{64,	128,	96,		144},	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Zero},
		{(uint8_t *)"6",	{128,	192,	96,		144},	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Zero},
		{(uint8_t *)"7",	{0,		64,		48,		96 },	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Zero},
		{(uint8_t *)"8",	{64,	128,	48,		96 },	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Zero},
		{(uint8_t *)"9",	{128,	192,	48,		96 },	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Zero},
		{(uint8_t *)".",	{64,	128,	192,	240},	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Zero},

		//Operators
		{(uint8_t *)"+/-",	{128,	192,	192,	240},	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Zero},
		{(uint8_t *)"+",	{192,	256,	96,		144},	LCD_COLOR_GREEN,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Add},
		{(uint8_t *)"-",	{256,	320,	96,		144},	LCD_COLOR_GREEN,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12}, 	&Calc_Sub},
		{(uint8_t *)"*",	{192,	256,	48,		96 },	LCD_COLOR_GREEN,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Mul},
		{(uint8_t *)"/",	{256,	320,	48,		96 },	LCD_COLOR_GREEN,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12}, 	&Calc_Div},
		{(uint8_t *)"sin",  {192,	256,	144,	192},	LCD_COLOR_GREEN,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Sin},
		{(uint8_t *)"=",	{192,	256,	192,	240},	LCD_COLOR_GREEN,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Zero},
		{(uint8_t *)"C",	{256,	320,	144,	192},	LCD_COLOR_GREEN,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12}, 	&Calc_Zero},
		{(uint8_t *)"AC",	{256,	320,	192,	240},	LCD_COLOR_GREEN,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Zero},


		//Answer Section
		{(uint8_t *)"Opp",	{0,		64,	     0,		48 }, 	LCD_COLOR_BLACK,  LCD_COLOR_WHITE,	CENTER_MODE,	{-32, 12},	&Calc_Zero},
		{(uint8_t *)"Res",	{64,	256,	 0,		48 }, 	LCD_COLOR_BLACK,  LCD_COLOR_WHITE,	RIGHT_MODE,		{-10, 12},	&Calc_Zero},

		//Debug
		{(uint8_t *)"DBG",	{256,	320,	 0,		48 }, 	LCD_COLOR_RED,  LCD_COLOR_WHITE,	CENTER_MODE,	{0, 12},	&Calc_Zero},

		//End of Structure
		{NULL,	{0,		0,		0,		0},		(int32_t)NULL,  	(int32_t)NULL,	(Line_ModeTypdef)NULL,	{0, 0}, NULL}
};


/*
 *
 * Function: CalculatorInit
 * ----------------------------
 * Simply initialises and turns on the calculator
 */
void CalculatorInit(void)
{
	uint8_t i;
	uint16_t a = 10000;
	BSP_LCD_Init();
	BSP_LCD_DisplayOn();
	BSP_TP_Init();    // Initialise interface and calibration process
	BSP_LCD_Clear(LCD_COLOR_BLACK);


	//Display and Debounce Post Calibration
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAt(160, 100, (uint8_t *)"LIFT YOU'RE", CENTER_MODE);
	BSP_LCD_DisplayStringAt(160, 140, (uint8_t *)"BLOODY FINGER", CENTER_MODE);

	while(a > 0)
	{
	while(BSP_TP_GetDisplayPoint(&display) == 0)
	{
		a = 1000;
	}
	a--;
	}

	// Loops through entire button structure printing them on the screen
	for(i=0; button[i].display != NULL; i++)
	{
	  ButtonDisplay(i,0);
	}
}

void CalculatorProcess(void) //using switch statement
{
	// Initialises all initial variables
	int8_t Button = -1;
	static uint8_t decimalRepeat =  0; 	//Flags if decimal point is pressed, prevents repeats
	static uint8_t finishedCalc = 0;		//Flags if going through second time
	static uint8_t input[LIMIT]; 		//Temporary input value store
	static uint8_t resultStr[LIMIT];	//Result Storage
	static uint8_t count = 0;			//Count through input array
	static uint8_t operator = -1;		//Storage of last operator pressed
	static uint8_t resultFlag =0;		//Flags if there's a result stored
	float negate;						//Holds a float to negate a string number

	// If a screen is pressed
	if (BSP_TP_GetDisplayPoint(&display) == 0)
	{

		if(!resultFlag)//A result is not stored
		{
			ArrayClear(resultStr);//Ensures Result is empty on startup
		}

		//Find which button
		Button = buttonNum(display.x,display.y);

		if(Debug == 1)
		{
			printf("Button Press: %s\n\r", button[Button].display);
		}

		switch(Button){

			case DEBUG:

				Calc_Debug();
				PrintString(input, ResultField);
				PrintString(button[operator].display, OPERATOR);

			break;

			case ALLCLEAR:

				if(Debug == 1)
				{
					printf("ALL");
				}

				ArrayClear(resultStr);
				resultFlag = 0; //ONLY time result flag clears
				operator = -1;
				finishedCalc = 0;

			case CLEAR:

				if(Debug == 1)
				{
					printf("CLEAR has been pressed\n\r");
				}

				ArrayClear(input);
				PrintString(input, ResultField);
				PrintString(button[operator].display, OPERATOR); //Might be a problem with all clear
				count = 0;
				decimalRepeat = 0;

			break;

			case NEGATE:

				if(Debug == 1)
				{
					printf("Negate: %s  => ", input);
				}

				if(resultFlag == 1 && finishedCalc == 1)
				{
					negate = -1*atof((char *)resultStr);
					sprintf((char *)resultStr, "%g", negate);
					PrintString(resultStr, ResultField);
				}
				else
				{
					negate = -1*atof((char *)input);
					sprintf((char *)input, "%g", negate);
					PrintString(input, ResultField);
				}

				if(Debug == 1)
				{
					printf(" %s\n\r", input);
				}

				//Think about this: 'count--' if goes positive??
				if (negate < 0) count++;
				else count--;

			break;

			case DECIMALPOINT:

				if(decimalRepeat == 0) decimalRepeat = 1;
				else //Decimal pressed twice: ignore it
				{
					PrintString(input, ResultField);
					break;
				}

			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 0:

				if(finishedCalc == 1) //accept new input with previous operator
				{
					ArrayClear(input);
					count = 0;
					finishedCalc = 0;
				}

				input[count] = button[Button].display[0]; // Stores char to argument 1
				PrintString(input, ResultField);		  // and prints it to the screen

				if(resultFlag == 1)
				{
					PrintString(button[operator].display, OPERATOR);   // AND prints the current operator
				}

				count++;

			break;

			case SINE:

				operator = Button;
				PrintString(button[operator].display, OPERATOR);

				if (resultFlag == 0)  //Doesn't need arg 1
				{
					ArrayClear(resultStr);
					strcpy((char *)resultStr, "1"); //if no arg 1 set it to '1*sin()'
					resultFlag = 1;
				}

			break;

			case PLUS:
			case SUBTRACT:
			case MULTIPLY:
			case DIVIDE:

				//Terminate input string
				input[count] = '\0';
				count = 0;

				if(resultFlag ==1)
				{
					if(finishedCalc == 0)//do a calculation and store new operator
					{
						if(Debug == 1)
						{
							printf("%s %s %s = ",resultStr,button[operator].display, input);
						}

						sprintf((char *)resultStr, "%g", (float)(*button[operator].operatorFunc)(resultStr, input));

						if(Debug == 1)
						{
							printf("%s\n\r", resultStr);
						}
					}

					PrintString(resultStr, ResultField);
				}
				else
				{
					strcpy((char*)resultStr,(char*)input); //Store in resultStr
				}

				ArrayClear(input);
				operator = Button;
				PrintString(button[operator].display, OPERATOR);
				resultFlag = 1; //First input now stored in result

			break;

			case EQUALS:

				if(resultFlag == 1)
				{
					if(Debug == 1)
					{
						printf("%s %s %s = ",resultStr,button[operator].display, input);
					}

					//Do calc or Repeat ongoing
					sprintf((char *)resultStr, "%g", (float)(*button[operator].operatorFunc)(resultStr, input));

					if(Debug == 1)
					{
						printf("%s\n\r", resultStr);
					}

				decimalRepeat = 0;
				finishedCalc = 1;
				resultFlag = 1;
				}

				PrintString(resultStr, ResultField);

			break;

			case OPERATOR:
			case ResultField:
			default:

				PrintString(input, ResultField);
				PrintString(button[operator].display, OPERATOR); //Might be a problem when operator = -1

			break;
		}

	}

	return;
}

//void CalculatorProcess(void) //using if else statements
//{
//	// Initialises all initial variables
//	int8_t Button = -1;
//	static uint8_t decimalRepeat =  0; 	//Flags if decimal point is pressed, prevents repeats
//	static uint8_t finishedCalc = 0;		//Flags if going through second time
//	static uint8_t input[LIMIT]; 		//Temporary input value store
//	static uint8_t resultStr[LIMIT];	//Result Storage
//	static uint8_t count = 0;			//Count through input array
//	static uint8_t operator = -1;		//Storage of last operator pressed
//	static uint8_t resultFlag =0;		//Flags if there's a result stored
//	float negate;						//Holds a float to negate a string number
//
//	// If a screen is pressed
//	if (BSP_TP_GetDisplayPoint(&display) == 0)
//	{
//		 //Find which button
//		 Button = buttonNum(display.x,display.y);
//
//		 if(Debug == 1)
//		 {
//			 printf("Button Press: %s\n\r", button[Button].display);
//		 }
//
//		 //if debug button, ignore everything else
//		 if (Button == DEBUG)
//		 {
//			 Calc_Debug();
//		 }
//
//
//		 else {
//
//			 	//ALLCLEAR has been pressed
//				if(Button == ALLCLEAR)
//				{
//
//					if(Debug == 1)
//					{
//						printf("ALLCLEAR has been pressed\n\r");
//					}
//
//					count = 0;
//					ArrayClear(input);
//					ArrayClear(resultStr);
//					PrintString(input, ResultField);
//					ClearDisplay(OPERATOR);
//					decimalRepeat = 0;
//					resultFlag = 0;
//					operator = -1;
//				}
//				//CLEAR Button have been pressed
//				else if(Button == CLEAR)
//				{
//					//Debugging
//					if(Debug == 1)
//					{
//						printf("CLEAR has been pressed\n\r");
//					}
//					ArrayClear(input);
//					PrintString(input, ResultField);
//					count = 0;
//					decimalRepeat = 0;
//				}
//				//Sine only needs second argument
//				if (Button == SINE)
//				{
//					 operator = Button;
//					 PrintString(button[operator].display, OPERATOR);
//
//				 if (resultFlag == 0)  //Doesn't need arg 1
//				 {
//					 ArrayClear(resultStr);
//					 strcpy((char *)resultStr, "1");
//					 resultFlag = 1;
//				 }
//
//				}
//
//				if(!resultFlag)//A result is not stored
//				{
//
//					ArrayClear(resultStr);//Ensures Result is empty on startup
//
//					if(Button <= DECIMALPOINT)	//checks whether a number button has been pressed and stores it as arg 1
//					{
//
//
//						 if(Button == DECIMALPOINT) //Decimal Pressed
//						 {
//							 if(decimalRepeat == 0) decimalRepeat = 1; //Decimal pressed twice: ignore it
//							 else
//							 {
//								 PrintString(input, ResultField);
//								 return;
//							 }
//						 }
//						 input[count] = button[Button].display[0]; 					// Stores char to argument 1
//						 PrintString(input, ResultField);							// and prints it to the screen
//						 count++;
//
//					resultFlag = 0; 												// Ensure cleared result flag
//				 }
//				 else if(Button >= NEGATE && Button < OPERATOR)						//button is an operator
//				 {
//
//					 if(Button != NEGATE)
//					 {
//						 decimalRepeat = 0;
//					 }
//
//					 //If a operator (* / + -) is pressed and there is an input
//					 if(count != 0 &&  Button >= PLUS && Button <= DIVIDE)
//					 {
//						 //Terminate input string
//						 input[count] = '\0';
//						 count =0;
//
//						 strcpy((char*)resultStr,(char*)input); //Store in resultStr
//
//						 ArrayClear(input);
//						 operator = Button;
//						 PrintString(button[operator].display, OPERATOR);
//						 resultFlag = 1; //First input now stored in result
//					 }
//					 else if(Button == NEGATE)
//					 {
//						 negate = -1*atof((char *)input);
//						 sprintf((char *)input, "%g", negate);
//						 PrintString(input, ResultField);
//						 count++;
//						 resultFlag = 0;
//					 }
//					 else{
//						 resultFlag = 0; //do nothing
//					 }
//
//				 }
//				 else //result area was pressed
//				 {
//					 PrintString(input, ResultField);
//					 resultFlag = 0; //do nothing
//				 }
//			}
//			else if(resultFlag)//Result holds an argument
//			{
//
//				 if(Button <= DECIMALPOINT) //button is number
//				 {
//
//					 if(finishedCalc == 1) //accept new input with previous operator
//					 {
//						 ArrayClear(input);
//						 count = 0;
//						 finishedCalc = 0;
//					 }
//
//					 if(Button == DECIMALPOINT) //Decimal Pressed
//					 {
//						 if(decimalRepeat == 0) decimalRepeat = 1; //Decimal pressed twice: ignore it
//						 else
//						 {
//							 PrintString(input, ResultField);
//							 return;
//						 }
//					 }
//
//					 input[count] = button[Button].display[0]; 			//stores char to argument 1
//					 PrintString(input, ResultField);					//and prints it to screen
//					 PrintString(button[operator].display, OPERATOR);   // AND prints the current operator
//
//					 count++;
//
//					 resultFlag = 1;
//				 }
//				 else if(Button >= NEGATE && Button < OPERATOR)         //button is operator
//				 {
//					 if(Button != NEGATE)
//					 {
//						 decimalRepeat = 0;
//					 }
//
//					 //If a operator is pressed (* / + - %) and and there is an input
//					 if(count != 0 && Button >= PLUS && Button <= DIVIDE)
//					 {
//						 //Terminate the input
//						 input[count] = '\0';
//
//						 if(finishedCalc == 0)//do a calculation and store new operator
//						 {
//							 if(Debug == 1)
//							 {
//								printf("%s %s %s = ",resultStr,button[operator].display, input);
//							 }
//
//							 sprintf((char *)resultStr, "%g", (float)(*button[operator].operatorFunc)(resultStr, input));
//
//							 if(Debug == 1)
//							 {
//								 printf("%s\n\r", resultStr);
//							 }
//						 }
//
//						 operator = Button;
//						 PrintString(button[operator].display, OPERATOR);
//						 ArrayClear(input);
//						 count = 0;
//						 PrintString(resultStr, ResultField);
//						 resultFlag = 1;
//					 }
//					 else if(Button == NEGATE)
//					 {
//						 //negate the input String
//						 negate = -1*atof((char *)resultStr);
//						 sprintf((char *)resultStr, "%g", negate);
//						 PrintString(resultStr, ResultField);
//						 resultFlag = 1;
//					 }
//
//					 else if(Button == EQUALS)
//					 {
//
//						 if(Debug == 1)
//						 {
//							 printf("%s %s %s = ",resultStr,button[operator].display, input);
//						 }
//
//						 //Do calc or Repeat ongoing
//						 sprintf((char *)resultStr, "%g", (float)(*button[operator].operatorFunc)(resultStr, input));
//
//
//						 if(Debug == 1)
//						 {
//							 printf("%s\n\r", resultStr);
//						 }
//						 PrintString(resultStr, ResultField);
//						 decimalRepeat = 0;
//						 finishedCalc = 1;
//						 resultFlag = 1;
//
//					}
//					else
//					{
//						resultFlag = 1;//do nothing
//					}
//				 }
//				 else//result area was pressed
//				 {
//					 PrintString(button[operator].display, OPERATOR);
//					 PrintString(input, ResultField);
//					 resultFlag = 1; //do nothing
//				 }
//			}
//		 }
//	}
//}

/*
 * Function: buttonNum
 * ----------------------------
 *
 * Finds which button is being pressed
 * Returns Integer Corresponding to Button
 *
 */

int8_t buttonNum(uint16_t xPosi, uint16_t yPosi)
{
	uint8_t j, i = 0;
	uint8_t x = 100;

	for(i=0; button[i].display != NULL; i++){
		if((xPosi >= button[i].co_ord[0]) && (xPosi <= button[i].co_ord[1]) && (yPosi >= button[i].co_ord[2]) && (yPosi <= button[i].co_ord[3]))
		{

			ButtonDisplay(i,1);

			while(x > 0)
			{

				if(BSP_TP_GetDisplayPoint(&display) == 0)
				{
					x = 100;
				}
				x--;

			}
			break;
		}
	}
	for(j=0; button[j].display != NULL; j++)
	{
		ButtonDisplay(j,0);
	}
	return i;
}



/*
 * Function: ButtonDisplay
 * ----------------------------
 *   Returns void
 *
 * Draws Button from button_s
 *
 *
 */
void ButtonDisplay(uint8_t buttonNum, uint8_t indent)
{

	//Fill Rectangle
	if(indent){
		BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	}
	else{
		BSP_LCD_SetTextColor(button[buttonNum].colour);
	}
	BSP_LCD_FillRect(button[buttonNum].co_ord[0],button[buttonNum].co_ord[2],
			button[buttonNum].co_ord[1]-button[buttonNum].co_ord[0],button[buttonNum].co_ord[3]-button[buttonNum].co_ord[2]);

	//Draw outlines
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawRect(button[buttonNum].co_ord[0],button[buttonNum].co_ord[2],
			button[buttonNum].co_ord[1]-button[buttonNum].co_ord[0],button[buttonNum].co_ord[3]-button[buttonNum].co_ord[2]);

	//Insert String
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

	if(indent){
		BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
	}
	else{
		BSP_LCD_SetBackColor(button[buttonNum].colour);
	}

	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAt((((button[buttonNum].co_ord[1]-button[buttonNum].co_ord[0])/2)+button[buttonNum].co_ord[0]),
			button[buttonNum].co_ord[2]+(0.3*(button[buttonNum].co_ord[3]-button[buttonNum].co_ord[2])),
			button[buttonNum].display, CENTER_MODE);

}

/*
 *
 * Function: PrintString
 * ----------------------------
 *   Returns void
 *
 * Prints a string inside a button boundary
 *
 *
 */
void PrintString(uint8_t *string, uint8_t Button)
{
	ClearDisplay(Button);
	BSP_LCD_SetTextColor(button[Button].fontColour);
	BSP_LCD_SetBackColor(button[Button].colour);
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAt(button[Button].co_ord[1]+button[Button].offSet[0],
			button[Button].co_ord[2]+button[Button].offSet[1],(uint8_t *)string,  button[Button].lineMode);

	return;
}

/*
 *
 * Function: ClearDisplay
 * ----------------------------
 *   Returns void
 *
 * Draws Empty Button on top of previous button to clear
 *
 *
 */
void ClearDisplay(uint8_t buttonNum)
{
	BSP_LCD_SetTextColor(button[buttonNum].colour);
	BSP_LCD_FillRect(button[buttonNum].co_ord[0],button[buttonNum].co_ord[2],
				button[buttonNum].co_ord[1]-button[buttonNum].co_ord[0],button[buttonNum].co_ord[3]-button[buttonNum].co_ord[2]);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawRect(button[buttonNum].co_ord[0],button[buttonNum].co_ord[2],
				button[buttonNum].co_ord[1]-button[buttonNum].co_ord[0],button[buttonNum].co_ord[3]-button[buttonNum].co_ord[2]);

	return;
}


/*
 * Function: CLEAR Array
 * ----------------------------
 *   Returns Void
 *
 *		Replaces values in array with all NULL characters
 *
 *
 */
void ArrayClear(uint8_t *Array_p)
{
	uint8_t i;
	for(i =0; i<LIMIT;i++){
		Array_p[i]= (uint8_t)'\0';
	}
};

//QUESTION 2 Operators

/*
 * Function: Calc_Zero
 * ----------------------------
 * Does nothing and returns nothing.
 * Occurs every time a button is pressed that requires
 * no immediate calculation
 */
float Calc_Zero(uint8_t *arg1, uint8_t *arg2)
{
	return 0;
};



/*
 *
 * Function: Calc_Mod
 * ----------------------------
 * Takes in two values and returns
 * the modulus
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
 * Takes in 2 uint's and returns sum
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
 *   Takes in 2 uint's and returns negated value
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
 * Takes in 2 uints and returns
 * multiplied result
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
 * Function: Calc_Div
 * ----------------------------
 * Takes in 2 uints and returns divised
 * solution
 */
float Calc_Div(uint8_t *arg1, uint8_t *arg2)
{

	float a, b;
	a = atof((char*)arg1);
	b = atof((char*)arg2);
	return a / b;
};

/*
 * Function: Calc_Sin
 * ----------------------------
 * Takes in 1 value and returns the sin
 * solution
 */
float Calc_Sin(uint8_t *arg1, uint8_t *arg2)
{
	return atof((char*)arg1)*sin(atof((char*)arg2)*3.14159265/180);
}

/*
 * Function: Calc_Debug
 * ----------------------------
 * Indents Debug
 *
 */
void Calc_Debug()
{
	Debug = !Debug;

	if(Debug == 1)
	{
		printf("Debug turned ON from Calculator\n\r");
	}
	else if(Debug == 0)
	{
		printf("Debug turned OFF from Calculator\n\r");
	}

	return;
}
