#define ii int
#define vii vector<int>
#define vvii vector<vector<int>>
#define pii pair<int, int>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define pb push_back
#define MOD 1000000007
#define ll long long
#define vll vector<ll>
#define vvll vector<vll>
#define all(x) (x).begin(), (x).end()
#define INF 1e9
#define ff first
#define ss second

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int s, int e, int k) {
        vvpii adj(n);

        for(int i=0; i<flights.size(); i++){
            int u = flights[i][0], v = flights[i][1], w = flights[i][2];
            adj[u].pb({v, w});
        }

        vector<int> dist(n, INF);

        set<vector<int>> pq; // {stops, cost, node}
        pq.insert({0, 0, s}); // {stops, cost, node}
        dist[s] = 0;

        while(!pq.empty()) {
            auto v = *pq.begin();
            pq.erase(pq.begin());

            int stops = v[0];
            int d = v[1];
            int u = v[2];

            if(stops > k) continue; // If we have exceeded the number of stops

            for(auto [v, w] : adj[u]){
                if(d + w < dist[v]){
                    dist[v] = d + w;
                    pq.insert({stops+1, dist[v], v});
                }
            }
        }

        return dist[e] == INF ? -1 : dist[e];
    }
};