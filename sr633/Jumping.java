/*
Problem Statement
    
Frog Suwako lives on a two-dimensional plane. She likes to jump. Currently, she is located in the point (0, 0). She would like to reach the point (x, y). You are given the ints x and y.   Suwako wants to reach the desired destination in a specific way: using a series of jumps with pre-determined lengths. You are given these lengths in a int[] jumpLenghts. For example, if jumpLengths = { 2, 5 }, Suwako must make a jump of length exactly 2, followed by a jump of length exactly 5.   Note that Suwako can jump onto arbitrary points in the plane, they are not required to have integer coordinates. Return "Able" (quotes for clarity) if Suwako is able to reach her desired destination from (0, 0) using the desired sequence of jump lengths. Otherwise, return "Not able".
Definition
    
Class: Jumping
Method: ableToGet
Parameters: int, int, int[]
Returns: String
Method signature: String ableToGet(int x, int y, int[] jumpLengths)
(be sure your method is public)

Limits
   
Time limit (s): 2.000
Memory limit (MB): 256

Constraints
- x will be between -1,000 and 1,000, inclusive.
- y will be between -1,000 and 1,000, inclusive.
- len will contain between 1 and 50 elements, inclusive.
- Each element in len will be between 1 and 1,000, inclusive.

Examples
0)
5
4
{2, 5}
Returns: "Able"
One possibility is to jump from (0, 0) to (2, 0), and then from (2, 0) to (5, 4).

1)
3
4
{4}
Returns: "Not able"
The distance from (0, 0) to (3, 4) is 5. You cannot get there using a single jump of length 4 - it is too short.

2)
3
4
{6}
Returns: "Not able"
The distance from (0, 0) to (3, 4) is 5. You cannot get there using a single jump of length 6 - it is too long.

3)
0
1
{100, 100}
Returns: "Able"
Here, one possible solution looks as follows: Let t = sqrt(100*100 - 0.5*0.5). Suwoko will make her first jump from (0, 0) to (t, 0.5), and her second jump from (t, 0.5) to (0, 1).

4)
300
400
{500}
Returns: "Able"

5)
11
12
{1,2,3,4,5,6,7,8,9,10}
Returns: "Able"

6)
11
12
{1,2,3,4,5,6,7,8,9,100}
Returns: "Not able"

This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior written consent of TopCoder, Inc. is strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved.
*/

import java.util.*;
public class Jumping{
  /*
  Just need to check whether the jumps and the distance can form a polygon
  */
  public String ableToGet(int x, int y, int[] jumpLengths) {
    int n = jumpLengths.length;
    double dist = Math.sqrt((double)(x*x+y*y));
    double totalLen = dist;
    double maxEdge = dist;
    for (int i = 0; i < n; i ++) {
      totalLen += (double)jumpLengths[i];
      maxEdge = Math.max((double)jumpLengths[i], maxEdge);
    }
    if (totalLen - maxEdge >= maxEdge) { // polygon check
      return "Able";
    }
    else {
      return "Not able";
    }
  }
}
