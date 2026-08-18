// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>
#include<set>

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
APPROACH: Multiset (Red-Black Tree) 
Time Complexity: O(N log K) | Space Complexity: O(K)
=======================================================================================
Problem: LeetCode 23 - Merge k Sorted Lists

Explanation:
- We use a `multiset<pair<int, ListNode*>>`. The `int` acts as the sorting key.
- `*ms.begin()` gives us the smallest pair in O(1) time.
- `ms.erase(ms.begin())` removes the smallest element in O(log K) time.
- Note: We strictly erase by iterator `ms.erase(ms.begin())`. If we erased by value, 
  it would delete ALL nodes with that same value!
=======================================================================================
*/

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        
        // The CP trick: sorting by the first element of the pair
        multiset<pair<int, ListNode*>> ms;
        
        // 1. Seed the multiset with the first node of every list
        for (auto head : lists) {
            if (head != NULL) {
                ms.insert({head->val, head});
            }
        }
        
        ListNode* dummy = new ListNode(-1);
        ListNode* tail = dummy;
        
        // 2. Process the multiset until it's empty
        while (!ms.empty()) {
            
            // Get the pair at the very front (the absolute minimum)
            auto it = ms.begin();
            ListNode* min_node = it->second;
            
            // Erase this specific iterator from the multiset
            ms.erase(it);
            
            // Attach the smallest node to our merged list
            tail->next = min_node;
            tail = tail->next;
            
            // If this node has a successor, insert it into the multiset!
            if (min_node->next != NULL) {
                ms.insert({min_node->next->val, min_node->next});
            }
        }
        
        ListNode* head = dummy->next;
        delete dummy;
        
        return head;
    }
};


/*
=======================================================================================
APPROACH 2: Divide and Conquer (In-Place)
Time Complexity: O(N log K) | Space Complexity: O(1)
=======================================================================================
Explanation:
We aggressively reuse the `mergeTwoLists` logic. By repeatedly merging adjacent pairs 
of lists, the total number of lists halves in every pass. This simulates a Merge Sort 
tree structure, guaranteeing that no node is traversed more than `log K` times.
Because `mergeTwoLists` is O(1) space, this entire algorithm is O(1) space!
=======================================================================================
*/

class Solution2 {
public:
    
    // The exact same optimal helper function you wrote earlier!
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(-1);
        ListNode* tail = dummy;
        
        while (l1 != NULL && l2 != NULL) {
            if (l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        
        if (l1) tail->next = l1;
        if (l2) tail->next = l2;
        
        ListNode* head = dummy->next;
        delete dummy;
        return head;
    }
    
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return NULL;
        
        int n = lists.size();
        
        // The step size dictates how far apart the two lists we are merging are.
        // pass 1: step = 1 (merge 0&1, 2&3, 4&5)
        // pass 2: step = 2 (merge 0&2, 4&6)
        // pass 3: step = 4 (merge 0&4)
        for (int step = 1; step < n; step *= 2) {
            
            for (int i = 0; i + step < n; i += step * 2) {
                // Merge list `i` and list `i + step`, store the result back into list `i`
                lists[i] = mergeTwoLists(lists[i], lists[i + step]);
            }
        }
        
        // The fully merged list accumulates at index 0
        return lists[0];
    }
};