#include "Ass-02.h"
#include "usart.h"

volatile uint8_t Debug = 0;

/*
 * STRUCTURE CONTAINING ALL POSSIBLE ACCEPTED COMMANDS
 */
const command_s CommandList[] =
{
		{(int8_t *)"add", 	&Ser_Add, 	(int8_t *)"add <num_1> +...+ <num_n> returns sum of all entered numbers"},
		{(int8_t *)"+", 	&Ser_Add, 	(int8_t *)"+ <num_1> +...+ <num_n> returns sum of all entered numbers"},
		{(int8_t *)"sub", 	&Ser_Sub, 	(int8_t *) "sub <num_1> -...- <num_n> subtracts any entered numbers from first number"},
		{(int8_t *)"-", 	&Ser_Sub, 	(int8_t *) "- <num_1> -...- <num_n> subtracts any entered numbers from first number"},
		{(int8_t *)"mul", 	&Ser_Mul, 	(int8_t *)"mul <num_1> *...* <num_n> returns product of all entered numbers"},
		{(int8_t *)"*", 	&Ser_Mul, 	(int8_t *)"* <num_1> *...* <num_n> returns product of all entered numbers"},
		{(int8_t *)"div", 	&Ser_Div, 	(int8_t *) "div <num_1> /<num_2> returns num 1 divided by num 2"},
		{(int8_t *)"/", 	&Ser_Div, 	(int8_t *) "/ <num_1> /<num_2> returns num 1 divided by num 2"},
		{(int8_t *)"help", 	&Ser_Help, 	(int8_t *)"help [command]: Prints help information for a command"},
		{(int8_t *)"debug", &Ser_Debug, (int8_t *)"debug <on|off>"},
		{(int8_t *)"clear", &Ser_Clear, (int8_t *)"clears the terminal window"},
		{(int8_t *)"sin", 	&Ser_Sin, 	(int8_t *)"sin <num_1> returns the value of sine(num_1 deg)"},
		{(int8_t *)"cos", 	&Ser_Cos, 	(int8_t *)"cos <num_1> returns the value of cosine(num_1 deg)"},
		{(int8_t *)"tan", 	&Ser_Tan, 	(int8_t *)"tan <num_1> returns the value of tan(num_1 deg)"},
		{NULL, NULL, NULL}
};




/*
 * FUNCTION: COMMANDLINEPARSERINIT
 * PURPOSE:  INITIALISES THE PARSER
 * INPUTS:   NOTHING
 * OUTPUTS:  NOTHING
 */
void CommandLineParserInit(void)
{
  // Print welcome message
  printf("\014");
  printf("ELEC3730 Assignment 2\n\r");
  printf("Zach Honan and Nic Rodgers - c3206664 and c3206083\n\r");

  return;

}

/*
 * FUNCTION: COMMANDLINEPARSERPROCESS
 * PURPOSE:  TAKES THE INPUT FROM PUTTY AND TURNS IT INTO INDIVIDUAL STRINGS
 * INPUTS:   NOTHING
 * OUTPUTS:  THE STRINGS ARE SAVED INTO THE DOUPLE POINTER: ARRAY_OF_WORDS
 */
