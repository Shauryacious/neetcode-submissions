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
APPROACH 1: Iterative (Three Pointers)
Time Complexity: O(N) | Space Complexity: O(1)
=======================================================================================
Explanation:
We maintain three pointers: `prev`, `curr`, and `next_node`. 
At every step, `next_node` temporarily saves the rest of the list so we don't lose it.
Then, we reverse the `curr` pointer to face `prev`. 
Finally, we shift both `prev` and `curr` one step forward.
=======================================================================================
*/
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = NULL;
        ListNode* curr = head;
        
        while (curr != NULL) {
            // 1. Scout ahead to save the rest of the list
            ListNode* next_node = curr->next;
            
            // 2. Reverse the current node's pointer
            curr->next = prev;
            
            // 3. Move the pointers one step forward
            prev = curr;
            curr = next_node;
        }
        
        // At the end, curr falls off into NULL, making prev the new head!
        return prev;
    }
};

/*
=======================================================================================
APPROACH 2: Recursive (The Trust Fall)
Time Complexity: O(N) | Space Complexity: O(N) due to Call Stack
=======================================================================================
Explanation:
I have refactored your lambda function to be much cleaner! 
Instead of maintaining a global `ans` variable and looking two steps ahead, the lambda 
just returns the `new_head` directly.
When `f(node->next)` returns, the sub-list is fully reversed. The node right after us 
(`node->next`) is now at the tail of that reversed sub-list. We simply tell it to 
point back at us, and we cap ourselves with NULL.
=======================================================================================
*/
class Solution2 {
public:
    ListNode* reverseList(ListNode* head) {
        
        // The lambda perfectly captures the recursive state
        auto f = [&](ListNode* node, auto&& f) -> ListNode* {
            
            // Base Case: If the list is empty or we reached the last node, 
            // this node is the new head of the reversed list!
            if (node == NULL || node->next == NULL) {
                return node;
            }
            
            // Recursive Trust Fall: Reverse everything after me
            ListNode* new_head = f(node->next, f);
            
            // My neighbor is now at the end of the reversed list. 
            // Make him point back at me!
            node->next->next = node;
            
            // Cap my own pointer so we don't create a cycle
            node->next = NULL;
            
            return new_head;
        };
        
        return f(head, f);
    }
};