/*
Problem Statement
    
For an integer n, let F(n) = (n - 0^2) * (n - 1^2) * (n - 2^2) * (n - 3^2) * ... * (n - k^2), where k is the largest integer such that n - k^2 > 0. You are given three long longs lo, hi and divisor. It is guaranteed that divisor will be a prime number. Compute and return the number of integers n between lo and hi, inclusive, such that F(n) is divisible by divisor.

Definition
    
Class:
SparseFactorialDiv2
Method:
getCount
Parameters:
long long, long long, long long
Returns:
long long
Method signature:
long long getCount(long long lo, long long hi, long long divisor)
(be sure your method is public)
    

Constraints
- lo will be between 1 and 1,000,000,000,000, inclusive.
- hi will be between lo and 1,000,000,000,000, inclusive.
- divisor will be between 2 and 997, inclusive.
- divisor will be a prime number.
Examples
0)
4
8
3
Returns: 3
The value of F(n) for each n = 4, 5, ..., 8 is as follows.
F(4) = 4*3 = 12
F(5) = 5*4*1 = 20
F(6) = 6*5*2 = 60
F(7) = 7*6*3 = 126
F(8) = 8*7*4 = 224
Thus, F(4), F(6), F(7) are divisible by 3 but F(5) and F(8) are not.

1)
9
11
7
Returns: 1
F(9) = 9*8*5 = 360
F(10) = 10*9*6*1 = 540
F(11) = 11*10*7*2 = 1540
Only F(11) is divisible by 7.

2)
1
1000000000000
2
Returns: 999999999999
Watch out for the overflow.

3)
16
26
11
Returns: 4

4)
10000
20000
997
Returns: 1211

5)
123456789
987654321
71
Returns: 438184668

This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior written consent of TopCoder, Inc. is strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved.

 */

#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
class SparseFactorialDiv2{
	public:
		long long getCount(long long lo, long long hi, long long divisor);
};
/* The problem is getting the count of distinct numbers where every number is 
 * divisible by divisor when subtracting a square of an integer.
 * For every possible x, 
 * count the numbers divisible by hi-x^2 and lo-1-x^2 and get the difference.
 * Remove duplicate when a smaller x has the same value of (x^2 % divisor).
 * Reason: 
 * If x1^2 % divisor = x2^2 % divisor and x2 > x1. 
 * We get a number N when (N - x2^2) % divisor = 0.
 * (N - x1^2) % divisor = N % divisor - x1^2 % divisor =  N % divisor - x2^2 % divisor = 0
 * Thus N must be included in the number set when trying x1
 */
long long SparseFactorialDiv2::getCount(long long lo, long long hi, long long divisor){
	long long ret = 0;
	long long mX = sqrt(hi);
	vector<bool> computed(divisor, false);
	long long h = 0, l = 0, s = 0;
	for (long long x = 0; x <= mX; x ++) {
		s = x*x;
		if (!computed[s % divisor] || s <= 1){
			h = (hi >= s ? (hi-s)/divisor : 0);
			l = (lo-1 >= s ? (lo-1-s)/divisor : 0);
			ret += (h - l);
		}
		computed[s % divisor] = true;
	}
	return ret;
}
