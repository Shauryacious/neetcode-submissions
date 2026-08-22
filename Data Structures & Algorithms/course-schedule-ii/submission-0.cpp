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
#include<functional>
#include<iterator>
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
PATTERN: Kahn's Algorithm (BFS Topological Sort)
Time Complexity: O(V + E) | Space Complexity: O(V + E) 
Where V is numCourses and E is the number of prerequisites.
=======================================================================================
Explanation:
- `indeg` (In-degree) tracks how many prerequisites a course currently has.
- We build a directed graph where an edge `u -> v` means "u must be taken before v".
- We seed the queue with all courses that have 0 prerequisites.
- As we process each course, we "unlock" its neighbors by decrementing their in-degree.
- If a neighbor's in-degree hits 0, it is ready to be taken, so we push it to the queue.
- If a cycle exists, the nodes in the cycle will never reach an in-degree of 0, 
  so our final `topo` array will be smaller than `n`.
=======================================================================================
*/

class Solution {
public:
    vector<int> findOrder(int n, vector<vector<int>>& pre) {
        // Step 1: Build Adjacency List and In-Degree Array
        vector<vector<int>> adj(n);
        vector<int> indeg(n, 0);

        for(auto p : pre){
            int a = p[0], b = p[1];
            // b is the prerequisite for a. Therefore, the directed edge is b -> a.
            adj[b].pb(a);
            
            // a requires one more prerequisite to be completed
            indeg[a]++;
        }

        vector<int> topo;
        queue<int> q;

        // Step 2: Seed the queue with all courses that require 0 prerequisites
        for(int i = 0; i < n; i++) {
            if(indeg[i] == 0) {
                q.push(i);
            }
        }

        // Step 3: Process the queue (Take the courses)
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            
            // Course 'u' is successfully taken, add it to our schedule
            topo.pb(u);

            // Step 4: Unlock dependent courses
            for(auto v : adj[u]) {
                indeg[v]--; // One prerequisite fulfilled for course 'v'
                
                // If all prerequisites for 'v' are met, it is ready to be taken
                if(indeg[v] == 0) {
                    q.push(v);
                }
            }
        }

        // Step 5: Cycle Verification
        // If we successfully processed all 'n' courses, return the schedule.
        if(topo.size() == n){
            return topo;
        }

        // Otherwise, a cycle exists (deadlock), making it impossible.
        return {};
    }
};