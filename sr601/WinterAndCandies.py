"""
Problem Statement
    
It's winter time! You have some candies arranged in a row and now you want to choose some of them and give them to your friend.

You are given a tuple (integer) type. Each candy has a type, which is some positive integer. For each i, type[i] represents the type of i-th candy. You want to choose some non-empty subset of candies with the following property: if the number of candies you choose is K, their types must be precisely all the numbers from 1 to K, inclusive. Return the number of different ways to do that. (Two ways are considered different if there exists some candy that is chosen in only one of them.)
Definition
    
Class: WinterAndCandies
Method: getNumber
Parameters: tuple (integer)
Returns: integer
Method signature: def getNumber(self, type):

Limits
    
Time limit (s): 2.000
Memory limit (MB): 256

Notes
- The answer will always fit in a signed 32-bit integer.

Constraints
- type will contain between 1 and 50 elements, inclusive.
- Each element of type will be between 1 and 50, inclusive.

Examples
0)
{1, 3, 2}
Returns: 3
There are 7 possible non-empty subsets in this case:
(1)
(3)
(2)
(1, 3)
(1, 2)
(3, 2)
(1, 3, 2)
Out of them, only first, fifth and seventh are valid. Thus, the answer is 3.

1)
{1, 1, 2}
Returns: 4
Note that the chosen subset can never contain two elements with the same type.

2)
{1, 3, 2, 5, 7, 4, 5, 4}
Returns: 9

3)
{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}
Returns: 62

4)
{2}
Returns: 0

This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior written consent of TopCoder, Inc. is strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved.
"""

import sys
class WinterAndCandies:
    def getNumber(self, type):
        if len(type) == 0:
            return -1
        sortedTypes = sorted(type)
        dp = [] 
        #dp[i] is the number of ways to choose candies when max candy type is i+1
        maxType = 0
        count = 0
        for i in range(len(sortedTypes)):
            if sortedTypes[i] == maxType:
                dp[-1] = (dp[-1]/count) * (count+1)
                count = count + 1    
            elif sortedTypes[i] == maxType + 1:
                maxType = maxType + 1
                if len(dp) == 0:
                    dp.append(1)
                else:
                    dp.append(dp[-1])
                count = 1
            else:
                break
        if len(dp) == 0:
            return 0
        ret = 0
        for i in range(len(dp)):
            ret = ret + dp[i]
        return ret
