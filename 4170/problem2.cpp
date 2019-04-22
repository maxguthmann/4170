#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

int main(){
	//table to hold number of ways to get [score][number of dice]
	vector<vector<int> > oberynTable(41, vector<int>(5, 0));
	//rolls with 1 die are all able to happen in 1 way
	for(int i = 1; i <= 10; i++){
		oberynTable[i][1] = 1;
	}
	
	for(int i = 1; i <= 40; i++){
		for(int numDice = 2; numDice <= 4; numDice++){
			for(int j = 1; j <= i - numDice + 1; j++){
				//similar to problem 1, subtract each possible die value and count how many ways numDice -1 can have that value
				oberynTable[i][numDice] += oberynTable[j][1]*oberynTable[i - j][numDice - 1];
			}
		}
	}
	
	//vector to hold number of rolls that lose to index
	vector<int> oberynOutcomes(40, 0);
	for(int i = 0; i <= 40; i++){
		for(int index = i; index < 40; index++){
			oberynOutcomes[index] += oberynTable[i][4];
		}
	}

	vector<vector<int> > gregorTable(41, vector<int>(9, 0));
	//initalize rolls with 1 die
	for(int i = 1; i <= 5; i++){
		gregorTable[i][1] = 1;
	}
	
	for(int i = 1; i <= 40; i++){
		for(int numDice = 2; numDice <= 8; numDice++){
			for(int j = 1; j <= i - numDice + 1; j++){
				gregorTable[i][numDice] += gregorTable[j][1]*gregorTable[i - j][numDice - 1];
			}
		}
	}
	//tally up gregors wins
	double gregorWins;
	double gregorLoses;
	for(int score = 1; score <= 40; score++){
		//gregor wins is the number of times gregor gets that roll*the number of times it wins
		gregorWins += gregorTable[score][8] * oberynOutcomes[score];
		gregorLoses += gregorTable[score][8] * (10000 - oberynOutcomes[score]);
	}
	//play every possible roll once
	float gregorWinPercentage = gregorWins/(gregorWins + gregorLoses);
	cout<<gregorWinPercentage<<endl;
}
