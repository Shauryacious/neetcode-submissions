// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<stack>
#include<bitset>
#include<unordered_map>
#include<unordered_set>
#include<chrono>
#include<random>
#include<string>
#include<functional>
#include<iomanip>
#include<limits>
#include<array>
#include<utility>
#include<iterator>
#include<cstring>

using namespace std;

// Define Constants & Macros
#define ii int
#define vii vector<int>
#define vvii vector<vector<int>>
#define pii pair<int, int>
#define vpii vector<pii>
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e9 
#define nl "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define py cout<<"YES"<<nl
#define pn cout<<"NO"<<nl
#define pm cout<<"-1"<<nl
#define all(x) (x).begin(), (x).end()

// Typedef
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<string> vs;
typedef vector<pll> vpll;

#define vvpll vector<vpll>

/*
=======================================================================================
PATTERN: Hash Map + Doubly Linked List (LRU Cache)
Time Complexity: O(1) for both get() and put() | Space Complexity: O(Capacity)
=======================================================================================
Explanation:
- We create a custom `Node` struct for the Doubly Linked List.
- `head` and `tail` are dummy nodes. The MRU node is always `head->next`. 
  The LRU node is always `tail->prev`.
- `addNode()` always inserts a node right after the `head` (marking it MRU).
- `deleteNode()` snips a node out of the list by connecting its prev and next neighbors.
- On `get`, if found, we delete it from its current spot and re-add it to the front.
- On `put`, if capacity is full, we locate the LRU (`tail->prev`), erase it from the 
  map, snip it from the list, and then add our new node.
=======================================================================================
*/

class LRUCache {
    
    // Custom Doubly Linked List Node
    struct Node {
        int key;
        int val;
        Node* prev;
        Node* next;
        Node(int k, int v) {
            key = k;
            val = v;
            prev = NULL;
            next = NULL;
        }
    };
    
    // Internal Variables
    int cap;
    unordered_map<int, Node*> m; // Maps key to its Node address
    Node* head;
    Node* tail;

    // Helper Function: Add node right after the dummy head (MRU position)
    void addNode(Node* new_node) {
        Node* temp = head->next;
        
        new_node->next = temp;
        new_node->prev = head;
        
        head->next = new_node;
        temp->prev = new_node;
    }
    
    // Helper Function: Delete a node from its current position
    void deleteNode(Node* del_node) {
        Node* del_prev = del_node->prev;
        Node* del_next = del_node->next;
        
        del_prev->next = del_next;
        del_next->prev = del_prev;
    }

public:
    LRUCache(int capacity) {
        cap = capacity;
        // Initialize dummy head and tail
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        
        // Connect them to each other initially
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (m.find(key) != m.end()) {
            Node* res_node = m[key];
            int ans = res_node->val;
            
            // Mark as recently used by moving to front
            deleteNode(res_node);
            addNode(res_node);
            
            return ans;
        }
        return -1;
    }
    
    void put(int key, int value) {
        // If the key already exists, update its value and move to front
        if (m.find(key) != m.end()) {
            Node* existing_node = m[key];
            existing_node->val = value;
            
            deleteNode(existing_node);
            addNode(existing_node);
        } else {
            // If at capacity, we must evict the LRU item
            if (sz(m) == cap) {
                // The LRU node is the one right before the dummy tail
                Node* lru_node = tail->prev;
                
                // Erase from map, delete from list, free memory
                m.erase(lru_node->key);
                deleteNode(lru_node);
                delete lru_node; 
            }
            
            // Insert the new node
            Node* new_node = new Node(key, value);
            addNode(new_node);
            m[key] = new_node; // Register in map
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */