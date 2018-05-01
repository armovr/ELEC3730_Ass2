//     $Date: 2017-04-04 04:00:13 +1000 (Tue, 04 Apr 2017) $
// $Revision: 872 $
//   $Author: Peter $

#include "Ass-02.h"
#include "usart.h"
//
// REPLACE THE EXAMPLE CODE WITH YOUR CODE
//Initialise the Command List using the Structure type of command_s



const command_s CommandList[] = {
		{(int8_t *)"add", &Add_Function, (int8_t *)"add <num_1> +...+ <num_n>"},
		{(int8_t *)"sub", &Sub_Function, (int8_t *) "sub <num_1> -...- <num_n>"},
		{(int8_t *)"mul", &Mul_Function, (int8_t *)"mul <num_1> *...* <num_n>"},
		{(int8_t *)"div", &Div_Function, (int8_t *) "div <num_1> /<num_2>"},
		{(int8_t *)"help", &Help_Function, (int8_t *)"help [command]: Prints help information for a command"},
		{(int8_t *)"debug", &Debug_Function, (int8_t *)"debug <on|off>"},
		{(int8_t *)"clear", &Clear_Function, (int8_t *)"clears the terminal window"},
		{(int8_t *)"clc", &Clear_Function, (int8_t *)"clears the terminal window"},
		{NULL, NULL, NULL}
};

/*
 * Function: Add_Function
 * ----------------------------
 *   Returns the Add of all the arguments passed into the function
 *
 *	ArgNum = number of arguments expected for calculation
 *	*ArgString[] = array of pointers to the start of the argument wordsdebug
 *
 */
int8_t Clear_Function(uint8_t ArgNum, uint8_t *ArgStrings[]){
	//printf("IN the Clear function\n\r");
	printf("\014");
	printf("ELEC3730 Assignment 2\n\r");
	return -1;

}




/*
 * Function: Add_Function
 * ----------------------------
 *   Returns the Add of all the arguments passed into the function
 *
 *	ArgNum = number of arguments expected for calculation
 *	*ArgString[] = array of pointers to the start of the argument words
 *
 */
int8_t Add_Function(uint8_t ArgNum, uint8_t *ArgStrings[]){
	float result=0;
	uint8_t i;
	//printf("IN the ADD function\n\r");
	if(ArgNum > 2){
		for(i = 1; i<ArgNum; i++){
			//Convert the input the string to a float and add to result
			result += atof((char*)ArgStrings[i]);
		}
		printf("Result = %g\n\r",result);
	}
	else{
		//No enough arguments have been entered
		printf("Not enough arguments have been entered for the add function,\n\renter 'add help' for help\n\r");
	}

	return -1;

}


/*
 * Function: Sub_Function
 * ----------------------------
  *	Calculates the Subtraction between String A - String B  - ...- String N
 *
 *	Returns -1
 *
 *	INPUTS:
 *	ArgNum =number of arguments expected for calculation
 *	*ArgString[] = array of pointers to the start of the argument words
 *
 */
int8_t Sub_Function(uint8_t ArgNum, uint8_t *ArgStrings[]){
	float result = 0;
	uint8_t i;
	//printf("IN the Sub function\n\r");
	if(ArgNum > 2){
		//Checks correct number of arguments have been entered
		result = atof((char*)ArgStrings[1]);
		for(i = 2; i<ArgNum; i++){
			result = result - atof((char*)ArgStrings[i]);
		}
		printf("Result = %g\n\r",result);
	}
	else{
		printf("Not enough arguments have been entered for the sub function,\n\renter 'help sub' for help\n\r");
	}

	return -1;

}

/*
 * Function: Mul_Function
 * ----------------------------
 *	Calculates the Multiplication between String A * String B  * ...* String N
 *	Returns -1
 *
 *	INPUTS:
 *	ArgNum =number of arguments expected for calculation
 *	*ArgString[] = array of pointers to the start of the argument words
 *
 */
