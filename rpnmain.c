/* Importing Modules*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

/* Function definitions */

/*function to print out the remaining stack values*/
void remainingToken(int *stack, int *top){
	fprintf(stderr, "Tokens left on stack:\n");
	for (int j=0; j <= *top; j++){
		fprintf(stderr, "stack[%d] = %d\n", j, stack[j]);
	}
}

/* chekcUnderflow checks that at least two elements are in the stack.
This function is called in the cases function*/
int checkUnderflow(char val, int *top){
	if(*top == 0){ //Checks to see if the stack pointer is on the second element, which means that there is only one element on the stack
		fprintf(stderr, "Stack underflow at \"%c\"\n", val);
		exit(1);
	}
	else{
		return 0;
	}
}

/* This function adds items to the stack and increments the top counter by one.
The top counter tells us where we are in the stack*/
int push(int x, int *stack, int *top){
	if(*top == 9){//checking to see if stack is full for stack overflow
			fprintf(stderr, "Stack overflow at \"%d\"\n", x);
			exit(1);
	}
	*top = *top + 1;
	stack[*top] = x;
	return 0;
}

/* This function removes items from the stack and checks if the stack is empty*/
int pop(int *stack, int *top){
	int popped = 0;
	if (*top == -1){ //The pointer starts at -1, so if it is still at -1, the stack is empty and nothing can be removed.
		fprintf(stderr, "Stack is empty\n");
		return 1;
	}
	else{
		popped = stack[*top];
		*top = *top -1; //To remove an item from the stack we simply move the stack pointer down by 1
		return popped;
	}
}

/* The add function is responsible for adding two numbers from the stack together,
and for ensuring no integer overflow occurs */
int add(int *stack, int *top){
	int val1 = pop(stack, top); //We get the values from the stack by popping them off the stack
	int val2 = pop(stack, top);
	/*checks to see that the result of the addition doesnt overflow by taking into
	account the max and min integer values*/
	if (val1 > INT_MAX - val2 || val1 < INT_MIN + val2){
		fprintf(stderr, "Integer overflow in %d + %d\n", val2, val1);
		exit(1);
	}
	else{
		push(val1 + val2, stack, top); //Adds the result of the operation back to the stack
		return 0;
	}
}

/* The multiplication function is responsible for multiplying two numbers from the stack together,
and for ensuring no integer overflow occurs */
int multiplication(int *stack, int *top){
	int val1 = pop(stack, top);
	int val2 = pop(stack, top);
	if ((val1 > INT_MAX / val2 && val1 > 0) //Checks to see if the product of the two numbers causes an integer overflow
			|| (val1 < 0 && val1 < INT_MIN / -val2)){ //Also checks for overflow but in this case for negative nunbers
			fprintf(stderr, "Integer overflow in %d x %d\n", val2, val1);
			exit(1);
	}
	else{
		push(val2 * val1, stack, top);//Adds the result of the operation back to the stack
		return 0;
	}
}

/* The subtraction function is responsible for subtracting two numbers from the stack from eachother,
and for ensuring no integer overflow occurs */
int subtract(int *stack, int *top){
	int val1 = pop(stack, top);
	int val2 = pop(stack, top);
	/*checks for overflow by considering the max and min integer values and the
	sign of the values*/
	if ((val2 < INT_MIN + val1 && val1 >0) || (val2 > INT_MAX + val1 && val1 <0) ){
		fprintf(stderr, "Integer overflow in %d - %d\n", val2, val1);
		exit(1);
	}
		else{
		/*pushes result onto stack,
		Note: order is important as val2 -val != val1 -val2 in all cases.
		Since val2 is added on the stack first, it takes the lead. */
		push(val2 - val1, stack, top);
		return 0;
	}
}

/* The division function is responsible for dividing the two numbers from the
stack, and for ensuring no integer overflow occurs */
int division(int *stack, int *top){
	int val1 = pop(stack, top);
	int val2 = pop(stack, top);
	/*For division the only possible way that overflow can occur is with:
											-2147483648/-1
	Therefore, to ensure no overflow occurs it is checked in the if statement*/
	if(val2 == INT_MIN && val1 == -1){
		fprintf(stderr, "Integer overflow in %d / %d\n", val2, val1);
		exit(1);
	}
	else if (val1 == 0){  //checks for 0 division
		fprintf(stderr, "Zero division in %d / %d\n", val2, val1);
		exit(1);
	}
	/*checks the remainder of the division between val2 and val1, if 0 val2 is
	divisble by val1*/
	else if (val2 % val1 == 0){
		push(val2/val1, stack, top);
		return 0;
	}
	else{
		fprintf(stderr, "%d is not divisible by %d\n", val2, val1);
		exit(1);
	}
}

