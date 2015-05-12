//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Equation.cpp
// -------------
// This class  will manage equation generator
// randomize the sign and numbers, and decides on the missing number
//
// Author: Ido Perry and Alex Odesser
// First version: 2015-04-04
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#include "Equation.h"
#include <stdlib.h>
#include "io_utils.h"
// this function will return a random sign for the equation
char Equation::RandomOperator()
{

	char res = NULL;
	int randomValue = rand() % 4;

	switch (randomValue)
	{
	case 0:
		res = '+';
		break;
	case 1:
		res = '-';
		break;
	case 2:
		res = '*';
		break;
	case 3:
		res = '/';
		break;
	default:
		break;
	}
	return res;
}

//this function will get the sign populated for the eqation and return the eqation part we will hide from the player
char Equation::RandomPartToHide(const char & op)
{
	if (op == '+' || op == '*') // operator is +  or * so we want to hide  the left or the right number
	{
		if (rand() % 2 == 0)
			return 'l';
		else
			return 'r';
	}
	else
	{
		if (rand() % 2 == 0) // operator is -  or / so we want to hide  the solution or the right number
			return 's';
		else
			return 'r';
	}
}

//this function will generte a new random equation according to the game definitions
void Equation::Init(const unsigned int & gameLevel)
{
	currentLevel = gameLevel;
	if (currentLevel <= 20)
		CreateEquationUntilLevel20();
	else
		CreateEquationAfterLevel20();
}


// this funciton will draw the equation in the relevant position and with the relvant hidden part
void Equation::Draw()const
{
	if (currentLevel <= 20)
		DrawUntilLevel20();
	else
		DrawAfterLevel20();
}

//this fucntion get a number and check if it solves the equations
SolutionType Equation::IsSolution(const unsigned int & num)
{
	if (currentLevel <= 20)
		return IsSolutionUntilLevel20(num);
	else
		return IsSolutionAfterLevel20(num);
}

//helper methood to IsSolution for levels 1-20
SolutionType Equation::IsSolutionUntilLevel20(const unsigned int & num)
{
	SolutionType res = WRONG_SOLUTION;
	switch (partToHide)
	{
	case 'l': // left part is hidden so check the left number
		if (num == num1)
			res = IS_SOLUTION;
		break;
	case 'r':// right part is hidden so check the right number
		if (num == num2)
			res = IS_SOLUTION;
		break;
	case 's':// solution part is hidden so check the solution number
		if (num == solution)
			res = IS_SOLUTION;
		break;
	default:  // we should not get here
		break;
	}

	return res;
}

//helper methood to IsSolution for levels 21+
SolutionType Equation::IsSolutionAfterLevel20(const unsigned int & num)
{
	SolutionType res = WRONG_SOLUTION;

		int firstHiddenNumberIndex = 0, SecondHiddenNumberIndex = MAX_NUMBER_OF_OPERANDS - 1;
		// get the hidden parts
		while (operandsArray[firstHiddenNumberIndex] != -1)
			++firstHiddenNumberIndex;
		while (operandsArray[SecondHiddenNumberIndex] != -1)
			--SecondHiddenNumberIndex;
	if (firstHiddenNumberIndex != SecondHiddenNumberIndex)
		{
		//we are tring to solve the partial equation therfore the soultion cant bet a number we are checking
		switch (firstHiddenNumberIndex)
		{
		case 0:
			num1 = num;
			break;
		case 1:
			num2 = num;
			break;
		case 2:
			num3 = num;
			break;
		default: // we shouldnet get here
			break;
		}
		res = SolvePartialEquation(SecondHiddenNumberIndex);
	}
	else
	{
		switch (firstHiddenNumberIndex)
		{
		case 1:
			if (num == num2)
				res = IS_SOLUTION;
			break;
		case 2:
			if (num == num3)
				res = IS_SOLUTION;
			break;
		case 3:
			if (num == solution)
				res = IS_SOLUTION;
			break;
		default: // we shouldnet get here
			break;
		}
	}
	
	if (res == PARTIAL_SOLUTION)
		operandsArray[firstHiddenNumberIndex] = num;

	return res;
}

