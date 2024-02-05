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
					flag = true;
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
				score = stoi(scoreStr);
				
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
			/*
			for (Player* player : players) {
				cout << "Player: " << player->getName() << "    Score: " << player->getScore() << endl;
				cout << endl << knockOutScore;
			}
			*/

			// Game loop
			bool gameInProgress = true;

			while (gameInProgress == true) {
				vector<Player*>::iterator currentPlayer = players.begin();
				while (currentPlayer != players.end()) {
					int playerScore = 0;

					// Roll all of the dice and add them to obj currentPlayer
					for (int i = 0; i < numDice; ++i) {
						playerScore += dice->roll();
					}

					cout << (*currentPlayer)->getName() << " rolls: " << playerScore << endl;

					if (playerScore == knockOutScore) {
						cout << (*currentPlayer)->getName() << " gets knocked out!" << endl;
						currentPlayer = players.erase(currentPlayer); // Remove the current player
					} else {
						++currentPlayer;
					}

					if (players.size() == 1) {
						gameInProgress = false;
						cout << "Winner: " << players[0]->getName() << endl << endl;
						(*currentPlayer)->addToScore(1);
						break;
					}

				}
			}

			delete dice;
			
		}
};

class BostonDiceGame : public DiceGame {
	public:
		void play() override {
			initPlayers();
			dice = new Dice(numDiceSides); // Task description said to assume 6-sided dice.

			int highestScore = 0;
			Player * winner = nullptr;

			for (Player* player : players) {
				int score = 0;
				int diceToRoll = numDice;
				
				// Loop through all dice rolls, getting the highest one out of each bunch.
				while (diceToRoll > 0) {
					int highestRoll = 0;
					for (int i = 0; i < diceToRoll; ++i) {
						int roll = dice->roll();
						highestRoll = max(highestRoll, roll);
					}
					score += highestRoll;
					cout << player->getName() << " rolls, preserving: " << highestRoll << endl;
					--diceToRoll;
				}

				// Update the player's score
				player->addToScore(score);

				if (score > highestScore) {
					highestScore = score;
					winner = player; // Update the winner's pointer
				}
			}

			// Display updated scores, and the winner after all rounds are complete.
			displayScores();

			if (winner != nullptr) {
				cout << "Winner: " << winner->getName() << " with score: " << highestScore << endl;
			}

			delete dice;
		}
};
			


int main() {
	// Initialize rand()
	srand((unsigned)time(0));

	int gameChoice;
	DiceGame* game = nullptr;
	
	cout << "1. Boston Dice Game." << endl;
	cout << "2. Knockout Dice Game." << endl;

	do {
		cout << "Select what game you want to play: ";
		cin >> gameChoice;

		switch (gameChoice) {
			case 1:
				game = new BostonDiceGame();
				break;
			case 2:
				game = new KnockOutGame();
				break;
			default:
				cout << "Invalid input. Please try again." << endl;
				continue;
		}
		break;
	} while (1);
	
	if (game != nullptr) {
		game->play();
		delete game;
	}
	
	return 0;

}
