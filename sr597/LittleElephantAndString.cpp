/*
Problem Statement
    
Little Elephant from the Zoo of Lviv likes strings.

You are given a string A and a string B of the same length. In one turn Little Elephant can choose any character of A and move it to the beginning of the string (i.e., before the first character of A). Return the minimal number of turns needed to transform A into B. If it's impossible, return -1 instead.

Definition
    
Class: LittleElephantAndString
Method: getNumber
Parameters: string, string
Returns: int
Method signature: int getNumber(string A, string B) (be sure your method is public)

Limits
    
Time limit (s):
2.000
Memory limit (MB):
64

Constraints
- A will contain between 1 and 50 characters, inclusive.
- B will contain between 1 and 50 characters, inclusive.
- A and B will be of the same length.
- A and B will consist of uppercase letters ('A'-'Z') only.


Examples
0)
"ABC"
"CBA"
Returns: 2
The optimal solution is to make two turns. On the first turn, choose character 'B' and obtain string "BAC". On the second turn, choose character 'C' and obtain "CBA".

1)
"A"
"B"
Returns: -1
In this case, it's impossible to transform A into B.

2)
"AAABBB"
"BBBAAA"
Returns: 3

3)
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"ZYXWVUTSRQPONMLKJIHGFEDCBA"
Returns: 25

4)
"A"
"A"
Returns: 0

5)
"DCABA"
"DACBA"
Returns: 2

This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior written consent of TopCoder, Inc. is strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved.
*/

#include <string>
#include <iostream>
using namespace std;
class LittleElephantAndString{
    public:
        int getNumber(string A, string B);
};
int LittleElephantAndString::getNumber(string A, string B){
    if (A.length() != B.length()) return -1;
    int len = A.length();
    int countCharA[256], countCharB[256];
    fill_n(countCharA, 256, 0);
    fill_n(countCharB, 256, 0);
    for (int n = 0; n < len; n ++) {
        countCharA[(int)A[n]] ++;
        countCharB[(int)B[n]] ++;
    }
    for (int n = 0; n < 256; n ++) {
        if (countCharA[n] != countCharB[n]) return -1;
    }
    // find the min i where LCS[A, B[i, end]]= len(B[i, end])
    int lcs[len][len];
    int down, right, diagonal;
    for (int i = len - 1; i >= 0; i --) {
        for (int j = len - 1; j >= 0; j --) {
            if (A[i] == B[j]) {
                if (i == len - 1 || j == len - 1) {
                    lcs[i][j] = 1;
                } 
                else {
                    lcs[i][j] = lcs[i+1][j+1] + 1;
                }
            }
            else {
                down = (i == len - 1 ? 0 : lcs[i+1][j]);
                right = (j == len - 1 ? 0 : lcs[i][j+1]);
                diagonal = ((i == len - 1 || j == len - 1) ? 0 : lcs[i+1][j+1]);
                lcs[i][j] = max(down, right);
                lcs[i][j] = max(lcs[i][j], diagonal);
            }
        }
    }
    for (int i = 0; i < len; i ++) {
        if (lcs[0][i] == len - i) {
            return i;
        } 
    }
    return len;
}