int8_t Mul_Function(uint8_t ArgNum, uint8_t *ArgStrings[]){
	float result = 1;
	int8_t ERR = 0;
	uint8_t i, j;
	//printf("IN the Mul function\n\r");
	if(ArgNum>2){
		for(i=1; i<ArgNum; i++){
			result *= atof((char*)ArgStrings[i]);
			j = 0;
			while(ArgStrings[i][j] != '\0')
			{
				if (Debug==1)
				{
					printf("arg %i\n\r", ArgStrings[i][j]);
				}
				/*
				  THIS FUNCTION ACCEPTS ALL NUMBERS AND THE CHARACTERS OF "." AND "/"
				  WE SHOULD MAKE IT TO NOT TAKE IN "/"
				*/
				if(ArgStrings[i][j] < 46 || ArgStrings[i][j] > 57 || ArgStrings[i][j]==47)
				{

					printf("ERROR: Operator Expects number in arg %i\n\r", i);
					printf("Interpreted Value: %g\n\r", atof((char*)ArgStrings[i]));
					ERR = 1;
					break;
				}
				/*float Reslt=atof((char*)ArgStrings[i]);
				if (Reslt==0)
				{
					printf("Error Within Inputs, two numbers expected\n\r");
					ERR=1;
					break;
				}
				else
				{
					if (Reslt!=ArgStrings[i][j])
					{
						printf("Result = %g\n\r", result);
						break;
					}

				}
				*/

				j++;
			}
		}
		if(ERR == 1)
		{
			printf("Possible Result from interpreted arguments : %g\n\r",result);
			ERR = 0;
		}
		else
		{
			printf("Result = %g\n\r",result);
		}
	}
	else{
		printf("Not enough arguments entered for the mul function,\n\r enter 'help mul' for help\n\r");
	}

	return -1;
}






/*
 * Function: Div_Function
 * ----------------------------
 *	Calculates the Division of String A and String B
 *	Returns -1
 *
 *	INPUTS:
 *	ArgNum =number of arguments expected for calculation
 *	*ArgString[] = array of pointers to the start of the argument words
 *
 */
int8_t Div_Function(uint8_t ArgNum, uint8_t *ArgStrings[]){
	float result;
	//printf("IN the Div function\n\r");
	uint8_t i,j;
	int8_t ERR = 0;
	if(ArgNum>3){
		//To many arguments have been entered
		printf("Too many arguments have been entered for the divide operator,\n\r type 'help div' for help\n\r");
	}
	if(ArgNum>2){ //Correct number of arguments have been entered for the divide function
		for(i=1; i<ArgNum; i++){
			j = 0;
			//Loop through each input string until NULL terminator is reached
			while(ArgStrings[i][j] != '\0')
			{
				//Check each character in the string is a ASCII CODE for a number
				if(ArgStrings[i][j] < 46 || ArgStrings[i][j] > 57 || ArgStrings[i][j] == 47)
				{
					//Character in the string was found to contain a Number character ASCII value
					//Report error and break out of loop
					printf("ERROR: Opperator Expects number in arg %i\n\r", i);
					printf("Interpreted Value: %g\n\r", atof((char*)ArgStrings[i]));
					ERR = 1;
					break;
				}
				j++;
			}
			//Do the calculaion
			result = atof((char*)ArgStrings[1])/atof((char*)ArgStrings[2]);
		}
		if(ERR == 1)
		{
			printf("Possible Result from interpreted arguments : %g\n\r",result);
			ERR = 0;
		}
		else
		{
			printf("Result : %g\n\r",result);
		}
	}
	else{
		//Not enough arguements have been entered
		printf("Not enough arguments entered for the mul function,\n\r enter 'help mul' for help\n\r");
	}
	return -1;

}

/*
 * Function: Help_Function
 * ----------------------------
 *   Prints out the help description of a specific function,
 *   or the entire list of possible commands in the command line interface
 *
 *	 ArgNum =number of arguments expected for calculation
 *	 *ArgString[] = array of pointers to the start of the argument words
 *
 */
int8_t Help_Function(uint8_t ArgNum, uint8_t *ArgStrings[]){
	uint8_t j,i;
	//printf("IN the Help function\n\r");
	if(ArgNum == 1){
		printf("\tCommand\tHelp\n\r");
		//Steps through all of the Commands
		for(i = 0; CommandList[i].NameString != 0;i++){
			printf("\t%s\t%s\n\r",CommandList[i].NameString,CommandList[i].HelpString);
		}
	}
	else{
		//Loop through all the arguments and print there corresponding help strings
		for(i=1; i<ArgNum;i++){
			//Loop through all the functions and find which function string matches the entered input string
			for(j=0;CommandList[j].NameString != NULL; j++){
				if(strcasecmp((char *)ArgStrings[i],(char *) CommandList[j].NameString) == 0){
					printf("%s\n\r",(char *) CommandList[j].HelpString);
				}
			}
		}

	}

	return -1;
}


