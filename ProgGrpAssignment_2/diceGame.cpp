#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <fstream>
#include <stdlib.h>

#define MAX_PLAYERS 10

using namespace std;

class Dice {
	private:
		int numSides;

	public:
		// Getter : numSides
		int getNumSides() {
			return this->numSides;
		}
	
		// Perform a single roll of the die
		int roll(int numSides) {
       			int number = rand() % (numSides) + 1; 
        		return number;
		}

		void writeToNumSides(int val) {
			this->numSides = val;
		}

};

class Player{
	private:
		string name;
		int score;
	public:
		// Constructor for Player
		Player(string name, int score) : name(name), score(score) {}

		// Getter : Player Name
		string getName() {
			return this->name;
		}
		// Getter : Score
		int getScore() {
			return this->score;
		}
		// Increases the player's score by a specified value
		void addToScore(int val){
			this->score += val;	
		}
};

/*
	Abstract class DiceGame
*/
class DiceGame{
	protected:
		Player *players[MAX_PLAYERS];
		Dice *dice;
		int numPlayers, numDice;
		
	public:
		// Pure virtual function	
		virtual void play() = 0;

		
		void initPlayers() {
			for (int i = 0; i < MAX_PLAYERS; i++) {
				string name;
				int score;
				
				// Prompt the user for info on each instance of the player class.
				cout << "Enter the name of player " << i+1 << ":";
				cin >> name;
				cout << "Enter the score of player " << i+1 << ":";
				cin >> score;
				
				// Create space in memory for a new Player instance.
				// Uses the Player constructor to write to both private variables.
				Player* new_player = new Player(name, score);
				players[i] = new_player;
			}
		}

		void displayScores() {
			for (int i = 0; i < MAX_PLAYERS; i++) {
				// The '->' operator allows you to reference a method or variable
				// within the structure (in this case, each player instance)
				string name = players[i]->getName();
				int score = players[i]->getScore();
				
				cout << name << ":" << score << endl;
			}
		}
};

int main() {
	// Initialize rand() & test
	srand((unsigned)time(0));
	cout<<rand()<<endl;
	
	return 0;

}
