#include <vector>
#include <iostream>
using namespace std;


int countCombinations(int value, vector<int> coins){
	vector<vector<int> > memoize(value + 1, vector<int>(coins.size(), 1));
	int countMinusCoinValue;
	//start at i = 1 because i = 0 is a vectors of 1s
	for(int i = 1; i <= value; i++){
		//optimize because coins[0] = 1
		memoize[i][0] = 1;
		for(size_t j = 1; j < coins.size(); j++){
			if(i < coins[j]){
				countMinusCoinValue = 0;
			}
			else{
				countMinusCoinValue = memoize[i-coins[j]][j];
			}
			memoize[i][j] = memoize[i][j-1] + countMinusCoinValue;	
		}
	}
	return memoize[value][coins.size() - 1];
}

int main(){
	vector<int> coins = {1, 5, 10, 20, 50, 100};
	int value = 500;
	int count = countCombinations(value, coins);
	cout<<count<<endl;
}