/*
 * Function:Debug_Function
 * ----------------------------
 *   Prints out the help description of a specific function
 *  Returns: Debug_State ==1 ON// Debug_State == 0 OFF
 *
 *  Inputs:
 *	ArgNum =number of arguments expected for calculation
 *	*ArgString[] = array of pointers to the start of the argument words
 *
 */
int8_t Debug_Function(uint8_t ArgNum, uint8_t *ArgStrings[]){
	//Check that only 2 arguments are entered
	if(ArgNum >2){
		printf("Too many arguments entered for the debug function,\r\ntype 'help debug' for help\r\n");
	}
	else if(ArgNum>1){
		//Correct amount of arguments have been entered, determine which state to toggle too
		//Check the input String, to determine which State to toggle Debug_State to
		if(strcasecmp((char *)ArgStrings[1],"On")==0){
			printf("Debug has been turned on\n\r");
			Debug = 1;
		}
		else if(strcasecmp((char *)ArgStrings[1],"Off")==0){
			printf("Debug has been turned off\n\r");
			Debug = 0;
		}
		else{
			printf("Input argument not recognised,\r\ntype 'help debug' for help\r\n");

		}
	}
	else{
		printf("Not enough arguments have been entered for the debug function,\r\ntype 'help debug' for help\r\n");
	}

	return -1;
}


void CommandLineParserInit(void)
{
  // Print welcome message
  printf("\014");
  printf("ELEC3730 Assignment 2\n\r");
  printf("Command Line Parser Example\n\r");

}



/*
 * Function: CommandLineParserProcess
 * ----------------------------
 *  Returns void
 *
 *	This function is used to implement the command line interface, when called it fist check to see if the uartReceive buffer has data if so
 *	it will check to see if it is a character or enter value then leave the function.
 *	If it was a enter value, this means a command and arguments has been entered and further action should be take.
 *
 *
 */
void CommandLineParserProcess(void)
{
  uint8_t c; //Holds the current input from the uartBuffer, awaiting for further process
  static uint8_t ArrOfChars[LIMIT]; //Holds the complete string of input from the serial communication
  static uint8_t i = 0; //Used to increment how many times a user has interface with the command line up until a enter command
  uint8_t j, count; //Variables used to evaluate the command line input
  uint8_t **array_of_words_pp; //Pointer to a array which holds pointers to strings

  // Check for input and echo back
  if (HAL_UART_Receive(&huart2, &c, 1, 0x0) == HAL_OK)
  {
	//Echo to PUTTY and toggle LED
    printf("%c", c);
    HAL_GPIO_TogglePin(GPIOD, LD4_Pin); // Toggle LED4

    //Check that the current input Character isn't enter and that the buffer limit hasn't been exceeded
    if(c != 13 && i<100){
    	//All conditions are fine
    	ArrOfChars[i]= c; //Load the character into the input string if not enter
    	i++; //increment the counter
    }
    else{
    	//Either Overflow of data or Enter was pressed
    	if(i == 100){
    		//Overflow has occured, continue process with this string size
    		printf("\nError to many characters entered in command line\n\r");
    	}
    	//Proceed and terminate string with a null character
    	ArrOfChars[i]='\0';
    	i = 0; //start from beginning again

    	//Now handle the input string and print the results
    	count = string_parser(ArrOfChars, &array_of_words_pp);

    	if (Debug == 1)
    	{
    		 printf("\nThe input string was '%s'\n\r",ArrOfChars);
    		 //Print the number of arguments entered
    		 printf("--> count = %d\r\n", count);
    	}

    	if(count != 0){

    		if (Debug == 1)
    		{
				//Print out the individual words if arguments entered is larger than 0
				for (j=0;j<count;j++)
				{
				  printf("---> %2d: '%s'\r\n", j+1, (array_of_words_pp)[j]);
				}
    		}

    		//**********************************************************************//
    		//Find out which command was entered and do calculation
        	while(CommandList[j].NameString != NULL){
    			if(strcasecmp((char *)array_of_words_pp[0],(char *) CommandList[j].NameString) == 0){
        			//Now do the correct operation based on the match
        			(*CommandList[j].Function_p)(count, array_of_words_pp);
    			}
    			j++;
        	}
        	if(CommandList[j].NameString == NULL){
        		printf("Input not recognised, please enter as follows:\n\r");
        		Help_Function(0,0);
        	}
		}
		else{
			//Let the user know that they must input commands
			printf("No arguments where entered, type 'help' for commands list\n\r");
		}
		//Free memory after the calculation process has occurred
    	if (count != 0)
       	{
       	  free(array_of_words_pp[0]);
       	  free(array_of_words_pp);
       	}
    }

  }
}

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
