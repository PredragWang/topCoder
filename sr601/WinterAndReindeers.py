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

import sys
class WinterAndReindeers:
    def getNumber(self, allA, allB, allC):
        A = ''.join(allA)
        B = ''.join(allB)
        C = ''.join(allC)
        a = len(A)
        b = len(B)
        c = len(C)
        if c > a or c > b:
            return 0
        lcsAB = self.lcs(A, B)
        rlcsAB = self.lcs(A[::-1], B[::-1])
        subSeqAC = self.subSeq(A, C)
        subSeqBC = self.subSeq(B, C)
        ret = 0
        m = len(subSeqAC)
        n = len(subSeqBC)
        for i in range(0, m, 2):
            startA = subSeqAC[i]
            endA = subSeqAC[i+1]
            for j in range(0, n, 2):
                startB = subSeqBC[j]
                endB = subSeqBC[j+1]
                lcsLeft = 0 if (startA == 0 or startB == 0) else lcsAB[startA-1][startB-1]
                lcsRight = 0 if (endA==a-1 or endB ==b-1) else rlcsAB[a-endA-2][b-endB-2]
                ret = max(ret, lcsLeft + lcsRight + c)
        return ret
                
    def lcs(self, A, B):
        m = len(A)
        n = len(B)
        if m == 0 or n == 0:
            return None
        dp = [n*[0] for i in range(m)]
        for i in range(m):
            for j in range(n):
                if A[i] == B[j]:
                    dp[i][j] = 1 if (i==0 or j==0) else dp[i-1][j-1] + 1
                else:
                    up = 0 if i == 0 else dp[i-1][j]
                    left = 0 if j == 0 else dp[i][j-1]
                    dp[i][j] = max(up, left)
        return dp
        
    def subSeq(self, str, C):
        n = len(str)
        c = len(C)
        dp = []
        for i in range(n-c+1):
            if not str[i] == C[0]:
                continue
            ptrC = 0
            for j in range(i, n):
                if str[j] == C[ptrC]:
                    ptrC = ptrC + 1
                    if ptrC == c:
                        if len(dp) > 0 and dp[-1] == j:
                            dp = dp[:-2]
                        dp.append(i)
                        dp.append(j)
                        break
        return dp
