//============================================================================
// Name        : OBST.cpp
// Author      : Kshitij Patil
// Version     :
// Copyright   : @Kshitij09
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <limits.h>
#include <iomanip>
using namespace std;
class OBST {
	string* key;
	float* p;
	float* q;
	float** cost;			//tree cost
	float** w;				//words cost
	int** r;				//root
	int N;					//No. of keys
public:
	OBST(string ki[],float pi[],float qi[],int n);
	float calculateCost();
	void printMatrix();
	void print(int l,int r);
};
OBST::OBST(string ki[],float pi[],float qi[],int n) {
	N = n;
	key = new string[N];
	p = new float[N];
	q = new float[N];
	this->key = ki;
	this->p = pi;
	this->q = qi;
	cost = new float*[N];
	w = new float*[N];
	r = new int*[N];
	for (int i = 0; i < N; ++i){
		cost[i] = new float[N];
		w[i] = new float[N];
		r[i] = new int[N];
	}

}
float OBST::calculateCost() {
	/*for a single key,
	 * Wi = qi
	 * Ci = 0
	 * Ri = 0
	 */
	for (int i = 0; i < N; i++) {
		w[i][i] = q[i];
		cost[i][i] = 0;
		r[i][i] = 0;
	}

	//Considering chain of length L
	for (int L = 2; L <= N; L++) {
		for (int i = 0; i <= N-L; i++) {
			int j = i+L-1;
			w[i][j] = w[i][j-1] + p[j] + q[j];
			cost[i][j] = INT_MAX;

			for (int k = i+1; k <= j; k++) {
				float c = cost[i][k-1] + cost[k][j];
				if (c < cost[i][j]){
					cost[i][j] = c;
					r[i][j] = k;
				}
			}
			cost[i][j] += w[i][j];
		}
	}
	return cost[0][N-1];
}
void OBST::printMatrix() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N-i; ++j) {
				cout << setw(7) << w[j][j+i];
		}
		cout << endl;
		for (int j = 0; j < N-i; ++j) {
				cout << setw(7) << cost[j][j+i];
		}
		cout << endl;
		for (int j = 0; j < N-i; ++j) {
				cout << setw(7) << r[j][j+i];
		}
		cout << endl;
		cout << endl;
	}
}
void OBST::print(int i,int j) {
	if (i >= j)
		return;
	cout << key[r[i][j]-1] << "   ";
	print(i,r[i][j]-1);
	print(r[i][j],j);
}
int main() {
	string key[] = {"do","if","return","while"};
	float p[] = {0,0.3,0.3,0.1,0.1};
	float q[] = {0.2,0.3,0.1,0.1,0.1};
	int n = 5;

	OBST tree = OBST(key,p,q,n);
	float cost = tree.calculateCost();
	tree.printMatrix();
	cout << "Cost = " << cost << endl;
	cout << "OBST in Preorder :" << endl;
	tree.print(0,n-1);
	cout << endl;
	return 0;
}