// this funciton will return the opposite operator ( + <-> - , / <->*) 
char ChangeOperatorSide(const char &op)
{
	switch (op)
	{
	case '+':
		return '-';
		break;
	case '-':
		return '+';
		break;
	case '*':
		return '/';
		break;
	case '/':
		return '*';
		break;
	default:
		break;
	}
}

// helper methood to draw. Draws the equation for levels 1-20
void Equation::DrawUntilLevel20()const
{
	gotoxy(position.getX(), position.getY());
	switch (partToHide)
	{
	case 'l':
		cout << "?" << operator1 << num2 << '=' << solution;
		break;
	case 'r':
		cout << num1 << operator1 << "?" << '=' << solution;
		break;
	case 's':
		cout << num1 << operator1 << num2 << '=' << "?";
		break;
	default:  // we should not get here
		break;
	}
}


void Equation::operandsArrayHideMinium(){

	int min, index;

	//TODO MAKE THE CODE WORK WITHOUT THIS 
	operandsArray[0] = num1;
	operandsArray[1] = num2;
	operandsArray[2] = num3;
	operandsArray[3] = solution;
	//END TODO

	for (int t = 0; t < 2; t++)
	{
		min = 10001;
		index = 0;
		for (int i = 0; i < MAX_NUMBER_OF_OPERANDS; i++)
		{
			if (operandsArray[i] < min && operandsArray[i] > -1){
				min = operandsArray[i];
				index = i;
			}
		}
		operandsArray[index] = -1;
	}
}

// helper methood to draw. Draws the equation for levels maxRandomNumber and above
void Equation::DrawAfterLevel20()const
{
	gotoxy(position.getX(), position.getY());

	for (int i = 0; i < MAX_NUMBER_OF_OPERANDS; i++)
	{
		if (operandsArray[i] != -1)
			cout << operandsArray[i];
		else
			cout << "?";
		if (i < 3)
			cout << ' ' << operatorsArray[i] << ' ';
	}
}


//helper methood to init, creates an equation for levels 1-20
void Equation::CreateEquationUntilLevel20()
{

	operator1 = RandomOperator();
	partToHide = RandomPartToHide(operator1);
	switch (operator1)
	{
	case '+': // Operator is + therfore we will generate 2 radnnom numbers  for the left and right numbers and calculate the solution
		num1 = rand() % (currentLevel + 10) + 1;
		num2 = rand() % (currentLevel + 10) + 1;
		solution = num1 + num2;

		break;
	case '-':// Operator is - therfore we will generate 2 radnnom numbers  for the right and and solution numbers and calculate the left number
		num2 = rand() % (currentLevel + 10) + 1;
		solution = rand() % (currentLevel + 10) + 1;
		num1 = solution + num2;
		break;
	case '*': // Operator is * therfore we will generate 2 randnom numbers  for the left and right numbers and calculate the solution
		num1 = rand() % (currentLevel + 10) + 1;
		num2 = rand() % (currentLevel + 10) + 1;
		solution = num1 * num2;
		break;
	case '/':// Operator is / therfore we will generate 2 radnnom numbers  for the right and and solution numbers and calculate the left number

		num2 = rand() % (currentLevel + 10) + 1;
		solution = rand() % (currentLevel + 10) + 1;
		num1 = solution * num2;
		break;
	default:  // we should not get here
		break;
	}
}
//helper methood to init, creates an equation for levels 21+. all random genreted numbers will be from 1 - 21 !!!
void Equation::CreateEquationAfterLevel20()
{

	for (int i = 0; i < MAX_NUMBER_OF_OPERATORS; ++i) // init operators array
		operatorsArray[i] = RandomOperator();

	switch (operatorsArray[0]) // init operands array
	{
	case '+':
		GenerteEquationNumbersFirstOperatorPlus();
		break;
	case '-':
		GenerteEquationNumbersFirstOperatorSubtruct();
		break;
	case '*':
		GenerteEquationNumbersFirstOperatorMultiply();
		break;
	case '/':
		GenerteEquationNumbersFirstOperatorDevide();
		break;
	default: // we should not get here
		break;
	}
	operandsArrayHideMinium(); // initialize the operands array array which is used to print the equation
}

