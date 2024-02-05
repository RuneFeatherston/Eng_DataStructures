#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime> 
#include <fstream>
#include <stdlib.h>
#include <limits>

using namespace std;

class Dice {
	private:
		int numSides;

	public:
		// Constructor for Dice
		Dice(int numSides) : numSides(numSides) {}

		// Getter : numSides
		int getNumSides() {
			return this->numSides;
		}
	
		// Perform a single roll of the die
		int roll() {
       			int number = rand() % (numSides) + 1; 
        		return number;
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
		// Rewrote the array to instead be a vector. This allows us to dynamically append players as needed.
		vector<Player*> players;
		Dice *dice;
		int numPlayers, numDice, numDiceSides;
		
	public:
		// Pure virtual function	
		virtual void play() = 0;

		
		void initPlayers() {
			// Prompt for number of players. This is defined in the DiceGame because both
			// games, Knock Out and Boston accept the number of players from the user.
			while (1) {
				bool flag = false;

				cout << "Enter the amount of players: ";
				cin >> numPlayers;

				if (numPlayers < 2) {
					cout << "Invalid value. There must be atleast 2 players." << endl;
					flag = true;
				} 

				cout << "Enter the amount of dice for the game: ";
				cin >> numDice;
				if (numDice < 1) {
					cout << "Invalid value. There must be atleast 1 dice." << endl;
					flag = true;
				}

				cout << "Enter the amount of sides per dice: ";
				cin >> numDiceSides;
				if (numDiceSides < 2) {
					cout << "Invalid value. There must be atleast 2 sides for the dice." << endl;
					flag == true;
				}

				cout << endl;

				if (flag == true) {
					continue;
				}
				break;
			}
			
			cout << "Number of players: " << numPlayers << endl;
			cout << "Number of dice: " << numDice << endl;
			cout << "Number of sides per dice: " << numDiceSides << endl;
			cout << endl;

			for (int i = 0; i < numPlayers; i++) {
				string name;
				string scoreStr;
				int score;
				
				// Prompt the user for info on each instance of the player class.
				cout << "Enter the name of player " << i+1 << ":";
				cin >> name;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
				// There was some weird behavior with the input handling involving
				// the stream detecting a new line. This fix worked, but I'm not 
				// completely sure what was going on...
				cout << "Enter the score of player " << i+1 << ":";
				getline(cin, scoreStr);
				try {
					score = stoi(scoreStr);
					break;
				} catch (invalid_argument& ia) {
					cerr << "ERROR: Invalid input. Must be numerical.\n";
				}

				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
				// Create space in memory for a new Player instance.
				// Uses the Player constructor to write to both private variables.
				players.push_back(new Player(name, score));
				
			}
		}

		void displayScores() {
			for (int i = 0; i < numPlayers; i++) {
				// The '->' operator allows you to reference a method or variable
				// within the structure (in this case, each player instance)
				string name = players[i]->getName();
				int score = players[i]->getScore();
				
				cout << name << ":" << score << endl;
			}
		}
};

class KnockOutGame : public DiceGame {
	public:
		void play() override {
			initPlayers();
			dice = new Dice(numDiceSides);

			// Calculate the Knock Out score (sum of N dice rolls)
			int knockOutScore = 0;
			for (int i = 0; i < numDice; ++i) {
				knockOutScore += dice->roll();
			}
			// Test to ensure that all players and scores are assigned properly.
			for (Player* player : players) {
				cout << "Player: " << player->getName() << "    Score: " << player->getScore() << endl;
				cout << endl << knockOutScore;
			}

			// Game loop
		}
};


int main() {
	// Initialize rand()
	srand((unsigned)time(0));

	KnockOutGame game;

	game.play();
	
	return 0;

}