void CommandLineParserProcess(void)
{
  uint8_t c; 								//Holds the current input from the uartBuffer, awaiting for further process
  static uint8_t Arr_Of_Chars[LIMIT]; 		//Holds the complete string of input from the serial communication
  static uint8_t i = 0; 					//Used to increment how many times a user has interface with the command line up until a enter command
  uint8_t j, count; 						//Variables used to evaluate the command line input
  uint8_t **array_of_words_p; 				//Pointer to a array which holds pointers to strings

  // Check for input and echo back
  if (HAL_UART_Receive(&huart2, &c, 1, 0x0) == HAL_OK)
  {
	//Echo to PUTTY and toggle LED
    printf("%c", c);
    HAL_GPIO_TogglePin(GPIOD, LD4_Pin); // Toggle LED4

    //Check that the current input Character isn't enter and that the buffer limit hasn't been exceeded
    if(c != 13 && i<100){
    	//All conditions are fine
    	Arr_Of_Chars[i]= c; //Load the character into the input string if not enter
    	i++; //increment the counter
    }
    else{
    	//Either Overflow of data or Enter was pressed
    	if(i == 100){
    		//Overflow has occurred, continue process with this string size
    		printf("\nError to many characters entered in command line\n\r");
    	}
    	//Proceed and terminate string with a null character
    	Arr_Of_Chars[i]='\0';
    	i = 0; //start from beginning again

    	//Now handle the input string and print the results
    	count = string_parser(Arr_Of_Chars, &array_of_words_p);

    	if (Debug == 1)
    	{
    		 printf("\nThe input string was '%s'\n\r",Arr_Of_Chars);
    		 //Print the number of arguments entered
    		 printf("--> count = %d\r\n", count);
    	}

    	if(count != 0){

    		if (Debug == 1)
    		{
				//Print out the individual words if arguments entered is larger than 0
				for (j=0;j<count;j++)
				{
				  printf("---> %2d: '%s'\r\n", j+1, (array_of_words_p)[j]);
				}
    		}

    		//**********************************************************************//
    		//Find out which command was entered and do calculation
        	for(j=0; CommandList[j].NameString != NULL; j++){
    			if(strcasecmp((char *)array_of_words_p[0],(char *) CommandList[j].NameString) == 0){
        			//Now do the correct operation based on the match
        			(*CommandList[j].Function_p)(count, array_of_words_p);
        			break;
    			}
        	}
        	if(CommandList[j].NameString == NULL){
        		printf("\nInput not recognised, please enter as follows:\n\r");
        		Ser_Help(1,"");
        	}

        	//Free memory after the calculation process has occurred
         	free(array_of_words_p[0]);
         	free(array_of_words_p);
		}
		else{
			//Let the user know that they must input commands
			printf("No arguments where entered, please enter as follows:\n\r");
        	Ser_Help(1,"");
		}

    }

  }

  return;
}

/*
 * FUNCTION: COMMANDLINEPARSERPROCESS
 * PURPOSE:  COUNTS THE NUMBER OF WORDS/NUMBERS AND RETURNS THEM INDIVIDUALLY
 * INPUTS:   ARRAY OF WORDS AND THE INPUT
 * OUTPUTS:  NUMBER OF WORDS
 */
uint8_t string_parser(char *inp, char **array_of_words_p[])
{
	uint8_t count = 0;														//word count
	uint8_t i = 0;															//character count
	char *inp_copy = malloc(strlen(inp)+1);									//allocate memory for input copy

	strcpy(inp_copy,inp);													//copy input string

	//find how many words and allocate memory
	//loop for entire input string (until EOF is found)
	while (inp[i]!= 0)
	{

		//finds first non-space character
		while(inp[i] == ' ')
		{
			i++;
		}

		//finds end of word (either space or NULL)
		while(inp[i] != ' ' && inp[i] != 0)
		{
			i++;
		}

		//increment word count
		count++;

	}


	//allocate memory for word strings
	(*array_of_words_p)= malloc((count) * sizeof(char *));

	i=0;									//reset variables
	count=0;


	//loop again to store locations of words in array_of_words
	//loop for entire input string (until EOF is found)
	while (inp_copy[i] != 0)
	{

		//replace all strings with NULL's
		while(inp_copy[i] ==' ' && inp_copy[i] != 0)
		{
			inp_copy[i] = 0; //Add null to end of word string
			i++;
		}

		//check if EOF, if not, start of word is found. store location and increment count
		if (inp_copy[i] != 0)
		{
			(*array_of_words_p)[count] = &inp_copy[i];
			count++;
		}

		//finds end of word (either space or NULL)
		while(inp_copy[i] != ' ' && inp_copy[i] != 0)
		{
			i++;
		}

	}


	return count;
}



/*
 * FUNCTION: CLEAR
 * PURPOSE:  CLEARS THE SERIAL PORT ON PUTTY
 * INPUTS:   NUMBER OF ARGUMENTS AND THE ARGUMENTS THEMSELVES
 * OUTPUTS:  NOTHING
 */
void Ser_Clear(uint8_t Argument_Num, uint8_t *Arg_Strings[]){

	CommandLineParserInit();

}