//helper methood for the case when first operator is +
void Equation::GenerteEquationNumbersFirstOperatorPlus()
{
	GenerteRandomNumsOpPM();
	switch (operatorsArray[1])
	{
	case '+':
		solution = num1 + num2 + num3;
		break;
	case '-':
		solution = (num1 + num2) - num3;
		break;
	case '*':
		solution = num1 + (num2 * num3);
		break;
	case '/':
		solution = num1 + (num2 / num3);
		break;
	default:// we should not get here
		break;
	}
}

//helper methood for the case when first operator is '-'
void Equation::GenerteEquationNumbersFirstOperatorSubtruct()
{
	GenerteRandomNumsOpS();
	switch (operatorsArray[1])
	{
	case '+':
		solution = num1 - num2 + num3;
		break;
	case '-':
		solution = num1 - num2 - num3;
		break;
	case '*':
		solution = num1 - (num2 * num3);
		break;
	case '/':
		solution = num1 - (num2 / num3);
		break;
	default:// we should not get here
		break;
	}
}

//helper methood for the case when first operator is '*'
void Equation::GenerteEquationNumbersFirstOperatorMultiply()
{
	GenerteRandomNumsOpPM();
	switch (operatorsArray[1])
	{
	case '+':
		solution = (num1 * num2) + num3;
		break;
	case '-':
		solution = (num1 * num2) - num3;
		break;
	case '*':
		solution = (num1 * num2) * num3;
		break;
	case '/':
		solution = (num1 * num2) / num3;
		break;
	default:// we should not get here
		break;
	}
}

//helper methood for the case when first operator is '/' 
void Equation::GenerteEquationNumbersFirstOperatorDevide()
{
	GenerteRandomNumsOpD();
	switch (operatorsArray[1])
	{
	case '+':
		solution = (num1 / num2) + num3;
		break;
	case '-':
		solution = (num1 / num2) - num3;
		break;
	case '*':
		solution = (num1 / num2) * num3;
		break;
	case '/':
		solution = (num1 / num2) / num3;
		break;
	default:// we should not get here
		break;
	}
}

//helper mehtood to genrate the equation after level 20 for the case when the first operator is + or * 
void Equation::GenerteRandomNumsOpPM()
{
	// first oprator is + or *, thefore genrate 2 random numbers for num1 and num 3
	int tempSolution;
	num1 = rand() % (MAX_RANDOM_NUMER_AFTER_LEVEL_20)+1;
	num3 = rand() % (MAX_RANDOM_NUMER_AFTER_LEVEL_20)+1;
	if (operatorsArray[1] == '+' || operatorsArray[1] == '*') // second oprator is + or *, thefore genrate 1 random number for num2
		num2 = rand() % (MAX_RANDOM_NUMER_AFTER_LEVEL_20)+1;
	else if (operatorsArray[1] == '-')
	{// second oprator is -, thefore genrate 1 random number for temp solution and calculate num2
		tempSolution = rand() % (MAX_RANDOM_NUMER_AFTER_LEVEL_20)+1;
		num2 = tempSolution + num3;
	}
	else
	{// second oprator is /, thefore genrate 1 random number for temp solution and calculate num2
		tempSolution = rand() % (MAX_RANDOM_NUMER_AFTER_LEVEL_20)+1;
		num2 = tempSolution * num3;
	}

}

