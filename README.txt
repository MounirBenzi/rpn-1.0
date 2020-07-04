Date: 9/03/2019
Description: This is a Reverse Polish Notation Calculator, which is capable of basic arithmetic: addition, subtraction, multiplication and division.
              Users should enter operands and operators, making sure the operands are all integers and that no illegal operators have been entered. Allowed operators are (+ , -, x, /)
              The correct number of operators should be used according to how many operands have been entered. It should be noted that there is a maximum of 10 operands.

Usage: This program can be executed from the command line, using the line:  $ ./rpn.exe operands... operators

            For example, basic addition would be carried out as such:
            $ ./rpn.exe 1 1 1 + +
            3
            To demonstrate subtraction:
            $ ./rpn.exe 8 6 1 - -
            3
            This can be slightly confusing, but this operation works as 8 - (6-1)
            The multiplication operator is x
            $ ./rpn.exe 5 6 1 x x
            30
            As this program only works with integers, division will not always work and will return errors
            $ ./rpn.exe 7 2 /
            7 is not divisible by 2
            $ ./rpn.exe 7 0 /
            Zero division in 7 / 0

            It is also possible to see the version of the program, using:
            $ ./rpn.exe --version
            The usage of the program can also be shown by running
            $ ./rpn.exe --usage

Implementation: All of the functions for the operators, the stack and overflow checking functions have been implemented and are working.

Changelog: Changelog:  09 Mar 2019 - Created the stack and its functions.
		                   10 Mar 2019 - Created cases function to deal with the various tokens
                       11 Mar 2019 - Altered code to no longer use global variables. In hindsight this should have been done at the very beginning
			                 11 Mar 2019 - Created Underflow function and altered my functions to check and deal with overflow and invalid tokens
                       12 Mar 2019 - Fixed bug in cases where arguments leading with an operator would cause the case to run
                       13 Mar 2019 - Added the remainingToken function used tot print out the tokens left on the stack
                       14 Mar 2019 - Fixed bug in detecting operators using the strtol function.
