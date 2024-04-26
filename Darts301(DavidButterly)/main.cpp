#include <iostream>
#include "DBoard.h"
#include "AimFunctions.h"
#include "Players.h"
#include "functions.cpp"
using namespace std;

int throw_bull(int acc) {

	//  Throw for the bull with accuracy p%  (20<p<85)

	int r = rand() % 100;

	if (r < (acc - 20))
		return 50;
	else if (r < 85)
		return 25;
	else
		return 1 + rand() % 20;
}


int throw_treble(int targ, int acc) {

	//  return result of throwing for treble d with accuracy p%  (o<90)


	int r = rand() % 100;

	if (r < acc)
		return 3 * targ;
	else if (r < 90)
		return targ;
	else if (r < 93)
		return 3 * DBoard::NeigborArray[0][targ];
	else if (r < 96)
		return 3 * DBoard::NeigborArray[1][targ];
	else if (r < 98)
		return DBoard::NeigborArray[0][targ];
	else
		return DBoard::NeigborArray[1][targ];
}


int throw_double(int targ, int acc) {

	//  return result of throwing for double d with accuracy 80%

	int r = rand() % 100;


	//using the accuracy here, can be used and if a miss occurs due to the accuracy then the player will be punished with a miss.
	if (r < acc)
		return 2 * targ;
	else if (r < 85)
		return 0;
	else if (r < 90)
		return targ;
	else if (r < 93)
		return 2 * DBoard::NeigborArray[0][targ];
	else if (r < 96)
		return 2 * DBoard::NeigborArray[1][targ];
	else if (r < 98)
		return DBoard::NeigborArray[0][targ];
	else
		return DBoard::NeigborArray[1][targ];
}



int throw_single(int d, int acc) {

	//  return result of throwing for single d with accuracy 88% (or 80% for the outer)

	int r = rand() % 100;

	if (d == 25) {		// outer  80%
		if (r < acc)
			return 25;
		else if (r < 90)
			return 50;
		else
			return 1 + rand() % 20;
	}
	else			// 1 to 20 single
		if (r < acc)
			return d;
		else if (r < 92)
			return DBoard::NeigborArray[0][d];
		else if (r < 96)
			return DBoard::NeigborArray[1][d];
		else if (r < 98)
			return 3 * d;
		else
			return 2 * d;
}








