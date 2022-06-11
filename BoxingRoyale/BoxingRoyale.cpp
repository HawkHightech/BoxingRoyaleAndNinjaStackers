// Author: Alexander Hawkins
// Game Title: Boxing Royale
// Compile: g++ -std=c++11 BoxingRoyale.cpp -o BoxingRoyale
// Compile (cont.): ./BoxingRoyale

#include <iostream> //Include io stream
#include <stdlib.h> //Include std library header file
#include <ctime> //Include time library
#include <numeric> //Include numeric library
#include <math.h> //Include math header file
using namespace std; //Using namespace std (standard)

/*
Pseudocode begin:

	Concept of Game: Two players fight each other in a boxing match.
	The last one standing is the boxing champion.

	Build a class to hold the player's name, health, attack strength and defense ability.
	Each player will go in turn to strike a punch as well as defend themselves.
		Every attack and defense will be a random integer.
	If player one attacks player two and deals damage on player two
		player two's health will go down by the amount of damage that was dealth
	If player two's defense is greater than player one's attack
		no damage will be made
	If player two attacks player one and deals damage on player one
		player one's health will go down by the amount of damage that was dealth
	If player one's defense is greater than player two's attack
		no damage will be made
	
	Players will box until someone is knocked out and there's a boxing champion

Pseudocode ends
*/

class BoxingRoyale //Creating a Class named BoxingRoyale
{
	public: //Public access specifier

		//Attributes
		string name; //Initializing a string named name
		int health; //Initializing an int name health

		//Methods
		BoxingRoyale(string name, int health, int attackCeil, int blockCeil) //Creating a constructor named Boxing with 4 perameters (name, health, attackCeil, blockCeil)
		{
			this->name = name; //Name perameter input is set to name public attribute
			this->health = health; //Health perameter input is set to health public attribute
			this->attackCeil = attackCeil; //AttackCeil perameter input is set to attackCeil private attribute
			this->blockCeil = blockCeil; //BlockCeil perameter input is set to blockCeil private attribute
		}

		int Attack() //Creating a function named Attack with 0 perameters returning an int
		{
			return rand()%this->attackCeil; //Return a random integer of attackCeil input (between 0 and attackCeil)
		}

		int Block() //Creating a function named Block with 0 perameters returning an int
		{
			return rand()%this->blockCeil; //Return a random integer of blockCeil input (between 0 and blockCeil)
		}

	private: //Private access specifier
		
		//Attributes
		int attackCeil; //Initializing an int named attackCeil
		int blockCeil; //Initializing an int named blockCeil
};

class Boxingfield: public BoxingRoyale //Creating a Class Inheritance (from BoxingRoyale) named Boxingfield
{
	public: //Public access specifier

		//Methods
		static string boxingRounds(BoxingRoyale& playerOne, BoxingRoyale& playerTwo) //Creating a function named boxingRounds with two perameters (pass by reference)
		{
			string boxingVocab[4] = {"jabs", "crosses", "hooks", "uppercuts"}; //Initializing an array for boxing terms
			int playerOneAttackAmt = playerOne.Attack(); //Initializing an int named playerOneAttackAmt set to the attack function for player one
			int playerTwoBlockAmt = playerTwo.Block(); //Initializing an int named playerTwoBlockAmt set to the block function for player two
			int damageForPlayerTwo = (playerOneAttackAmt - playerTwoBlockAmt); //Initializing an int named damageForPlayerTwo set to (playerOneAttackAmt - playerTwoBlockAmt)

			if (damageForPlayerTwo <= 0) //If Damage is less than or equal to 0
			{
				damageForPlayerTwo = 0; //Damage is set to 0
			}

			playerTwo.health = (playerTwo.health - damageForPlayerTwo); //The player's health equals (health - given damage)

			if (playerTwo.health > 0) //If the player's health is greater than 0
			{
				cout << playerOne.name << " " << boxingVocab[rand()%4] << " " << playerTwo.name << " and creates " << damageForPlayerTwo << " damage." << endl; //Display the player's boxing style and damage they made
				cout << playerTwo.name << "'s health is at " << playerTwo.health << "." << endl; //Display the player's health
			}

			else if (playerTwo.health <= 0) //If the player's health is less than or equal to 0
			{
				playerTwo.health = 0; //Set health to 0 (avoids negative output)
				cout << playerOne.name << " " << boxingVocab[rand()%4] << " " << playerTwo.name << " and creates " << damageForPlayerTwo << " damage." << endl; //Display the player's boxing style and damage they made
				cout << playerTwo.name << "'s health is at " << playerTwo.health << "." << endl; //Display the player's health
				cout << playerTwo.name << " has been Knocked Out & " << playerOne.name << " is the Boxing Champion!" << endl; //Display the player that has been KO'd and the player that is the Boxing Champion
				return "KO!"; //return a string 'KO!'
			}

			return "Boxing Continues"; //Return a string 'Boxing Continues'
		}

		static void beginBoxing(BoxingRoyale& playerOne, BoxingRoyale& playerTwo) //Creating a function named boxingBoxing with two perameters (pass by reference)
		{
			while (true) //While loop that runs until break statement
			{
				if (Boxingfield::boxingRounds(playerOne, playerTwo) == "KO!") //If boxingRounds function returns KO!
				{
					cout << "End of Game" << endl; //Display End of Game
					break; //End program
				}

				else if (Boxingfield::boxingRounds(playerTwo, playerOne) == "KO!") //If boxingRounds function returns KO!
				{
					cout << "End of Game" << endl; //Display End of Game
					break; //End program
				}

				else //else
				{
					cout << "New Round" << endl; //Display New Round
				}
			}
		}
};

int main() //main function
{
	srand(time(NULL)); //Initializing the random numbers generators
	BoxingRoyale Ai("Ai", 300, 40, 15); //Creating an object named BoxingRoyale named Ai
	BoxingRoyale Kenzo("Kenzo", 300, 30, 30); //Creating an object named BoxingRoyale named Kenzo
	BoxingRoyale Hawk("Hawk", 250, 40, 30); //Creating an object named BoxingRoyale named Hawk


	Boxingfield::beginBoxing(Ai, Kenzo); //Call beginBoxing function with the two objects (Ai, Kenzo)

	return 0; //return 0
}