/*
 * FUNCTION: ADD
 * PURPOSE:  ADDS THE TWO VALUES STORED IN THE ARG_STRINGS
 * INPUTS:   NUMBER OF ARGUMENTS AND THE ARGUMENTS THEMSELVES
 * OUTPUTS:  THE RESULT OF THE SUM SAVED IN THE rslt VARIABLE
 */
float Ser_Add(uint8_t Argument_Num, uint8_t *Arg_Strings[])
{
	float rslt = 0;
	int8_t err = 0;
	uint8_t i, j;
	if(Argument_Num > 2){
		for(i=1; i<Argument_Num; i++){
			//Loop through each input string until NULL terminator is reached
			for(j = 0; Arg_Strings[i][j] != '\0'; j++)
			{


				if(Arg_Strings[i][j] < 46 || Arg_Strings[i][j] > 57 || Arg_Strings[i][j] == 47)
				{
					//Character in the string was found to contain a Number character ASCII value
					//Report error and break out of loop
					printf("ERROR: Non-number in argument %i\n\r", i);
					printf("Interpreted Value: %g\n\r", atof((char*)Arg_Strings[i]));
					err = 1;
					break;
				}


			}

			rslt += atof((char*)Arg_Strings[i]);

		}
		if(err == 1)
		{
			printf("Possible result = %g\n\r",rslt);
			err = 0;
		}
		else
		{
			printf("result = %g\n\r",rslt);
		}
	}
	else{
		printf("At least 1 input required for Addition function,\n\r");
		printf("type: 'help add' for more info\n\r");
	}

	return rslt;
}




/*
 * FUNCTION: SUB
 * PURPOSE:  SUBTRACTS THE TWO VALUES STORED IN THE ARG_STRINGS
 * INPUTS:   NUMBER OF ARGUMENTS AND THE ARGUMENTS THEMSELVES
 * OUTPUTS:  THE DIFFERENCE OF THE VARIABLES SAVED IN THE rslt VARIABLE
 */
float Ser_Sub(uint8_t Argument_Num, uint8_t *Arg_Strings[])
{

	uint8_t i, j;
	float rslt = atof((char*)Arg_Strings[1]);
	int8_t err = 0;

	//Checks correct number of arguments have been entered
	if(Argument_Num > 2){
		for(i=1; i<Argument_Num; i++)
		{

			//Loop through each input string until NULL terminator is reached
			for(j = 0; Arg_Strings[i][j] != '\0'; j++)
			{



				if(Arg_Strings[i][j] < 46 || Arg_Strings[i][j] > 57 || Arg_Strings[i][j] == 47)
				{
					//Character in the string was found to contain a Number character ASCII value
					//Report error and break out of loop
					printf("ERROR: Non-number in argument %i\n\r", i);
					printf("Interpreted Value: %g\n\r", atof((char*)Arg_Strings[i]));
					err = 1;
					break;
				}
			}

			if(i > 1)
			{
				rslt -= atof((char*)Arg_Strings[i]);
			}

		}
		if(err == 1)
		{
			printf("Possible result = %g\n\r",rslt);
			err = 0;
		}
		else
		{
			printf("result = %g\n\r",rslt);
		}
	}
	else{
		printf("At least 1 input required for Subtract function,\n\r");
		printf("type: 'help sub' for more info\n\r");
	}

	return rslt;
}

/*
 * FUNCTION: MUL
 * PURPOSE:  MULTIPLIES THE TWO VALUES STORED IN THE ARG_STRINGS
 * INPUTS:   NUMBER OF ARGUMENTS AND THE ARGUMENTS THEMSELVES
 * OUTPUTS:  THE RESULT OF THE MULTIPLIED VARIABLES SAVED IN THE rslt VARIABLE
 */
