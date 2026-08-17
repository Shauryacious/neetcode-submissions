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
APPROACH 1: Iterative (Dummy Node + In-Place Splicing)
Time Complexity: O(N + M) | Space Complexity: O(1)
=======================================================================================
Explanation:
We use a `dummy` node to eliminate edge-case initializations. We use a pointer `k` to 
weave the existing nodes together by simply updating their `next` pointers. 
Once one list is exhausted, we attach the entire remainder of the other list in O(1).
=======================================================================================
*/
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        
        // 1. The Dummy Node trick
        ListNode* dummy = new ListNode(-1);
        ListNode* k = dummy;
        
        // 2. Weave the pointers together (No 'new' allocations!)
        while (list1 != NULL && list2 != NULL) {
            if (list1->val <= list2->val) {
                k->next = list1;
                list1 = list1->next;
            } else {
                k->next = list2;
                list2 = list2->next;
            }
            k = k->next;
        }
        
        // 3. The Tail Attach shortcut
        if (list1 != NULL) {
            k->next = list1;
        } else if (list2 != NULL) {
            k->next = list2;
        }
        
        // Return the actual head, skipping the dummy
        return dummy->next;
    }
};

/*
=======================================================================================
APPROACH 2: Recursive (The Elegant Way)
Time Complexity: O(N + M) | Space Complexity: O(N + M) for call stack
=======================================================================================
Explanation:
This is pure magic. We ask: "Which node is smaller?" 
The smaller node becomes the head. What is its `next`? 
Its `next` is simply the result of recursively merging the *rest* of its own list 
with the other list. 
=======================================================================================
*/
class Solution2 {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        
        // The lambda to handle the recursive state
        auto f = [&](ListNode* l1, ListNode* l2, auto&& f) -> ListNode* {
            
            // Base cases: if one list is empty, just return the other
            if (l1 == NULL) return l2;
            if (l2 == NULL) return l1;
            
            // The Trust Fall: Link the smaller node to the merged result of the rest
            if (l1->val <= l2->val) {
                l1->next = f(l1->next, l2, f);
                return l1;
            } else {
                l2->next = f(l1, l2->next, f);
                return l2;
            }
        };
        
        return f(list1, list2, f);
    }
};