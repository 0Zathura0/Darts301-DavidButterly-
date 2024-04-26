#pragma once
#include <iostream>

class DBoard
{
public:

	//setting the arry up here makes more sense to me rather than setting it up
	//for every function as per the example code

	//this allows me to call on it wen it is needed.
	//declaring the variable as static so i dont need to make an object of the DB just to call the array

	static constexpr short int NeigborArray[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
		{0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };

};