int main()
{

	//this section is initializing the players
	std::string player_name;
	int accuracy;

	cout << "Enter player1s name please: " << endl;
	cin >> player_name;
	Players* player1 = new Players(player_name); //creating ponter to obkect
	cout << "Enter player1s accuracy please: " << endl;
	cin >> accuracy;
	player1->setaccuracy(accuracy);
	

	cout << "Enter player2s name please: " << endl;
	cin >> player_name;
	Players* player2 = new Players(player_name);//creating pointer to object
	cout << "Enter player2s accuracy please: " << endl;
	cin >> accuracy;
	player2->setaccuracy(accuracy);


	//setting up the player arrays
	Players* PlayerArray[2];
	PlayerArray[0] = player1;
	PlayerArray[1] = player2;

	//i decided to allow the user to decide whos going first
	int first = 0;

	//ask to input number of player
	do
	{
		cout << "whos first 1 for player1 or 2 for player 2?: ";
		cin >> first;

	} while (first < 1 || first > 2); //untill its between 1 or 2 for inpt val
	
	first = first - 1; //-1 to interact with player arrays


	//declaring how many games to simulate.
	int nogames = 0;
	cout << "How many games do you wish to simulate?" << endl;
	cin >> nogames;

	//setting up the current player variable which will allow simple swapping between players
	bool current = first;

	cout << player1->getName() << " | " << player2->getName() << endl;

	
	for (int i = 0; i < nogames; i++)
	{
		int score = 0;





		PlayerArray[0]->resetSets();
		PlayerArray[1]->resetSets();


		while (PlayerArray[0]->getSetsWon() !=7 || PlayerArray[1]->getSetsWon() != 7)
		{


			for(int j = 0; j < 3; j++)
			{


				//if the score is above 50 go for bull untill < 50 is reached-----------------
				if (PlayerArray[current]->getscore() >= 50)
				{
					score = PlayerArray[current]->getscore() - throw_bull(PlayerArray[current]->getaccuracy());
					PlayerArray[current]->setscore(score);
					
				}



				//if less than 50 and odd----------------------------------------
				else if (PlayerArray[current]->getscore() < 50 && PlayerArray[current]->getscore() % 2 != 0)
				{
					int target = 1;

					score = PlayerArray[current]->getscore() - throw_single(target, PlayerArray[current]->getaccuracy());

					//the below section of code checks if the score is greater than 0 and not == 1
					if (score != 1 && score >= 0)
					{
						PlayerArray[current]->setscore(score);
						
					}
					//if the scoore is in fact either 1 or somehow less than 0 loop untill it is not.
					else if (score == 1)
					{


					}
					else if (score < 0)
					{

						PlayerArray[!current]->setSetsWon(1);
						PlayerArray[0]->resetscore();
						PlayerArray[1]->resetscore();
					}
					
				}

				//if less than 50 and even-----------------------------------------
				else if (PlayerArray[current]->getscore() < 50 && PlayerArray[current]->getscore() % 2 == 0)
				{
					int target = PlayerArray[current]->getscore() / 2;

					score = PlayerArray[current]->getscore() - throw_double(target, PlayerArray[current]->getaccuracy());

					//the below section of code checks if the score is greater than 0 and not == 1
					if (score != 1 && score >= 0)
					{
						PlayerArray[current]->setscore(score);
						
					}
					//if the scoore is in fact either 1 or somehow less than 0 loop untill it is not.
					else if (score == 1)
					{
					

					}
					else if (score < 0)
					{

						PlayerArray[!current]->setSetsWon(1);
						PlayerArray[0]->resetscore();
						PlayerArray[1]->resetscore();
					}



				}

				//if less than 10 and odd-------------------------
				else if (PlayerArray[current]->getscore() < 10 && PlayerArray[current]->getscore() % 2 != 0)
				{
					int target = 1;
					score = PlayerArray[current]->getscore() - throw_single(target, PlayerArray[current]->getaccuracy());


					//the below section of code checks if the score is greater than 0 and not == 1
					if (score != 1 && score >= 0)
					{
						PlayerArray[current]->setscore(score);
						
					}
					//if the scoore is in fact either 1 or somehow less than 0 loop untill it is not.
					else if (score == 1)
					{


					}
					else if (score < 0)
					{

						PlayerArray[!current]->setSetsWon(1);
						PlayerArray[0]->resetscore();
						PlayerArray[1]->resetscore();
					}
				
				}

				//if less than or equil to 10 and even-----------------------------------
				else if (PlayerArray[current]->getscore() <= 10 && PlayerArray[current]->getscore() % 2 == 0)
				{
					int target = PlayerArray[current]->getscore() / 2;

					score = PlayerArray[current]->getscore() - throw_double(target, PlayerArray[current]->getaccuracy());

					//the below section of code checks if the score is greater than 0 and not == 1
					if (score != 1 && score >= 0)
					{
						PlayerArray[current]->setscore(score);
						
					}
					//if the scoore is in fact either 1 or somehow less than 0 loop untill it is not.
					else if (score == 1)
					{


					}
					else if (score < 0)
					{

						PlayerArray[!current]->setSetsWon(1);
						PlayerArray[0]->resetscore();
						PlayerArray[1]->resetscore();
					}
	
				}



				//if the current players score is == 0 they win the set.
				else if (PlayerArray[current]->getscore() == 0)
				{

					
					PlayerArray[current]->setSetsWon(1);
					PlayerArray[0]->resetscore();
					PlayerArray[1]->resetscore();
				}


			}// end of number darts thrown for loop

			current = !current;


		
			cout << player1->getSetsWon() << " | " << player2->getSetsWon() << endl;
		}//end of while


	}//end of nogames for loop



	

	
		










		//to remove from heap
		delete player1, player2;
}// end of main