#include <iostream>

#include <iomanip>

using namespace std;

#include <cstdlib>

#include <ctime>

#include <fstream>

#include <string>

#include <cstring>

 

#define MAX_PLAYERS 10

 

class Dice

{

private:

    int numSides;

 

public:

    // Perform a single roll of the die

    int roll(int numSides)

    {

        int number = rand() % (numSides) + 1; // generating a random interger between the range 1 - numSides

        return number;

    }

};

 

class Player

{

private:

    string name;

    int score;

 

public:

    // Getter : Player Name

    string getName()

    {

        return name;

    }

    // Getter : Score

    int getScore()

    {

        return score;

    }

    // Increases the player's score by a specified value

    void addToScore(int val)

    {

        score = score + val;

    }

    Player(string n, int s) // parametrized constructor

    {

        name = n;

        score = s;

    }

};

 

class DiceGame

{

 

protected:

    Player *players[MAX_PLAYERS];

    Player *tempplayers[MAX_PLAYERS];

    Dice *dice;

    int numPlayers, numDice;

 

    unsigned int arr_length = 0;

 

public:

    //        Pure virtual function

    virtual void play() = 0;

 

    DiceGame(int a, int b) // parametrized constructor

    {

        numPlayers = a;

        numDice = b;

    }

 

    int FindMaxIndex(size_t len, int rolls[]) // finding the index position of the maximum element

    {

        int maximum = rolls[0];

        int index = 0;

        for (int i = 0; i <= len; i++)

        {

            xxxxxxxxxxxxxxxxxxxxx

            {

                index = i;

                maximum = rolls[i];

            }

        }

        return index;

    }

 

    void writeScoresToFile()

    {

        ofstream fw("scorecard.txt", std::ofstream::out | std::ios_base::app);

 

        // check if file was successfully opened for writing

        xxxxxxxxxxxxxxxxxxxxx

        {

            // store array contents to text file

            for (int i = 0; i < numPlayers; i++)

            {

                // writing player info into the file

               

            }

            xxxxxxxxxxxxxxxxxxxxx

        }

        else

            cout << "Problem with opening file";

    }

 

    void getHighestScore()

    {

        string lines; // getting the total number of lines in the file

        int line_count = 0;

        ifstream mFile("scorecard.txt");

        xxxxxxxxxxxxxxxxxxxxx // opening

        {

            while (mFile.peek() != EOF)

            {

                getline(mFile, lines);

                xxxxxxxxxxxxxxxxxxxxx

            }

        }

        mFile.close();

        cout << "The player with the highest score:";

        int finalscores[line_count - 1]; // obtaining, converting and storing all player scores in an array

        int pos = 0;

        int winner_position;

        string line;

        ifstream myfile("scorecard.txt");

        xxxxxxxxxxxxxxxxxxxxx

 

        {

            while (getline(myfile, line))

            {

                int start = line.find(':');

                xxxxxxxxxxxxxxxxxxxxx

                xxxxxxxxxxxxxxxxxxxxx

 

                // declaring character array

                char char_array[n + 1];

 

                // copying the contents of the string to char array

                strcpy(char_array, score.c_str());

                xxxxxxxxxxxxxxxxxxxxx

 

                finalscores[pos] = score1;

                pos += 1;

            }

            size_t len = sizeof(finalscores) / sizeof(finalscores[0]);

            winner_position = FindMaxIndex(len, finalscores);

            xxxxxxxxxxxxxxxxxxxxx

        }

        else

            cout << "Unable to open file";

 

        int count = 0; // finding the name of the player with maximum score

 

        ifstream myfile1("scorecard.txt");

        if (myfile1.is_open())

        {

            while (getline(myfile1, line))

            {

                if (count == winner_position)

                {

                    xxxxxxxxxxxxxxxxxxxxx

                    xxxxxxxxxxxxxxxxxxxxx

                    cout << winner_name;

                }

                count += 1;

            }

            myfile1.close();

        }

    }

 

    void initPlayers()

    {

        string pname;                        // player name

        int pscore;                          // player score

        for (int i = 0; i < numPlayers; i++) // taking player name and score as input and storing it in player array

        {

            cout << "Enter the player name: ";

            cin >> pname;

            cout << "Enter the score: ";

            cin >> pscore;

            players[i] = new Player(pname, pscore);

            xxxxxxxxxxxxxxxxxxxxx

        }

    }

 

    void displayScores()

    {

        xxxxxxxxxxxxxxxxxxxxx

        for (int i = 0; i < len; i++) // looping through player array and displaying their name and score

        {

            cout << players[i]->getName() << ":" << players[i]->getScore() << endl;

        }

    }

};

 

class BostonDice : public xxxxxxxx // creating a inherited class

{

private:

    xxxxxxxxxxxxxxxxxxxxx

    xxxxxxxxxxxxxxxxxxxxx

 

public:

    BostonDice(int a, int b) : DiceGame(a, b) // parametrized constructor

