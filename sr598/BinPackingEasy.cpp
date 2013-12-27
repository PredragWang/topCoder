/*
Problem Statement
    
Fox Ciel has some items. The weight of the i-th (0-based) item is item[i]. She wants to put all items into bins.  The capacity of each bin is 300. She can put an arbitrary number of items into a single bin, but the total weight of items in a bin must be less than or equal to 300.  You are given the vector <int> item. It is known that the weight of each item is between 101 and 300, inclusive. Return the minimal number of bins required to store all items.
Definition
    
Class: BinPackingEasy
Method: minBins
Parameters: vector <int>
Returns: int
Method signature: int minBins(vector <int> item) (be sure your method is public)

Limits
Time limit (s):
2.000
Memory limit (MB):
64

Constraints
- item will contain between 1 and 50 elements, inclusive.
- Each element of item will be between 101 and 300, inclusive.


Examples
0)
{150, 150, 150, 150, 150}
Returns: 3
You have five items and each bin can hold at most two of them. You need at least three bins.

1)
{130, 140, 150, 160}
Returns: 2
For example, you can distribute the items in the following way:
Bin 1: 130, 150
Bin 2: 140, 160

2)
{101, 101, 101, 101, 101, 101, 101, 101, 101}
Returns: 5

3)
{101, 200, 101, 101, 101, 101, 200, 101, 200}
Returns: 6

4)
{123, 145, 167, 213, 245, 267, 289, 132, 154, 176, 198}
Returns: 8

This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior written consent of TopCoder, Inc. is strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved.
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class BinPackingEasy{
    public:
    int minBins(vector <int> item){
        sort(item.begin(), item.end());
        int len = item.size();
        int ret = 0;
        int countMin = 0;
        int ptr1 = 0, ptr2 = len - 1;
        while (item[ptr1]==100) {
            ptr1 ++;
            countMin ++;
        }
        ret += countMin/3;
        ptr1 = (countMin/3)*3;
        while (ptr1 < ptr2) {
            if (item[ptr1]+item[ptr2] <= 300) {
                ret += 1;
                ptr2 --;
                ptr1 ++;
            }
            else {
                ret += 1;
                ptr2 --;
            }
        }
        if (ptr1 == ptr2) ret += 1;
        return ret;
    }
};
