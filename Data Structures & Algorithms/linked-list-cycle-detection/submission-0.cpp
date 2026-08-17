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

/*
=======================================================================================
PATTERN: Fast & Slow Pointers (Floyd's Tortoise and Hare)
Time Complexity: O(N) | Space Complexity: O(1)
=======================================================================================
Problem: LeetCode 141 - Linked List Cycle

Intuition:
- We launch two pointers from the head. Fast moves by 2, Slow moves by 1.
- If there is a cycle, Fast will lap Slow and they will eventually point to the 
  exact same memory address. 
- If Fast reaches a `NULL` node or `fast->next` is `NULL`, it means the list has an 
  end. Thus, no cycle.
=======================================================================================
*/

class Solution {
public:
    bool hasCycle(ListNode *head) {
        
        // Initialize both runners at the starting line
        ListNode *fast = head;
        ListNode *slow = head;
        
        // Fast runner checks for the finish line (NULL)
        while (fast != NULL && fast->next != NULL) {
            
            // Fast moves 2 steps, Slow moves 1 step
            fast = fast->next->next;
            slow = slow->next;
            
            // If they collide, they are trapped in a loop!
            if (fast == slow) {
                return true;
            }
        }
        
        // Fast hit a NULL, meaning the list terminates safely.
        return false;
    }
};