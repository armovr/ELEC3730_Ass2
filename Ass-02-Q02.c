#include "Ass-02.h"

//*************Button Definitions*************
//Names for button order
#define DECIMALPOINT 	10
#define NEGATE 			11

#define PLUS 			12
#define SUBTRACT 		13
#define MULTIPLY 		14
#define DIVIDE 			15
#define MODULUS 		16
#define EQUALS 			17
#define CLEAR 			18
#define ALLCLEAR 		19

#define OPERATOR 		20
#define ResultField 	21

#define SINE 			22
#define DEBUG 			23



//Button Structure initialisation
const button_s button[] = {
		//Buttons
		{(uint8_t *)"0",	{0,		64,		192, 	240},	(uint8_t *)&font24,	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"1",	{0,		64,		144,	192},	(uint8_t *)&font24,	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"2",	{64,	128,	144,	192},	(uint8_t *)&font24,	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"3",	{128,	192,	144,	192},	(uint8_t *)&font24,	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"4",	{0,		64,		96,		144},	(uint8_t *)&font24,	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"5",	{64,	128,	96,		144},	(uint8_t *)&font24,	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"6",	{128,	192,	96,		144},	(uint8_t *)&font24,	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"7",	{0,		64,		48,		96 },	(uint8_t *)&font24,	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"8",	{64,	128,	48,		96 },	(uint8_t *)&font24,	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"9",	{128,	192,	48,		96 },	(uint8_t *)&font24,	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)".",	{64,	128,	192,	240},	(uint8_t *)&font24,	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},

		//Operators
		{(uint8_t *)"+/-",	{128,	192,	192,	240},	(uint8_t *)&font24,	LCD_COLOR_WHITE,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"+",	{192,	256,	96,		144},	(uint8_t *)&font24,	LCD_COLOR_GREEN,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Add},
		{(uint8_t *)"-",	{256,	320,	96,		144},	(uint8_t *)&font24,	LCD_COLOR_GREEN,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12}, 	&Calc_Sub},
		{(uint8_t *)"X",	{192,	256,	48,		96 },	(uint8_t *)&font24,	LCD_COLOR_GREEN,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Mul},
		{(uint8_t *)"/",	{256,	320,	48,		96 },	(uint8_t *)&font24,	LCD_COLOR_GREEN,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12}, 	&Calc_Div},
		{(uint8_t *)"%",	{192,	256,	144,	192},	(uint8_t *)&font24,	LCD_COLOR_GREEN,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Mod},
		{(uint8_t *)"=",	{192,	256,	192,	240},	(uint8_t *)&font24,	LCD_COLOR_GREEN,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},
		{(uint8_t *)"C",	{256,	320,	144,	192},	(uint8_t *)&font24,	LCD_COLOR_GREEN,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12}, 	&Calc_0},
		{(uint8_t *)"AC",	{256,	320,	192,	240},	(uint8_t *)&font24,	LCD_COLOR_GREEN,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_0},


		//Answer Section
		{(uint8_t *)"Opp",	{0,		64,	     0,		48 },	(uint8_t *)&font24,	LCD_COLOR_BLACK,  LCD_COLOR_WHITE,	CENTER_MODE,	{-32, 12},	&Calc_0},
		{(uint8_t *)"Res",	{64,	192,	 0,		48 },	(uint8_t *)&font24,	LCD_COLOR_BLACK,  LCD_COLOR_WHITE,	RIGHT_MODE,		{0, 12},	&Calc_0},

		//Sin
		{(uint8_t *)"sin",	{256,	320,	 0,		48 },	(uint8_t *)&font24,	LCD_COLOR_GREEN,  LCD_COLOR_BLACK,	CENTER_MODE,	{0, 12},	&Calc_Sin},

		//Debug
		{(uint8_t *)"DBG",	{192,	256,	 0,		48 },	(uint8_t *)&font24,	LCD_COLOR_RED,  LCD_COLOR_WHITE,	CENTER_MODE,	{0, 12},	&Calc_0},

		//End of Structure
		{NULL,	{0,		0,		0,		0},		NULL,	(int32_t)NULL, (int32_t)NULL,	(Line_ModeTypdef)NULL,	{0, 0}, NULL}
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
	BSP_LCD_CLEAR(LCD_COLOR_BLACK);


	//Display and Debounce Post Calibration
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_Setfont((sFONT*)&font24);
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


