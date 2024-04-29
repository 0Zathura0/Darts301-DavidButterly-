#include "Players.h"


//constructior
Players::Players(std::string PlayerName)
{
	name = PlayerName;
};
//deconstructor
Players::~Players() {};


//function for getting the name and returning it
std::string Players::getName()
{
	return name;
};

//Function for setting the name
void Players::setName(std::string newName) 
{
	name = newName;
};

//functions for getting and setting the accuracy.
int Players::getaccuracy()
{
	return accuracy;
}

void Players::setaccuracy(int newacc)
{
	accuracy = newacc;
}


//functions for getting and setting the score.
int Players::getscore()
{
	return score;
};

void Players::setscore(int newscore)
{
	score = newscore;
};

void Players::resetscore()
{
	score = 501;
};


//functions for getting and setting the SetsWon in players class.
int Players::getSetsWon()
{
	return SetsWon;
};

void Players::setSetsWon(int newset)
{
	SetsWon = SetsWon + newset;
};

void Players::resetSets()
{
	SetsWon = 0;
};


int Players::getgames()
{
	return gameswon;

};

void Players::setgames(int newgame)
{
	gameswon = newgame;
};


int Players::getstrat()
{

	return strat;
};

void Players::setstrat(int newstrat)
{
	strat = newstrat;

}