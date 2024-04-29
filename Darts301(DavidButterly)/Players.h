#pragma once
#include <iostream> 
#include <string>

class Players
{

private:

	//declaring the name variable
	std::string name;

	//declaring the accuracy variable
	int accuracy = 0;

	//declaring the current score o the player
	int score = 501;

	//declaring the SetsWon Variable
	int SetsWon = 0;

	//declaring games won
	int gameswon = 0;


	//declare strat
	int strat = 0;

public:
	Players(std::string PlayersName);
	~Players();

	std::string getName();
	void setName(std::string newName);

	int getaccuracy();
	void setaccuracy(int newacc);

	int getscore();
	void setscore(int newscore);
	void resetscore();

	int getSetsWon();
	void setSetsWon(int newset);
	void resetSets();

	int getgames();
	void setgames(int newgame);

	int getstrat();
	void setstrat(int newstrat);


};

