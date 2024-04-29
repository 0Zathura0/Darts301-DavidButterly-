
//inclusion of the libraries
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
			return DBoard::NeigborArray[0][d]; //using the array from DBoard class
		else if (r < 96)
			return DBoard::NeigborArray[1][d];
		else if (r < 98)
			return 3 * d;
		else
			return 2 * d;
}


//input validation to make sure accuracy is not going above 100 or below 0
int accval(int acc) {
	while (acc < 0 || acc > 100) //while acc ! in peramiters, keep asking for correct no 
	{

		//will consistently ask for input while the user hasnt entered a valid number
		cout << "Enter player1s accuracy within the peramiters of 0 and 100: " << endl;
		cin >> acc; //setting the accuracy

	}
	//return acc
	return acc;
}







//main function
int main()
{

	//this section is initializing the players
	//creating the player name variable
	std::string player_name;


	//creating the accuracy variable
	int accuracy;
	
	//ask for and store the name in player name and then create the object and give them the name
	cout << "Enter player1s name please: " << endl;
	cin >> player_name;
	Players* player1 = new Players(player_name); //creating ponter to obkect

	//asks for and stores the accuracy, and then validated it using the function and finally stores the returned value
	cout << "Enter player1s accuracy please: " << endl;
	cin >> accuracy; //setting the accuracy
	accuracy = accval(accuracy);// input validation
	player1->setaccuracy(accuracy);

	//asks if the user would allow p1 to use the strategy and stores the chosen option
	int p1s = 0;
	cout << "would you like for this player to use stratagy?: 0 for no 1 for yes" << endl;
	cin >> p1s;


	//sets the strat variable in the class
	player1->setstrat(p1s);



	//asks for and stores p2s name then creates the object
	cout << "Enter player2s name please: " << endl;
	cin >> player_name;
	Players* player2 = new Players(player_name);//creating pointer to object


	//asks for and stores the accuracy, then validates and stores it
	cout << "Enter player2s accuracy please: " << endl;
	cin >> accuracy; //setting the accuracy
	accuracy = accval(accuracy);//input val

	//sets the accuracy in the class
	player2->setaccuracy(accuracy);



	//asks if the user wants p2 to use the strat and stores the chosen option
	int p2s = 0;
	cout << "would you like for this player to use stratagy?: 0 for no 1 for yes" << endl;
	cin >> p2s;

	//stores the options in the class
	player2->setstrat(p2s);


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


	// prints the names of the players too the screen
	cout << player1->getName() << " | " << player2->getName() << endl;

	int occurance[15] = { 0 }; //i chose 15 as if 2 people play till one hits 7, thats to total amount of possible score combinations there are.
	//int setresults[2][100001] = {0}; //i chose 100000 here as we want to simulate 100000 games at maximum
	int possible_results[2][14] = { {7,7,7,7,7,7,7,6,5,4,3,2,1,0}, //listing all of the possible results from the scores
									{0,1,2,3,4,5,6,7,7,7,7,7,7,7} };

	//creating the p1 and p2 variables for later use.
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

				//loop for length of possible outcomes array, this allows for looping of the possible outcomes array to see if this score matches any seen there
				for (int j = 0; j < 14; j++) {

					//if sets won by each player match any possible score, add 1 to the occurencce in that value
					if (possible_results[0][j] == player1->getSetsWon() && possible_results[1][j] == player2->getSetsWon()) {

						// add one to the current value in the array
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





			//if enemy is ahead by large margin, risk it for a biscuit----------------- these first 3 should activate when the player has strat enabled.

			//if player enemy score is < 150 and current is > 250 and has strat enabled do 
			if (PlayerArray[!current]->getscore() <= 150 && PlayerArray[current]->getscore() > 250 && PlayerArray[current]->getstrat() == 1)
			{

				//set target to 20
				int target = 20;

				//score = the stored score - the throw function
				//throwing a treble and passing in target and the current players accuracy
				score = PlayerArray[current]->getscore() - throw_treble(target, PlayerArray[current]->getaccuracy());
				
				//set the score for the current player
				PlayerArray[current]->setscore(score);



			}
			// if enemy is < 100 and current > 190 do
			else if (PlayerArray[!current]->getscore() <= 100 && PlayerArray[current]->getscore() >= 190 && PlayerArray[current]->getstrat() == 1)
			{

				int target = 20;

				//score = the stored score - the throw function
				score = PlayerArray[current]->getscore() - throw_treble(target, PlayerArray[current]->getaccuracy());
				
				//store to class
				PlayerArray[current]->setscore(score);

			}

			// if enemy less than 50 and current > 150 and has strat 1 do
			else if (PlayerArray[!current]->getscore() <= 50 && PlayerArray[current]->getscore() >= 150 && PlayerArray[current]->getstrat() == 1)
			{

				int target = 20;

				//score = the stored score - the throw function
				score = PlayerArray[current]->getscore() - throw_treble(target, PlayerArray[current]->getaccuracy());
				
				//store to class
				PlayerArray[current]->setscore(score);

			}
			// if > 50 throw for bull
			else if (PlayerArray[current]->getscore() >= 50)
			{
				//score = the stored score - the throw function
				score = PlayerArray[current]->getscore() - throw_bull(PlayerArray[current]->getaccuracy());

				//store to class
				PlayerArray[current]->setscore(score);

			}

			//if less than 50 and odd do----------------------------------------
			else if (PlayerArray[current]->getscore() < 50 && PlayerArray[current]->getscore() % 2 != 0) // im using the % to determine if the score is even or odd, 0 means even !0 means odd				{
			{		//if the number is odd then set target to 1 to get back to an even number as the only way to win is by a double.

				//set targ 1
				int target = 1;

				//score = the stored score - the throw function this time thowing single
				score = PlayerArray[current]->getscore() - throw_single(target, PlayerArray[current]->getaccuracy());

				//if not 1 and greater than 0 then do 
				if (score != 1 && score > 0)
				{
					//save to class
					PlayerArray[current]->setscore(score);

				}
				//if the scoore is in fact 1 do nothing, to simulate keepig score what it was prior to 1
				else if (score == 1)
				{


				}
				//also do nothing
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

			//if less than 50 and even-----------------------------------------
			else if (PlayerArray[current]->getscore() < 50 && PlayerArray[current]->getscore() % 2 == 0)
			{


				//devide the score by 2, as it is even then use that as the target.
				int target = PlayerArray[current]->getscore() / 2;
				
				//score = the stored score - the throw function
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

				//do nothing
				else if (score < 0)
				{



				}
				// if 0 save sets won to class and reset score to play again 
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


	//loop for 14
	for (int i = 0; i < 14; i++)
	{
		//frequency = occurence / number of games played and timesed by 100, static_cast<double> allows the occurences to be a double
		double freq = static_cast<double>(occurance[i]) / nogames * 100;

		//print all of the possible results and their corresponding frequency
		cout << possible_results[0][i] << " | " << possible_results[1][i] << " | " << freq << "%" << endl;


	}

	//to remove from heap
	delete player1, player2;

	//done to allow viewing of theh exe results rather than have it close the eindow instantly
	system("Pause");

}// end of main
