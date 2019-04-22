#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

int main(){
	vector<vector<int> > matrix(15, vector<int>(15));
	
	//read in the matrix
	int value;
	int maximum = 0;
	int maxI, maxJ;
	for(int i = 0; i < 15; i++){
		for(int j = 0; j < 15; j++){
			cin>>value;
			matrix[i][j] = value;
			if(value > maximum){
				maximum = value;
			}
		}
	}
	vector<vector<int> > copy(matrix);
  //turn to minimization problem for hungarian algorithm
	for(int i = 0; i < 15; i++){
		for(int j = 0; j < 15; j++){
			matrix[i][j] = maximum - matrix[i][j];
		}
	}
	//hungarian algorithm
	vector<int> u(16), v(16), p(16), way(16);
	for(int i = 1; i < 15; ++i){
		p[0] = i;
		int j0 = 0;
		vector<int> minv(16, 10000);
		vector<char> used(16, false);
		do{
			used[j0] = true;
			int i0 = p[j0];
			int delta = 10000;
			int j1;
			for(int j = 1; j <= 15; ++j){
				if(!used[j]){
					int cur = matrix[i0][j] - u[i0] - v[j];
					if(cur < minv[j]){
						minv[j] = cur;
						way[j] = j0;
					}
					if(minv[j] < delta){
						delta = minv[j];
						j1 = j;
					}
				}
			}
			for(int j = 0; j <= 15; ++j){
				if(used[j]){
					u[p[j]] += delta;
					v[j] -= delta;
				}
				else{
					minv[j] -= delta;
				}
			}
			j0 = j1;
		} while(p[j0] != 0);
		do{
			int j1 = way[j0];
			p[j0] = p[j1];
			j0 = j1;
		} while(j0);
	}

	vector<int> answer(15);
	for(int i = 0; i <= 15; ++i){
		answer[p[i]] = i;
	}

	int sum = 0;
	for(int i = 0; i < 15; i++){
		sum += copy[i][answer[i]];
	}
	cout<<sum<<endl;
}