float Ser_Mul(uint8_t Argument_Num, uint8_t *Arg_Strings[])
{

	float rslt = 1;
	int8_t err = 0;
	uint8_t i, j;

	if(Argument_Num > 2){


		for(i=1; i<Argument_Num; i++){

			//Loop through each input string until NULL terminator is reached
			for(j = 0; Arg_Strings[i][j] != '\0'; j++)
			{


				if(Arg_Strings[i][j] < 46 || Arg_Strings[i][j] > 57 || Arg_Strings[i][j]==47)
				{
					//Character in the string was found to contain a Number character ASCII value
					//Report error and break out of loop
					printf("ERROR: Non-number in argument %i\n\r", i);
					printf("Interpreted Value: %g\n\r", atof((char*)Arg_Strings[i]));
					err = 1;
					break;
				}

			}

			rslt *= atof((char*)Arg_Strings[i]);

		}
		if(err)
		{
			printf("Possible result = %g\n\r",rslt);
			err = 0;
		}
		else
		{
			printf("result = %g\n\r",rslt);
		}
	}
	else{
		printf("At least 1 input required for Multiply function,\n\r");
		printf("type: 'help mul' for more info\n\r");
	}

	return rslt;
}

/*
 * FUNCTION: DIV
 * PURPOSE:  DIVIDES THE TWO VALUES STORED IN THE ARG_STRINGS
 * INPUTS:   NUMBER OF ARGUMENTS AND THE ARGUMENTS THEMSELVES
 * OUTPUTS:  THE DIVISION OF THE TWO SAVED IN THE rslt VARIABLE
 */
float Ser_Div(uint8_t Argument_Num, uint8_t *Arg_Strings[])
{
	float rslt = 0;
	uint8_t i,j;
	int8_t err = 0;

	if(Argument_Num == 3){ //Correct number of arguments have been entered for the divide function
		for(i=1; i<Argument_Num; i++){

			//Loop through each input string until NULL terminator is reached
			for(j = 0; Arg_Strings[i][j] != '\0'; j++)
			{



				//Check each character in the string is a ASCII CODE for a number
				if(Arg_Strings[i][j] < 46 || Arg_Strings[i][j] > 57 || Arg_Strings[i][j] == 47)
				{
					//Character in the string was found to contain a Number character ASCII value
					//Report error and break out of loop
					printf("ERROR: Non-number in argument %i\n\r", i);
					printf("Interpreted Value: %g\n\r", atof((char*)Arg_Strings[i]));
					err = 1;
					break;
				}
			}

			//Do the calculation
			rslt = atof((char*)Arg_Strings[1])/atof((char*)Arg_Strings[2]);

		}
		if(err)
		{
			printf("Possible result = %g\n\r", rslt);
			err = 0;
		}
		else
		{
			printf("result = %g\n\r", rslt);
		}
	}
	else{
		printf("Only 2 inputs allowed for Division function,\n\r");
		printf("type: 'help div' for more info\n\r");
	}

	return rslt;
}

/*
 * FUNCTION: SIN
 * PURPOSE:  FINDS THE SINE RATIO OF THE FIRST VARIABLE STORED IN ARG_STRINGS
 * INPUTS:   NUMBER OF ARGUMENTS AND THE ARGUMENTS THEMSELVES
 * OUTPUTS:  SINE RATIO STORED IN rslt VARIABLE
 */
float Ser_Sin(uint8_t Argument_Num, uint8_t *Arg_Strings[]){
	float rslt=0,Read_Val;
	if(Argument_Num == 2)
	{
		Read_Val=atof((char*)Arg_Strings[1]);
		rslt = sin(Read_Val*(3.14159265/180));
		printf("result = %g\n\r",rslt);
	}
	else
		{
			if (Argument_Num < 2)
			{
				printf("Need at least 1 input for Sine function\n\r");
			}
			else
			{
				printf("Too many inputs for Sine function\n");
			}
			printf("type: 'help sin' for more info\n\r");
		}

	return rslt;
}

/*
 * FUNCTION: COS
 * PURPOSE:  FINDS THE COSINE RATIO OF THE FIRST VARIABLE STORED IN ARG_STRINGS
 * INPUTS:   NUMBER OF ARGUMENTS AND THE ARGUMENTS THEMSELVES
 * OUTPUTS:  COSINE RATIO STORED IN rslt VARIABLE
 */
float Ser_Cos(uint8_t Argument_Num, uint8_t *Arg_Strings[]){
	float rslt=0,Read_Val;
	if(Argument_Num == 2)
	{
		Read_Val=atof((char*)Arg_Strings[1]);
		rslt = cos(Read_Val*(3.14159265/180));
		printf("result = %g\n\r",rslt);
	}
	else
		{
			if (Argument_Num < 2)
			{
				printf("Need at least 1 input for Cosine function\n\r");
			}
			else
			{
				printf("Too many inputs for Cosine function\n");
			}
			printf("type: 'help cos' for more info\n\r");
		}

	return rslt;
}

