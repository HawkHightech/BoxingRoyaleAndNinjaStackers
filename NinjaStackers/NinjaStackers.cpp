// Author: Alexander Hawkins
// Game Title: NinjaStackers
// Compile: g++ -std=c++11 NinjaStackers.cpp -o NinjaStackers
// Compile (cont.): ./NinjaStackers

#include <iostream> //Include io stream
#include <fstream> //Include file stream
#include <stdlib.h> //Include std library header file
#include <stack> //Include stack object implementation
#include <unistd.h> //Include unix standard header file
using namespace std; //Using namespace std (standard)

/*
Pseudocode begin:

	System will begin with the player menu:
		1. Play the game
		2. Learn about the rules of the game
		3. Exit the game
	If the user selects Play the game:
		The computer will input random numbers onto the stack.
		After 10 random numbers are generated:
			The computer will stop adding numbers to the stack.
		The user will then begin to type each number from the top of the stack to the bottom.
		If the user inputs the incorrect number:
			User's score will be in deducted by 25 points.
		Else if the user inputs the correct number:
			User's score will be in added by 100 points.
		When all numbers are typed into the system, the game will be complete.
	The user will be given a score for performance.
		Point system? Timer?
	If the user selects Learn about the rules of the game:
		Info about the game will be displayed on the monitor for the user to read.
			Cout outputs.
	If the user selects Exit the game:
		The game will exit.

	Reason for utilizing elementArray: To show I understand the implementation of an array

Pseudocode ends
*/

class Ninjas //Creating a class named Ninjas
{
	public: //Public access specifier
		int userScore = 0; //Attribute int userScore set to 0

		void decreaseUserScore(int decScore) //Method decreaseUserScore with one perameter to decrease the user's score
		{
			userScore = userScore - decScore; //Decrease the user's score by 25
		}

		void increaseUserScore(int incScore) //Method increaseUserScore with one perameter to increase the user's score
		{
			userScore = userScore + incScore; //Increase the user's score by 100
		}

	protected: //Protected access specifier
		int highScore = 0; //Attribute int highScore set to 0
		string userPerformance; //Attribute string userPerformance
};

class NinjaSets: public Ninjas //Creating a class named NinjaSets derived from the Ninjas class
{
	public: //Public access specifier

		NinjaSets(int userScoreboard) //Constructor named NinjaSets with one perameter for the user's score
		{
			userScore = userScoreboard; //User's Score is set to the initialized int userScoreboard
		}

		int setHighScore() //Method setHighScore to set the user's high score
		{
			if (userScore > highScore) //If the new score is better than the previous score
			{
				highScore = userScore; //Set the new score as the high score
			}

			return highScore; //Return the highscore
		}

		string setPerformance() //Method setPerformance to set the user's performance
		{
			if (userScore >= 0 && userScore <= 700) //If the user's score is between 0-700
			{
				userPerformance = "Impersistent"; //UserPerformance is set to "Impersistent"
			}

			else if (userScore > 700 && userScore < 975) //If the user's score is between 701-974
			{
				userPerformance = "Focused"; //UserPerformance is set to "Focused"
			}

			else if (userScore >= 975 && userScore <= 1000) //If the user's score is between 975-1000
			{
				userPerformance = "Senseii"; //UserPerformance is set to "Senseii"
			}

			else //else
			{
				userPerformance = "Evaluation not calculated"; //UserPerformance is set to "Evaluation not calculated"
			}

			return userPerformance; //Return userPerformance
		}
};

NinjaSets ninjaScore(0); //Creating an object named ninjaScore utilizing NinjaSets class

int playerMenu() //Creating a function named playerMenu with 0 perameters, returning type int
{
	int playerSelect; //Initializing an int named playerSelect

	cout << "" << endl; //Output open space to the user (similar to \n)
	cout << "Welcome to Ninja Stackers! Please select an option: " << endl; //Output welcome message to the user
	cout << "1. Play Ninja Stackers" << endl; //Output first option to the user
	cout << "2. Learn the rules of Ninja Stackers" << endl; //Output second option to the user
	cout << "3. Exit game" << endl; //Output third option to the user
	cin >> playerSelect; //Store the user's input into playerSelect

	return playerSelect; //Return the user's input
}

void gameInstructionKey() //Creating a function named gameInstructionKey with 0 perameters, returning type void
{
	cout << "" << endl; //Output open space to the user (similar to \n)
	cout << "The goal of Ninja Stackers is to type every given number from the top of the stack to the bottom of the stack without losing any points." << endl; //Display 'The goal . . .' to the user
	cout << "The computer will give the user 10 random numbers." << endl; //Display 'The computer . . .' to the user
	cout << "When all 10 numbers are generated, the user will have to input each number one at a time." << endl; //Display 'When all . . .' to the user
	cout << "If the user inputs an incorrect number, the user's score will be deducted by 25 points." << endl; //Display 'If the user . . .' to the user
	cout << "If the user inputs a correct number, the user's score will be added by 100 points." << endl; //Display 'If the user . . .' to the user
	cout << "Be consistent and try your best to receive full points!" << endl; //Display 'Be consistent . . .' to the user

}