/*The cases function checks to whether a valid token has been entered by the
user. If not an error message is printed and the code is exitted  */
int cases(char token[], int argc, int *stack, int *top){
	int size = strlen(token); //getting the size of of the entered token
	if(size > 1){//If the token length is greater than 1, print error
		fprintf(stderr, "Invalid token \"%s\"\n", token);
		exit(1);
	}
	switch(token[0]){//using a switch to check what argument was entered. where argv[0] is the operator
		case '+': //if + is entered
			if (*top==-1 && size==1){ //ensuring that an operator is not the first element
				fprintf(stderr, "First value cannot be an operator");
				exit(1);
			}
			else if(!checkUnderflow(token[0], top) && size==1){//checks for underflow
					add(stack, top);
					return 0;
				}
		case '-':
			if (*top==-1 && size==1){
				fprintf(stderr, "First value cannot be an operator");
				exit(1);
			}
			else if(!checkUnderflow(token[0], top) && size==1){
				subtract(stack, top);
				return 0;
			}
			return 0;
		case 'x':
			if (*top==-1 && size==1){
				fprintf(stderr, "First value cannot be an operator");
				exit(1);
			}
			else if(!checkUnderflow(token[0], top) && size==1){
				multiplication(stack, top);
				return 0;
			}
		case '/':
			if (*top==-1 && size==1){
				fprintf(stderr, "First value cannot be an operator");
				exit(1);
			}
			else if(!checkUnderflow(token[0], top) && size==1){
				division(stack, top);
				return 0;
			}
		default:
			fprintf(stderr, "Invalid token \"%s\"\n", token);
			exit(1);
	}
}

/*This function is used to check for integer overflow by looking at the limits
and max values of int*/
int string_to_int(char *str, int *result){
  long long_val = strtol(str, NULL, 10); //converts strings to a long data type
  if ( (long_val == LONG_MIN && errno == ERANGE)
      || (long_val == LONG_MAX && errno == ERANGE)
      || long_val < INT_MIN
      || long_val > INT_MAX) {
    return 0;
  }
  *result = (int)long_val;
  return 1;
}

/*This function takes the user input, creates the stack and is what drives the
operations*/
int stackCreation(int argc, char*argv[]){
	int stack[10]; //creates our stack
	int top = -1; // pointer to stack
	char *endptr; //pointer used to find the end of string in strtol
	int operator; //used to find overflow
	int value = 0;
	for(int i=0; i<argc; i++){
		if (!string_to_int(argv[i], &operator)){ //checking for integer overflow
			fprintf(stderr, "Integer overflow at token \"%s\"\n", argv[i]);
			exit(1);
		}
		else {
					value = strtol(argv[i], &endptr, 10);
					/*Checks if the value is an integer.
					If there is no text in the entered argument and the first element
					is not '+' (accounts for arguments starting with +) then push to stack*/
					if (*endptr == '\0' && argv[0][0] != '+'){
						push(value, stack, &top);
					}
					else{ // if the argument is not an integer, check if its an operator
							cases(argv[i], argc, stack, &top);
					}
		}
	}
	//checks if there are multiple tokens left on the stack
	if (top != 0){
		remainingToken(stack, &top);
		return 1;
	}
	else{
			fprintf(stdout,"%d\n", stack[0]); //prints the final result
			return 0;
	}
}

int main(int argc, char *argv[]){
	if(argc == 2 && !strcmp(argv[1], "--version")){
		printf("1.0\n");
		return 0;
	}
	else if(argc == 2 && !strcmp(argv[1], "--usage")){
		printf("./rpn.exe --usage\n");
		printf("./rpn.exe --version\n");
		printf("./rpn.exe TOKENS...\n");
		return 0;
	}
	else if(argc == 1){
		fprintf(stderr, "./rpn.exe --usage\n");
		fprintf(stderr,"./rpn.exe --version\n");
		fprintf(stderr,"./rpn.exe TOKENS...\n");
		return 1;
	}
	else {
		 return stackCreation(argc-1, argv+1);
	}
}