    {

        xxxxxxxxxxxxxxxxxxxxx

        xxxxxxxxxxxxxxxxxxxxx

    }

 

    // finding the maximum element in an array

    int FindMax(size_t len, int rolls[])

    {

        int maximum = rolls[0];

        for (int i = 0; i <= len; i++)

        {

            if (rolls[i] > maximum)

            {

                xxxxxxxxxxxxxxxxxxxxx

            }

        }

        return maximum;

    }

 

    void play()

    {

        int nDiceRoll;

        int upside;

        int PlayerScores[nplayers];

        int TempPlayerScore;

        int TempPlayerRolls[nDiceRoll];

 

        cout << "Enter the number of times you want to roll the dice: ";

        cin >> nDiceRoll;

 

        initPlayers();

        Dice BostonDiceGame;

 

        xxxxxxxxxxxxxxxxxxxxx // iterating through all the players

        {

            TempPlayerScore = 0;

            for (int j = 0; j < nDiceRoll; j++) // rolling the dice nDiceRoll times

            {

                int TempPlayerRolls[nDiceRoll];

                xxxxxxxxxxxxxxxxxxxxx // finding the maximum number for each set of rolls

                {

                    upside = BostonDiceGame.roll(nDiceSides);

                    TempPlayerRolls[k] = upside;

                }

                xxxxxxxxxxxxxxxxxxxxx

                TempPlayerScore += FindMax(len, TempPlayerRolls); // updating player score with maximum number

                cout << endl;

            }

            xxxxxxxxxxxxxxxxxxxxx

            cout << players[i]->getName() << " has a score of " << TempPlayerScore << endl; // displaying maximum score

        }

        xxxxxxxxxxxxxxxxxxxxx

        int pos = FindMaxIndex(len, PlayerScores);

        int maxscore = FindMax(len, PlayerScores);

        cout << "Winner of Boston Dice Game is " << players[pos]->getName() << " with a score of " << maxscore << endl;

 

        players[pos]->addToScore(10); // adding a score of 10 to the player

    }

};

 

class KnockOut : public xxxxxx // creating a inherited class

{

private:

    int nplayers;   // number of players in the game

    int nDiceSides; // number of sides the dice has

 

    int KnockOutScore = 0;

 

public:

    xxxxxxxxxxxxxxxxxxxxx // parametrized constructor

    {

        nplayers = a;

        nDiceSides = b;

    }

 

    void play()

    {

        Dice KnockOutDice;

        int nDiceRoll;

        int upside;

 

        int tempnplayers = nplayers;

 

        cout << "Enter the number of times you want to roll the dice: ";

        cin >> nDiceRoll;

 

        xxxxxxxxxxxxxxxxxxxxx // calculating the knockout score for a given number of dice rolls

        {

            upside = KnockOutDice.roll(nDiceSides);

            KnockOutScore += upside;

        }

        cout << "The KnockOut Score is " << KnockOutScore << endl; // displaying the knockout score

 

        initPlayers();

 

       xxxxxxxxxxxxxxxxxxxxx // running the loop until 1 player is left

        {

            int temp;

            for (int j = 0; j < nplayers; j++) // iterating through each player

            {

                temp = 0;

                xxxxxxxxxxxxxxxxxxxxx // finding the sum of their dice rolls and storing it in temp

                {

                    upside = KnockOutDice.roll(nDiceSides);

                    temp += upside;

                }

 

                if (temp == KnockOutScore) // checking if sum of dice rolls is equal to the knockout score

                {

                    cout << "The knockout score matches for player " << tempplayers[j]->getName() << ":" << temp << endl;

                    for (int l = j; l < nplayers; l++) // if yes, removing the player from the players array

                    {

 

                        xxxxxxxxxxxxxxxxxxxxx

                    }

                    nplayers -= 1;

                }

            }

        }

 

        cout << "The winner of the game is: " << (tempplayers[0]->getName()) << endl; // displaying the winner name

        string a = tempplayers[0]->getName();

        for (int x = 0; x < tempnplayers; x++)

        {

            string b = players[x]->getName();

            if (a == b)

            {

                players[x]->addToScore(15); // adding a score of 10 to the player

            }

        }

    }

};

 

int main()

{

    DiceGame *game;

    srand((xxxxx)time(xxxxx));

 

    cout << endl;

    int no_of_players, dice_sides;

    char choice;

 

    cout << "Enter the number of players playing the game: ";

    cin >> no_of_players;

    cout << "Enter the number of sides the dice has: ";

    cin >> dice_sides;

 

    cout << "Enter the game you want to play (Boston[B] or Knockout[K]): ";

    cin >> choice;

 

    if (choice == 'B')

    {

        BostonDice game1(xxxxx, dice_sides);

        game = &game1;

        game->play();

    }

    else if (choice == 'K')

    {

        KnockOut game1(no_of_players, xxxxx);

        game = &game1;

        game->play();

    }

 

    game->writeScoresToFile();

    game->getHighestScore();

 

    delete game;

    return 0;

}