int incorrectInput() //Creating a function named incorrectInput with 0 perameters, returning type int
{
	cout << "Incorrect. -25 PTS. Type EVERY element one at a time from the END element to the START element." << endl; //Display 'Incorrect. -25 . . .' to the user
	cout << "If you have already unstacked an element, input the next preferred element." << endl; //Display 'If you have . . .' to the user
	ninjaScore.decreaseUserScore(25); //Decrease the user's score by 25
	return 0; //Return 0
}

void gameNS() //Creating a function named gameNS with 0 perameters, returning type void
{
	stack<int> ninjaStack; //Creating an instance of a stack named ninjaStack
	srand((unsigned int)time(NULL)); //Initialize the random number generators
	int aiSelectElement = ((rand()%1000) + 1); //Creating an int named aiSelectElement which stores a random number between 1 and 1000
	int elementArray[10]; //Creating an int array named elementArray set to size 10 (0-9)
	int remainingElements = 9; //Creating an int named remainingElements set to 9

	char userReady; //Creating a char named userReady
	cout << "Are you ready to begin?" << endl; //Output a ready request message to the user
	cout << "(Y) = Yes | (N) = No" << endl; //Output '(Y) = Yes | (N) = No' to the user
	cin >> userReady; //Store the user's input into userReady

	if (userReady == 'y' || userReady == 'Y') //If the user inputs y or Y
	{
		//Stack push elements begin

		ninjaScore.userScore = 0; //Set the user's score back to 0

		for (int stackElements = 0; stackElements <= 9; stackElements++) //Creating a for loop to add elements into the array
		{
			aiSelectElement = ((rand()%1000) + 1); //Store a new random number between 1 and 1000
			ninjaStack.push(aiSelectElement); //Push the fourth random number onto the stack
			//cout << ninjaStack.top() << endl;
			cout << "Element " << aiSelectElement << " has been added to the stack. " << remainingElements << " elements remaining." << endl; //Display stack append and the amount of elements remaining
			elementArray[stackElements] = aiSelectElement; //Append the random number into the selected position of the array
			remainingElements--; //Subtract the remaining elements by 1
			sleep(1); //Wait for one second
		}

		cout << "All elements have been added to the stack." << endl; //Display 'All elements . . .' to the user
		cout << "Type EVERY element one at a time from the END element to the START element. GO!" << endl; //Display 'Type . . .' to the user

		int decreaseArrayPosition = 9; //Creating an int named decreaseArrayPosition set to 9 (top of array)

		while (!ninjaStack.empty()) //While the stack is not empty
		{
			int elementReady; //Creating an int named elementReady
			cin >> elementReady; //Store the user's input into elementReady

			if (elementReady == elementArray[0] && elementReady == ninjaStack.top()) //If the user's input equals the zeroth position of the array, and the user's input equals the number at the top of the stack
			{
				cout << "Correct! You've received +100 PTS." << endl; //Display 'Correct! You've . . .' to the user
				ninjaStack.pop(); //Pop the number out of the top of the stack
				ninjaScore.increaseUserScore(100); //Increase the user's score by 100
			}

			else if (elementReady == elementArray[decreaseArrayPosition] && elementReady == ninjaStack.top()) //If the user's input equals the position of the array, and the user's input equals the number at the top of the stack
			{
				cout << "Correct! You've received +100 PTS. Keep going!" << endl; //Display 'Correct! You've . . .' to the user
				ninjaStack.pop(); //Pop the number out of the top of the stack
				ninjaScore.increaseUserScore(100); //Increase the user's score by 100
				decreaseArrayPosition--; //Subtract decreaseArrayPosition by 1
			}

			else //else
			{
				incorrectInput(); //Call incorrectInput() function
			}

		}

		if (ninjaStack.empty()) //If the stack if empty
		{
			if (ninjaScore.userScore < 0) //If the user's score is negative
			{
				ninjaScore.userScore = 0; //Set the score to 0
			}

			cout << "Congratulations! You're a Ninja Stacker!" << endl; //Display a congratulations message + final score to the user
			cout << "Final Score: " << ninjaScore.userScore << endl; //Display the user's final score
			cout << "High Score: " << ninjaScore.setHighScore() << endl; //Display the user's high score
			cout << "Performance: " << ninjaScore.setPerformance() << endl; //Display the user's performance
		}

	}

	else //else
	{
		//playerMenu(); //Call playerMenu() function
	}

}

int main() //Main Function
{

	int playerSelectChoice = playerMenu(); //Initializing an int named playerSelectChoice set to the playerMenu() function

	while (playerSelectChoice != 3) //While the user does not input 3
	{
		if (playerSelectChoice == 1) //If playerSelectChoice equals 1
		{
			gameNS(); //Begin the game (call the gameNS() function)
			playerSelectChoice = playerMenu(); //Go the main menu (playerSelectChoice is set to playerMenu() function)
		}

		else if (playerSelectChoice == 2) //If playerSelectChoice equals 2
		{
			gameInstructionKey(); //Display the Game Instructions to the user (call the function gameInstructions())
			playerSelectChoice = playerMenu(); //Go the main menu (playerSelectChoice is set to playerMenu() function)
		}

		else //Else
		{
			return 0; //return 0
		}
	}

	cout << "Goodbye!" << endl; //Output 'Goodbye!' to the user
}