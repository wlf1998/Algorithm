/***************
 * Longest Common Subsequence Problem
 * Lifeng Wang
 * 2018.11.24
 * *************/
#include <vector>
#include <string>
#include <iostream>
#include <string.h>
#include <sstream>
using namespace std;

/*********
 * output lcs
 * veca is the length of Xi and Yj
 * *******/ 
int LCS_length(const string &str1, const string &str2, vector< vector<int> > &veca, vector< vector<int> > &vecb) {
	int i, j;
	int biggest = 0;
	if (str1 == "" || str2 == "")
		return 0;
	for (i = 0; i <= str1.length(); i++) {
		veca[i][0] = 0;
	}
	for (j = 0; j <= str2.length(); j++) {
		veca[0][j] = 0;
	}
	for (i = 1; i <= str1.length(); i++) {
		for (j = 1; j <= str2.length(); j++) {
			//if Xi-1 == Yj-1, then lcs is veca[i-1][j-1]+1
			//at this time, veca[i][j] = 1 shows that str[i-1] is an element of child LCS
			if (str1[i - 1] == str2[j - 1]) {
				veca[i][j] = veca[i - 1][j - 1] + 1;
				vecb[i][j] = 1;
			}
			else {
				if (veca[i - 1][j] >= veca[i][j - 1]) {
					veca[i][j] = veca[i - 1][j];
					vecb[i][j] = 2;
				}
				else {
					veca[i][j] = veca[i][j-1];
					vecb[i][j] = 3;
				}
			}
		}
	}
	return veca[str1.length()][str2.length()];
}

/**************
 * print an LCS order
 * the order is up first, then left
 * ***********/ 
void PrintOneLCS(vector<vector<int> > &vecb, string &str1, int i, int j) {
	if (i == 0 || j == 0)
		return;
	if (vecb[i][j] == 1) {
		PrintOneLCS(vecb, str1, i - 1, j - 1);
		cout << str1[i - 1] << " ";
	}
	else if (vecb[i][j] == 2)
		PrintOneLCS(vecb, str1, i -1, j);
	else
		PrintOneLCS(vecb, str1, i, j - 1);
}

/***************
 * init veca to a two-dimensional array, line = str1.length + 1, raw = str2.length +1 
 * veca is the length of Xi and Yj
 * vecb is the best solution of veca[i][j]'s child problem
 * *************/
int main() {
	string input;
	getline(cin, input);
	stringstream ss(input);
	string str1, str2;
	ss >> str1;
	ss >> str2;
	vector< vector<int> > veca(str1.length() + 1, vector<int>(str2.length() + 1));
	vector< vector<int> > vecb(str1.length() + 1, vector<int>(str2.length() + 1));
	cout << LCS_length(str1, str2, veca, vecb) << endl;
	PrintOneLCS(vecb, str1, str1.length(), str2.length());
	return 0;
}