void CalculatorProcess(void)
{
	// Initialises all initial variables
	int8_t Button = -1;
	static uint8_t decimalRepeat =  0; 	//Flags if decimal point is pressed, prevents repeats
	static uint8_t preCo = 0;
	static uint8_t input[LIMIT]; 		//Temporary input value store
	static uint8_t Result[LIMIT];		//Result Storage
	static uint8_t count = 0;			//Count through input array
	static uint8_t operator = -1;		//Storage of last operator pressed
	static uint8_t resultFlag =0;		//Flags if there's a result stored
	float negate;						//Holds a float to negate a string number

	// If a screen is pressed
	if (BSP_TP_GetDisplayPoint(&display) == 0)
	{
		//Find which button
		 Button = buttonNum(display.x,display.y);

		 //if debug, ignore everything else
		 if (Button >= DEBUG)
		 {
			 Calc_Debug();
		 }

		 //Sine works differently
		 else if (Button == SINE)
		 {
	 		 if(Debug == 1)
			 {
				 printf("Button Press: %s\n\r", button[Button].display);
			 }

	 		 resultFlag = 0;

		 }


		 else
		 {
			 switch(resultFlag)										 // checks resultFlag against all posibilities shown below
			 {
				 case 0:										 // Case=0 when no button has been pressed yet

					 if(Button <= DECIMALPOINT)							 // checks whether a number button has been pressed and stores it as arg 1
					 {
						 if(Debug == 1)
						 {
							 printf("Button Press: %s\n\r", button[Button].display);
						 }

						 if(decimalRepeat == 1 && Button == DECIMALPOINT)
						 {
							 //decimal point has been pressed twice, check for next operator
						 }
						 else if(Button == DECIMALPOINT) //Decimal Pressed
						 {
							 decimalRepeat = 1;
							 input[count] = button[Button].display[0]; 	                // Stores argument 1
							 PrintString(input, ResultField);                           // and prints it to the screen
							 count++;
						 }
						 else
						 {

							 input[count] = button[Button].display[0]; 	// Stores argument 1
							 PrintString(input, ResultField);								// and prints it to the screen
							 count++;
						 }
						resultFlag = 0; 															// remain in arg1 update case
					 }
					 else if(Button >= 11 && Button < 20)									// checks on whether an operator has been checked
					 {
						 //If debugging is activated, display the button that was pressed
						 if(Debug == 1)
						 {
							 printf("Button Press: %s\n\r", button[Button].display);
						 }

						 if(Button != NEGATE)
						 {
							 decimalRepeat = 0;
						 }
						//Can only leave resultFlag 0 if a operator is pressed (X / + - %) and Arguments have been entered in input
						 if(count != 0 && Button != EQUALS && Button != ALLCLEAR && Button != CLEAR && Button != NEGATE){

						 //Terimate the input string with a null and reset the counter before leaving
							 //Debugging
							 if(Debug == 1)
							 {
								 printf("Case 0: Operator has been pressed\n\r");
							 }
							 input[count] = '\0';
							 count =0;
							 //Update Result Argument before leaving
							 strcpy((char*)Result,(char*)input);
							 //Value has been copied to Result argument, clear the  inputer
							 ArrayClear(input);
							 operator = Button;
							 PrintString(button[operator].display, OPERATOR);
							 resultFlag = 1;
						 }
						 else if(Button == NEGATE)
						 {
							//negate the input String
							 negate = -1*atof((char *)input);
							 sprintf((char *)input, "%g", negate);
							 PrintString(input, ResultField);
							 count++;
							 resultFlag = 0;
						 }
						 //No argument has been entered therefore wait before leaving initial resultFlag
						else if( Button != ALLCLEAR || Button != CLEAR){

							count = 0;
							ArrayClear(input);
							PrintString(input, ResultField);
							ClearDisplay(OPERATOR);
							decimalRepeat = 0;
							resultFlag = 0;
						}
						 //No argument has been entered therefore wait before leaving initial resultFlag
						else{
							resultFlag = 0;
						}
					 }

					 else		 //result area was pressed do nothing no button was found
					 {
								 //printf("PRESSED IN RESULT\n\r");//debug
						 resultFlag = 0;
					 }
					 break;
				 case 1://Result holds an argument

					 if(Button < 11)
					 {
						 //Debugging
						 if(Debug == 1)
						 {
							 printf("Button Press: %s\n\r", button[Button].display);
						 }

						 if(preCo == 1)
						 {
							 ArrayClear(input);
							 count = 0;
							 preCo = 0;
						 }
						 //if number is pressed update argument 1
						 if(decimalRepeat == 1 && Button == DECIMALPOINT)
						 {
							 //do nothing
						 }
						 else if(Button == DECIMALPOINT)
						 {
							 input[count] = button[Button].display[0];
							 PrintString(input, ResultField);//*function* print in result pannel
							 PrintString(button[operator].display, OPERATOR);//*function* print in result pannel
							 decimalRepeat = 1;
							 count++;
						 }
						 else
						 {
							 input[count] = button[Button].display[0];
							 PrintString(input, ResultField);//*function* print in result pannel
							 PrintString(button[operator].display, OPERATOR);//*function* print in result pannel
							 count++;
						 }
						 resultFlag = 1; // remain in arg1 update case
					 }
					 else if(Button >= 11 && Button < 20)
					 {
						 //Debugging
						 if(Debug == 1)
						 {
							 printf("Button Press: %s\n\r", button[Button].display);
						 }

						 if(Button != NEGATE)
						 {
							 decimalRepeat = 0;
						 }
						//Can only leave resultFlag 1 if a operator is pressed (X / + - %) and Arguments have been entered in input
						 if(count != 0 && Button != EQUALS && Button != ALLCLEAR && Button != CLEAR && Button != NEGATE && Button != SINE){
						 //Terminate the input string with a null and reset the counter before leaving
							 if(Debug == 1)
							 {
								 printf("Case 1: Operator has been pressed\n\r");
							 }
							 input[count] = '\0';
							 count =0;
							 //Update Result Before updating command
							 //Calculation completed
							 if(preCo == 0){ //do a normal calculation
								 if(Debug == 1)
								 {
									printf("%s %s %s = ",Result,button[operator].display, input);
								 }

								 sprintf((char *)Result, "%g", (float)(*button[operator].operatorFunc)(Result, input));

								 //Debugging
								 if(Debug == 1)
								 {
									 printf("%s\n\r", Result);
								 }
							 }
							 else{
								//Because we are coming back from the repeated equals operator, dont do another calculation but clear string instead
								ArrayClear(input);
								count = 0;
								preCo = 0; //Set the equals flag to zero so next return does a normal calculation
							 }
							 //Update command entered
							 operator = Button;
							 PrintString(button[operator].display, OPERATOR);
							 //CLEAR the previous value
							 ArrayClear(input);
							 PrintString(Result, ResultField);
							 resultFlag = 1;
							 }
							 else if(Button == NEGATE)
							 {
								//negate the input String
								 negate = -1*atof((char *)Result);
								 sprintf((char *)Result, "%g", negate);
								 PrintString(Result, ResultField);
								 resultFlag = 1;
							 }
							 //ALLCLEAR has been pressed
							 else if(Button == EQUALS){


								 //Debugging
								 if(Debug == 1)
								 {
									 //Result String
									 printf("%s %s %s = ",Result,button[operator].display, input);
								 }

								 //Repeat the previous calculation
								 sprintf((char *)Result, "%g", (float)(*button[operator].operatorFunc)(Result, input));

								 //Debugging
								 if(Debug == 1)
								 {
									 printf("%s\n\r", Result);
								 }
								 PrintString(Result, ResultField);
								 decimalRepeat = 0;
								 preCo = 1;
								 resultFlag = 1;
							 }

							else if( Button == ALLCLEAR){

								count = 0;
								ArrayClear(input);
								ArrayClear(Result);
								PrintString(input, ResultField);
								ClearDisplay(OPERATOR);
								decimalRepeat = 0;
								resultFlag = 0;
							}
							//CLEAR Button have been pressed
							else if(Button == CLEAR){
								 //Debugging
								 if(Debug == 1)
								 {
									 printf("Case 1: CLEAR has been pressed\n\r");
								 }
								ArrayClear(input);
								PrintString(input, ResultField);
								count = 0;
								decimalRepeat = 0;
								resultFlag = 1;
							}
							 //No argument has been entered therefore wait before leaving initial resultFlag
							else{
								resultFlag = 1;
							}
					 }
					 else//result area was pressed do nothing no button was found
					 {
						resultFlag = 1;
					 }
					 break;

				  default:
					 //Do nothing
					 break;
			 }
		 }
	}

}


