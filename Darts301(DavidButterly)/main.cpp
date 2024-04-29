
#include <iostream>
#include "DBoard.h"
#include "AimFunctions.h"
#include "Players.h"
#include "functions.cpp"
using namespace std;



//with the example functions i added in the accuracy section in all of them, so they work mostly the same unless the accuracy is too low.
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

int accval(int acc) {
	while (acc < 0 || acc > 100) //while acc ! in peramiters, keep asking for correct no 
	{
		cout << "Enter player1s accuracy within the peramiters of 0 and 100: " << endl;
		cin >> acc; //setting the accuracy

	}

	return acc;
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
	cin >> accuracy; //setting the accuracy
	accuracy = accval(accuracy);// input validation
	player1->setaccuracy(accuracy);


	bool p1s = 0;
	cout << "would you like for this player to use stratagy?: 0 for no 1 for yes" << endl;
	cin >> p1s;

	if (p1s == 0)
	{
		p1s = false;
	}
	else
	{
		p1s = true;
	}





	cout << "Enter player2s name please: " << endl;
	cin >> player_name;
	Players* player2 = new Players(player_name);//creating pointer to object


	cout << "Enter player2s accuracy please: " << endl;
	cin >> accuracy; //setting the accuracy
	accuracy = accval(accuracy);//input val


	player2->setaccuracy(accuracy);




	bool p2s = 0;
	cout << "would you like for this player to use stratagy?: 0 for no 1 for yes" << endl;
	cin >> p2s;




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

	int occurance[15] = { 0 }; //i chose 15 as if 2 people play till one hits 7, thats to total amount of possible score combinations there are.
	//int setresults[2][100001] = {0}; //i chose 100000 here as we want to simulate 100000 games at maximum
	int possible_results[2][14] = { {7,7,7,7,7,7,7,6,5,4,3,2,1,0}, //listing all of the possible results from the scores
									{0,1,2,3,4,5,6,7,7,7,7,7,7,7} };
	int p1 = 0;
	int p2 = 0;

	//loop for the number of games requested----------------------------------------------
	for (int i = 0; i < nogames; i++)
	{


		//set score to 0
		int score = 0;
		int counter = 0;

		//infinite loop untill broken--------------------------------------
		while (true)
		{
			//set win condition to activate when a player reaches 7 sets--------------------------------------------
			if (PlayerArray[0]->getSetsWon() == 7 || PlayerArray[1]->getSetsWon() == 7)
			{

				//set number of games won
				PlayerArray[current]->setgames(1);

				//cout << player1->getSetsWon() << "|" << player2->getSetsWon();





				for (int j = 0; j < 14; j++) {


					if (possible_results[0][j] == player1->getSetsWon() && possible_results[1][j] == player2->getSetsWon()) {
						occurance[j]++;

					}
				}
				//resetting the player back to first selection and the sets back to 0
				current = first;
				PlayerArray[0]->resetSets();
				PlayerArray[1]->resetSets();

				//break to break the while and then start the process again untill the no of games wanted is reached
				break;
			}



			
			//if the score is above 50 go for bull untill < 50 is reached-----------------
			if (PlayerArray[current]->getscore() >= 50)
			{

				score = PlayerArray[current]->getscore() - throw_bull(PlayerArray[current]->getaccuracy());
				PlayerArray[current]->setscore(score);

			}


			//if less than 50 and odd----------------------------------------
			else if (PlayerArray[current]->getscore() < 50 && PlayerArray[current]->getscore() % 2 != 0) // im using the % to determine if the score is even or odd, 0 means even !0 means odd				{
			{		//if the number is odd then set target to 1 to get back to an even number as the only way to win is by a double.
				
				
				int target = 1;

				score = PlayerArray[current]->getscore() - throw_single(target, PlayerArray[current]->getaccuracy());
				if (score != 1 && score > 0)
				{
					PlayerArray[current]->setscore(score);

				}
				//if the scoore is in fact 1 do nothing, to simulate keepig score what it was prior to 1
				else if (score == 1)
				{


				}
				else if (score < 0)
				{

				}

				//if the score is 0 add 1 to sets won and reset the score
				else if (score == 0)
				{
					PlayerArray[current]->setSetsWon(1);
					PlayerArray[0]->resetscore();
					PlayerArray[1]->resetscore();
				}
			}
			//the below section of code checks if the score is greater than 0 and not == 1


			

			//if less than 50 and even-----------------------------------------
			else if (PlayerArray[current]->getscore() < 50 && PlayerArray[current]->getscore() % 2 == 0)
			{

				
				//devide the score by 2, as it is even then use that as the target.
				int target = PlayerArray[current]->getscore() / 2;

				score = PlayerArray[current]->getscore() - throw_double(target, PlayerArray[current]->getaccuracy());

				//the below section of code checks if the score is greater than 0 and not == 1
				if (score != 1 && score > 0)
				{
					PlayerArray[current]->setscore(score);

				}
				//if the scoore is in fact either 1 or somehow less than 0 loop untill it is not.
				else if (score == 1)
					{


				}
				else if (score < 0)
				{



				}
				else if (score == 0)
				{

					PlayerArray[current]->setSetsWon(1);
					PlayerArray[0]->resetscore();
					PlayerArray[1]->resetscore();
				}

			}
			



			//swapping the current player after no off darts for loop.
			current = !current;
			




		}//end of while



	}//end of nogames for loop



	for (int i = 0; i < 14; i++)
	{
		double freq = static_cast<double>(occurance[i]) / nogames * 100;
		cout << possible_results[0][i] << " | " << possible_results[1][i] << " | " << freq << "%" << endl;


	}

	//to remove from heap
	delete player1, player2;
}// end of main
