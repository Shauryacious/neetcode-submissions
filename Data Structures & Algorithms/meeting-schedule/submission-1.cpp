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
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Solution {
public:
    bool canAttendMeetings(vector<Interval>& intervals) {
        int n = intervals.size();
        
        // If there are 0 or 1 meetings, there can't be any conflicts.
        if (n <= 1) return true;
        
        // 1. Custom Comparator to sort Interval objects by Start Time
        auto cmp = [&](const Interval& a, const Interval& b) -> bool {
            return a.start < b.start; 
        };
        
        // Apply the lambda to sort chronologically
        sort(all(intervals), cmp);
        
        // 2. Check for overlapping adjacent meetings
        for (int i = 1; i < n; i++) {
            
            // If the current meeting starts strictly before the previous one ends...
            if (intervals[i].start < intervals[i - 1].end) {
                return false; // Conflict detected!
            }
        }
        
        return true;
    }
};