// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>

using namespace std;

#define ii int
#define vii vector<int>
#define vvii vector<vector<int>>
#define pii pair<int, int>
#define vpii vector<pii>
#define pb push_back
#define MOD 1000000007
#define ll long long
#define vll vector<ll>
#define vvll vector<vll>
#define all(x) (x).begin(), (x).end()
#define INF 1e9

/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

/*
=======================================================================================
APPROACH 1: Manual Binary Search (The Core Algorithm)
Time Complexity: O(log N) | Space Complexity: O(1)
=======================================================================================
Intuition:
- We set our search space from `1` to `n`.
- We calculate `mid` safely to avoid overflow.
- We call the `guess(mid)` API once per loop and store the result. (Calling it multiple 
  times in the if-else conditions would be inefficient!).
- If result is 0, we found it.
- If result is -1, our guess is too big. We discard the right half (`hi = mid - 1`).
- If result is 1, our guess is too small. We discard the left half (`lo = mid + 1`).
=======================================================================================
*/
class Solution {
public:
    int guessNumber(int n) {
        int lo = 1;
        int hi = n;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            
            int res = guess(mid);
            
            if (res == 0) {
                return mid; // Target found
            } 
            else if (res == -1) {
                hi = mid - 1; // Guess is higher than pick, search lower half
            } 
            else {
                lo = mid + 1; // Guess is lower than pick, search upper half
            }
        }

        return -1;
    }
};