/*
 * FUNCTION: TAN
 * PURPOSE:  FINDS THE TAN RATIO OF THE FIRST VARIABLE STORED IN ARG_STRINGS
 * INPUTS:   NUMBER OF ARGUMENTS AND THE ARGUMENTS THEMSELVES
 * OUTPUTS:  TAN RATIO STORED IN rslt VARIABLE
 */
float Ser_Tan(uint8_t Argument_Num, uint8_t *Arg_Strings[])
{
	float rslt=0, Read_Val;
	if(Argument_Num == 2)
	{
		Read_Val=(atof((char*)Arg_Strings[1]));
		rslt = tan(Read_Val*(3.14159265/180));
		printf("result = %g\n\r",rslt);
	}
	else
		{
			if (Argument_Num < 2)
			{
				printf("Need at least 1 input for Tangent function\n\r");
			}
			else
			{
				printf("Too many inputs for Tangent function\n");
			}
			printf("type: 'help tan' for more info\n\r");
		}

	return rslt;
}

/*
 * FUNCTION: HELP
 * PURPOSE:  PROVIDES A HELP MENU ON PUTTY
 * INPUTS:   NUMBER OF ARGUMENTS AND THE ARGUMENTS THEMSELVES
 * OUTPUTS:  NOTHING
 */
void Ser_Help(uint8_t Argument_Num, uint8_t *Arg_Strings[])
{
	uint8_t j,i;

	printf("\tCommand\tHelp\n\r");

	if(Argument_Num == 2){

		//Prints help on entered command
		for(i=1; i<Argument_Num;i++){

			//Loop through all the functions and find which function string matches the entered input string
			for(j=0;CommandList[j].NameString != NULL; j++){

				if(strcasecmp((char *)Arg_Strings[i],(char *) CommandList[j].NameString) == 0){

					printf("%s\n\r",(char *) CommandList[j].HelpString);
					return;

				}
			}
		}
	}

	//Loop through all the arguments and print there corresponding help strings
	for(i = 0; CommandList[i].NameString != 0;i++){

		printf("\t%s\t%s\n\r", CommandList[i].NameString, CommandList[i].HelpString);
	}



	return;
}

/*
 * FUNCTION: DEBUG
 * PURPOSE:  PROVIDES FEEDBACK FROM EVERY STEP OF THE CODE, ALLOWING
 * 			 FOR MORE EASY DEBUGGING
 * INPUTS:   NUMBER OF ARGUMENTS AND THE ARGUMENTS THEMSELVES
 * OUTPUTS:  PRINTS THE STEPS OF CODE ONTO PUTTY
 */
void Ser_Debug(uint8_t Argument_Num, uint8_t *Arg_Strings[]){
	//Check that only 2 arguments are entered
	if(Argument_Num >2){
		printf("Too many arguments entered for the debug function,\r\ntype 'help debug' for help\r\n");
	}
	else if(Argument_Num>1){
		//Correct amount of arguments have been entered, determine which state to toggle too
		//Check the input String, to determine which State to toggle Debug_State to
		if(strcasecmp((char *)Arg_Strings[1],"On")==0){

			if(Debug == 1)
			{
				printf("Debug is already ON\n\r");
			}
			else
			{
				printf("Debug has been turned ON\n\r");
				Debug = 1;
			}
		}
		else if(strcasecmp((char *)Arg_Strings[1],"Off")==0){
			if(Debug == 0)
			{
				printf("Debug is already OFF\n\r");
			}
			else
			{
				printf("Debug has been turned OFF\n\r");
				Debug = 0;
			}
		}
		else{
			printf("Input argument not recognised,\r\ntype 'help debug' for help\r\n");
		}
	}
	else{
		if(Debug == 1)
		{
			printf("Debug is ON\n\r");
		}
		else if(Debug == 0)
		{
			printf("Debug is OFF\n\r");
		}
	}

	return;
}
