class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();

        // Initialize with -1 so we don't read garbage values
        vector<vector<int>> dp(n + 1, vector<int>(2, -1));

        // prev = 1 -> last element taken (starting a new letter)
        // prev = 0 -> last element not taken (MUST combine s[i-1] and s[i])
        auto f = [&](int i, int prev, auto && f) -> int {
            // Base case: if we reach the end while holding a skipped character, it's invalid
            if(i == n) return prev == 1 ? 1 : 0;
            
            if(s[i] == '0' && prev == 1) return 0;

            if(dp[i][prev] != -1) return dp[i][prev];

            int ans = 0;

            if(prev == 1){
                // Take curr element as a single digit
                ans += f(i+1, 1, f);

                // Skip curr element, hold it to pair next time
                // (Only skip if there is actually a next element to pair with!)
                if (i + 1 < n) {
                    ans += f(i+1, 0, f);
                }
            }
            else{
                // We are forced to combine the skipped s[i-1] with current s[i]
                int twoDigit = (s[i-1] - '0') * 10 + (s[i] - '0');
                
                if(twoDigit >= 10 && twoDigit <= 26){
                    // Successfully paired! The current element is now taken.
                    ans += f(i+1, 1, f); 
                }
            }

            return dp[i][prev] = ans;
        };

        return f(0, 1, f);
    }
};