//helper mehtood to genrate the equation after level 20 for the case when the first operator is - or /  generates random numbers 2, 3 and solution
void Equation::GenerteRandomNumsOpS()
{
	// first operator is -, therefore generate 2 random numbers for num3 and temp solution
	int tempSolution;
	num3 = rand() % (MAX_RANDOM_NUMER_AFTER_LEVEL_20)+1;
	tempSolution = rand() % (MAX_RANDOM_NUMER_AFTER_LEVEL_20)+1;
	if (operatorsArray[1] == '+')
	{
		//second opertator is +, thefore genrate radnom number for num 2 and calculate num 1 
		num2 = rand() % (MAX_RANDOM_NUMER_AFTER_LEVEL_20)+1;
		num1 = tempSolution + num2;
	}
	else if (operatorsArray[1] == '*')
	{
		//second opertator is *, thefore genrate radnom number for num 2 and calculate num 1 
		num2 = rand() % (MAX_RANDOM_NUMER_AFTER_LEVEL_20)+1;
		num1 = tempSolution + (num2*num3);
	}
	else if (operatorsArray[1] == '-')
	{
		//second opertator is -, thefore calculate num2 then genrate a radnom temp solution an calculate num1
		num2 = rand() % (MAX_RANDOM_NUMER_AFTER_LEVEL_20)+1;
		num1 = (num3 + tempSolution) + num2;
	}
	else// operator 2 == '/'
	{
		num2 = tempSolution * num3;
		tempSolution = rand() % (MAX_RANDOM_NUMER_AFTER_LEVEL_20)+1;
		num1 = tempSolution + (num2 - num3);
	}
}


void Equation::GenerteRandomNumsOpD()
{
	// first operator is /, therefore generate 3 random numbers for num2 , num 3 and temp solution and clculate num 1
	int tempSolution;
	num3 = rand() % (MAX_RANDOM_NUMER_AFTER_LEVEL_20)+1;
	tempSolution = rand() % (MAX_RANDOM_NUMER_AFTER_LEVEL_20)+1;
	num2 = rand() % (MAX_RANDOM_NUMER_AFTER_LEVEL_20)+1;
	if (operatorsArray[1] == '+')
	{
		//second opertator is +, calculate num 1 
		num1 = tempSolution * num2;
	}
	else if (operatorsArray[1] == '*')
	{
		//second opertator is *, thefore calculate num 1 
		num1 = tempSolution * num2;
	}
	else if (operatorsArray[1] == '-')
	{
		//second opertator is - , thefore calculate num1 
		num1 = (num3 + tempSolution) * num2;
	}
	else if (operatorsArray[1] == '/')
	{
		//second opertator is /, thefore calculate num1 
		num1 = (num3 * tempSolution) * num2;
	}
}

// helper methood will return the state of the partail solution posabiility
SolutionType Equation::SolvePartialEquation(const int & secondHiddenNumber)
{
	switch (secondHiddenNumber)
	{
	case 1:
		return ExtractNum2PartialSolutionState();
	case 2:
		return ExtractNum3PartialSolutionState();
		break;
	case 3:
		return ExtractSolutionPartialSolutionState();
		break;
	default:
		break;
	}
}


