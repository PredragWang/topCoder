"""
Problem Statement
    
It's winter time! Time to play some games.

Four reindeers are playing the following game. The first three of them choose three non-empty strings: A, B, and C. (The strings are not necessarily distinct.) Then, the fourth one (and it happens to be the youngest one) finds a string S that satisfies the following conditions:
S is a subsequence of A. (I.e., either S equals A, or S can be obtained from A by removing some of its characters.)
S is a subsequence of B.
C is a (contiguous) substring of S.
There is no string longer than S that satisfies the previous three conditions.

You are given three tuple (string)s allA, allB and allC. Concatenate all elements of allA, allB and allC to obtain strings A, B and C, respectively. Return the length of the string S. If there is no such string, return 0.


Definition
    
Class: WinterAndReindeers
Method: getNumber
Parameters: tuple (string), tuple (string), tuple (string)
Returns: integer
Method signature: def getNumber(self, allA, allB, allC):


Constraints
- allA, allB and allC will each contain between 1 and 50 elements, inclusive.
- Each element of allA, allB and allC will contain between 1 and 50 characters, inclusive.
- Each element of allA, allB and allC will consist only of uppercase English letters ('A'-'Z').


Examples
0)
{"X"}
{"X", "Y"}
{"X"}
Returns: 1
In this case, A = "X", B = "XY", C = "X". The longest possible string that satisfies conditions from the statement is "X". Thus, the answer is 1.

1)
{"ABCXD"}
{"BCDEF"}
{"CD"}
Returns: 3
The longest possible string in this case is "BCD".

2)
{"WE", "LOVE"}
{"WORKING", "FOR", "SANTA"}
{"JK"}
Returns: 0
No string satisfies all criteria in this case. Thus, the answer is 0.

3)
{"ABCDE"}
{"CDEAB"}
{"B"}
Returns: 2

4)
{"ABCABDEGAXAHDJBAAHFJDXBB", "ABHFHCDALFDJDBBA", "BABBAXAXXX"}
{"ABLOCBAXBAHAJDXBIJKA", "JBABCDAHKFIUDALPJAH", "AABACX"}
{"AXBADXBBAB", "CDD"}
Returns: 23

This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior written consent of TopCoder, Inc. is strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved.
"""

"""
Idea:
The problem is to find the longest common subsequence between A and B containing a specified substring C
Algorithm:
Find (xa, ya) pairs where A[xa, ya] contains the whole subsequence of C
Find (xb, yb) pairs where B[xb, yb] contains the whole subsequence of C
For every (xa, ya) and (xb, yb) combination, longest possible S should has the length:
lcs(A[0, xa-1], B[0, xb-1]) + lcs(A[ya+1, ], B[yb+1, ]) + <length of C>
"""
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
class WinterAndReindeers{
	public:
		int getNumber(vector<string> allA, vector<string> allB, vector<string> allC);
	private:
		vector<vector<int>> lcs(string A, string B);
		vector<vector<int>> lcsReverse(string A, string B);
		vector<int> subSeq(string str, string C);
};
int WinterAndReindeers::getNumber(vector<string> allA, vector<string> allB, vector<string> allC){
	string A("");
	string B("");
	string C("");
	for (string s : allA) A = A + s;
	for (string s : allB) B = B + s;
	for (string s : allC) C = C + s;
	int a = A.length(), b = B.length(), c = C.length();
	vector<vector<int>> lcsAB = lcs(A, B);
	vector<vector<int>> rlcsAB = lcsReverse(A, B);
	vector<int> subSeqAC = subSeq(A, C);
	vector<int> subSeqBC = subSeq(B, C);
	int m = subSeqAC.size(), n = subSeqBC.size();
	int ret = 0;
	int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
	int lcsLeft = 0, lcsRight = 0;
	for (int i = 0; i < m; i += 2) {
		x1 = subSeqAC[i]; 
		y1 = subSeqAC[i+1];
		for (int j = 0; j < n; j += 2) {
			x2 = subSeqBC[j]; 
			y2 = subSeqBC[j+1];
			lcsLeft = ((x1 == 0 || x2 == 0) ? 0 : lcsAB[x1-1][x2-1]);
			lcsRight = ((y1 == a-1 || y2 == b-1) ? 0 : rlcsAB[y1+1][y2+1]);
			ret = max(ret, lcsLeft + lcsRight + c);
		}
	}
	return ret;
}
vector<vector<int>> WinterAndReindeers::lcs(string A, string B) {
	int m = A.length();
	int n = B.length();
	vector<vector<int>> dp(m, vector<int>(n, 0));
	int up = 0, left = 0;
	for (int i = 0; i < m; i ++) {
		for (int j = 0; j < n; j ++) {
			if (A[i] == B[j]) {
				dp[i][j] = (i>0 && j>0 ? dp[i-1][j-1]+1 : 1);
			}
			else {
				up = (i == 0 ? 0 : dp[i-1][j]);
				left = (j == 0 ? 0 : dp[i][j-1]);
				dp[i][j] = max(up, left);
			}
		}
	}
	return dp;
}

vector<vector<int>> WinterAndReindeers::lcsReverse(string A, string B) {
	int m = A.length();
	int n = B.length();
	vector<vector<int>> dp(m, vector<int>(n, 0));
	int down = 0, right = 0;
	for (int i = m-1; i >= 0; i --) {
		for (int j = n-1; j >= 0; j --) {
			if (A[i] == B[j]) {
				dp[i][j] = (i<m-1 && j<n-1 ? dp[i+1][j+1]+1 : 1);
			}
			else {
				down = (i == m-1 ? 0 : dp[i+1][j]);
				right = (j == n-1 ? 0 : dp[i][j+1]);
				dp[i][j] = max(down, right);
			}
		}
	}
	return dp;
}

vector<int> WinterAndReindeers::subSeq(string str, string C){
	vector<int> dp;
	int n = str.length();
	int c = C.length();
	int ptrC = 0;
	for (int i = 0; i <= n-c; i++) {
		if (str[i] != C[0]) {
			continue;
		}
		ptrC = 0;
		for (int j = i; j < n; j++) {
			if (str[j] == C[ptrC]) {
				ptrC ++;
				if (ptrC == c) {
					if (dp.size() > 0 && dp.back() == j) {
						dp.pop_back();
						dp.pop_back();
					}
					dp.push_back(i);
					dp.push_back(j);
					break; 
				}
			}
		}
	}
	return dp;
}