/*
 * Function: buttonNum
 * ----------------------------
 *
 * Finds which button is being pressed
 * Returns Integer Corresponding to Button
 *
 */

int8_t buttonNum(uint16_t xPosi, uint16_t yPosi){
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
void ButtonDisplay(uint8_t buttonNum, uint8_t indent){

	//Fill Rectangle
	if(Indent){
		BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	}
	else{
		BSP_LCD_SetTextColor(button[DbuttonNum.colour);
	}
	BSP_LCD_FillRect(button[buttonNum].co_ord[0],button[buttonNum].co_ord[2],
			button[buttonNum].co_ord[1]-button[buttonNum].co_ord[0],button[buttonNum].co_ord[3]-button[buttonNum].co_ord[2]);

	//Draw outlines
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawRect(button[buttonNum].co_ord[0],button[buttonNum].co_ord[2],
			button[buttonNum].co_ord[1]-button[buttonNum].co_ord[0],button[buttonNum].co_ord[3]-button[buttonNum].co_ord[2]);

	//Insert String
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

	if(Indent){
		BSP_LCD_SetBackColor(LCD_COLOR_GRAY);
	}
	else{
		BSP_LCD_SetBackColor(button[buttonNum].colour);
	}

	BSP_LCD_Setfont((sFONT*)button[buttonNum].font);
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
	BSP_LCD_Setfont((sFONT *)button[Button].font);
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
 * Function: Calc_0
 * ----------------------------
 * Does nothing and returns nothing.
 * Occurs every time a button is pressed that requires
 * no immediate calculation
 */
float Calc_0(uint8_t *arg1, uint8_t *arg2)
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
	return sin((atof((char*)arg1))*3.14159265/180);
}

/*
 * Function: Calc_Debug
 * ----------------------------
 * Indents Debug
 *
 */
float Calc_Debug()
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

	return 0;
};