// helper methood to extract the partial state of the solution when num 2 is still hidden
SolutionType Equation::ExtractNum2PartialSolutionState()
{
	int tempSolution = 0;
	SolutionType res = WRONG_SOLUTION;
	switch (operatorsArray[0])
	{
	case '+':
		switch (operatorsArray[1])
		{
		case '+':// A+X+B=C ==> X = C-A-B
			tempSolution = solution - num1 - num3;
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '-':// A+X-B=C ==> X = C-A+B
			tempSolution = solution - num1 + num3;
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '/':// A+(X/B)=C ==> X = (C-A)*B
			tempSolution = (solution - num1) * num3;
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '*':// A+(X*B)=C ==> X = (C-A)/B
			tempSolution = (solution - num1) / num3;
			if (IsInteger((solution - num1), num3) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
		default: // we should not get here
			break;
		}
		break;
	case '-':
		switch (operatorsArray[1])
		{
		case '+'://A-X+B=C ==> X = C+A-B
			tempSolution = solution + num1 - num3;
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '-'://A-X-B=C ==> X = C+A+B
			tempSolution = solution + num1 + num3;
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '/'://A-(X/B)=C ==> X = (C+A)*B
			tempSolution = (solution + num1) * num3;
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '*'://A-(X*B)=C ==> X = (C+A)/B
			tempSolution = (solution + num1) / num3;
			if (IsInteger((solution + num1), num3) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
		default: // we should not get here
			break;
		}
		break;
	case '*':
		switch (operatorsArray[1])
		{
		case '+'://(A*X)+B=C ==> X = (C-B)/A
			tempSolution = (solution - num3) / num1;
			if (IsInteger((solution - num3), num1) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '-'://(A*X)-B=C ==> X = (C+B)/A
			tempSolution = (solution + num3) / num1;
			if (IsInteger((solution + num3), num1) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '/'://(A*X)/B=C ==> X = (C*B)/A
			tempSolution = (solution * num3) / num1;
			if (IsInteger((solution * num3), num1) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '*'://(A*X)*B=C ==> X = (C/B)/A
			tempSolution = (solution / num3) / num1;
			if (IsInteger(solution, num3) && IsInteger((solution / num3), num1) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		default: // we should not get here
			break;
		}
		break;
	case '/':
		switch (operatorsArray[1])
		{
		case '+'://(A/X)+B=C ==> X = A/(C-B)
			tempSolution = num1 / (solution - num3);
			if (IsInteger(num1, (solution - num3)) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '-'://(A/X)-B=C ==> X = A/(C+B)
			tempSolution = num1 / (solution + num3);
			if (IsInteger(num1, (solution + num3)) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '/'://(A/X)/B=C ==> X = A/(C*B)
			tempSolution = num1 / (solution * num3);
			if (IsInteger(num1, (solution * num3)) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '*'://(A/X)*B=C ==> X = (A*B)/X
			tempSolution = (num1 *num3) / solution;
			if (IsInteger((num1 * num3), solution) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		default: // we should not get here
			break;
		}
		break;
	default: // we should not get here
		break;
	}

	if (res == PARTIAL_SOLUTION)
		num2 = tempSolution;
	return res;
}


// helper methood to extract the partial state of the solution when  num3 is still hidden
SolutionType Equation::ExtractNum3PartialSolutionState()
{
	int tempSolution = 0;
	SolutionType res = WRONG_SOLUTION;

	switch (operatorsArray[0])
	{
	case '+':
		switch (operatorsArray[1])
		{
		case '+':// A+B+X=C ==> X=C-A-B
			tempSolution = solution - num1 - num2;
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '-':// A+B-X=C ==> X=A+B-C
			tempSolution = (num1 + num2) - solution;
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '/':// A+(B/X)=C ==> X=B/(C-A)
			tempSolution = num2 / (solution - num1);
			if (IsInteger(num2, (solution - num1)) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '*':// A+(B*X)=C ==> X=(C-A)/B
			tempSolution = (solution - num1) / num2;
			if (IsInteger((solution - num1), num2) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		default: // we should not get here
			break;
		}
		break;
	case '-':
		switch (operatorsArray[1])
		{
		case '+':// A-B+X=C ==> X=C+A+B
			tempSolution = solution + num1 - num2;
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '-':// A-B-X=C ==> X=C+A+B
			tempSolution = solution + num1 + num2;
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '/':// A-(B/X)=C ==> X=B/(C+A)
			tempSolution = num2 / (solution + num1);
			if (IsInteger(num2, (solution + num1)) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '*':// A-(B*X)=C ==> X=(C+A)/B
			tempSolution = (solution + num1) / num2;
			if (IsInteger((solution + num1), num2) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		default: // we should not get here
			break;
		}
		break;
	case '*':
		switch (operatorsArray[1])
		{
		case '+':// (A*B)+X=C ==> X=C-(A*B)
			tempSolution = solution - (num1 * num2);
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '-':// (A*B)-X=C ==> X=(A*B)-C
			tempSolution = (num1 * num2) - solution;
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '/':// (A*B)/X=C ==> X=(A*B)/C
			tempSolution = (num1 * num2) / solution;
			if (IsInteger((num1 * num2), solution) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '*':// (A*B)*X=C ==> X=C/(A*B)
			tempSolution = solution / (num2 * num1);
			if (IsInteger(solution, (num1 * num2)) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		default: // we should not get here
			break;
		}
		break;
	case '/':
		switch (operatorsArray[1])
		{
		case '+':// (A/B)+X=C ===> X= C-(A/B)
			tempSolution = solution - (num1 / num2);
			if (IsInteger(num1, num2) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '-':// (A/B)-X=C ===> X= C+(A/B)
			tempSolution = solution + (num1 / num2);
			if (IsInteger(num1, num2) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '/':// (A/B)/X=C ===> X= A/(C*B)
			tempSolution = num1 / (solution * num2);
			if (IsInteger(num1, (solution * num2)) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '*':// (A/B)*X=C ===> X= (C*B)/A
			tempSolution = (solution * num2) / num1;
			if (IsInteger((solution * num2), num1) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		default: // we should not get here
			break;
		}
		break;
	default: // we should not get here
		break;
	}

	if (res == PARTIAL_SOLUTION)
		num3 = tempSolution;

	return res;


}

// helper methood to extract the partial state of the solution when the solution is still hidden
SolutionType Equation::ExtractSolutionPartialSolutionState()
{
	int tempSolution = 0;
	SolutionType res = WRONG_SOLUTION;

	switch (operatorsArray[0])
	{
	case '+':
		switch (operatorsArray[1])
		{
		case '+':// A+B+C=X ==
			tempSolution = num1 + num2 + num3;
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '-':// A+B-C=X 
			tempSolution = (num1 + num2) - num3;
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '/':// A+(B/C)=X
			tempSolution = num1 + (num2 / num3);
			if (IsInteger(num2, num3) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '*':// A+(B*C)=X 
			tempSolution = num1 + (num2 *num3);
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		default: // we should not get here
			break;
		}
		break;
	case '-':
		switch (operatorsArray[1])
		{
		case '+':// A-B+C=X 
			tempSolution = num1 - num2 + num3;
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '-':// A-B-C=X 
			tempSolution = num1 - num2 - num3;
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '/':// A-(B/C)=X
			tempSolution = num1 - (num2 / num3);
			if (IsInteger(num2, num3) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '*':// A-(B*C)=X
			tempSolution = num1 - (num2 * num3);
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		default: // we should not get here
			break;
		}
		break;
	case '*':
		switch (operatorsArray[1])
		{
		case '+':// (A*B)+C=X 
			tempSolution = (num1 * num2) + num3;
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '-':// (A*B)-C=X X
			tempSolution = (num1 * num2) - num3;
			if (tempSolution > 0 && tempSolution < (currentLevel + 10))
				if (IsSolutionInRange(tempSolution))
					res = PARTIAL_SOLUTION;
			break;
		case '/':// (A*B)/C=X 
			tempSolution = (num1 * num2) / num3;
			if (IsInteger((num1 * num2), num3) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
		case '*':// (A*B)*C=X 
			tempSolution = (num1 * num2) * num3;
			if (IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		default: // we should not get here
			break;
		}
		break;
	case '/':
		switch (operatorsArray[1])
		{
		case '+':// (A/B)+C=X 
			tempSolution = (num1 / num2) + num3;
			if (IsInteger(num1, num2) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
		case '-':// (A/B)-C=X 
			tempSolution = (num1 / num2) - num3;
			if (IsInteger(num1, num2) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '/':// (A/B)/C=X 
			tempSolution = (num1 / num2) / num3;
			if (IsInteger(num1, num2) && IsInteger((num1 / num2), num3) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		case '*':// (A/B)*C=X 
			tempSolution = (num1 / num2) * num3;
			if (IsInteger(num1, num2) && IsSolutionInRange(tempSolution))
				res = PARTIAL_SOLUTION;
			break;
		default: // we should not get here
			break;
		}
		break;
	default: // we should not get here
		break;
	}

	if (res == PARTIAL_SOLUTION)
		solution = tempSolution;

	return res;
}
