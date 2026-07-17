#define pb push_back

class Solution {
public:

    string encode(vector<string>& strs) {
        string ct = ""; //cipher text
        for(auto s : strs){
            int n = s.size();

            string sz = "";
            while(n){
                if(n&1) sz += "1";
                else sz += "0";

                n >>= 1;
            }

            //Why 8 ? 
            // bcs 2^8 = 256
            // size of each individual string : 200 < 256
            while(sz.size() != 8){
                sz += "0";
            }

            reverse(sz.begin(), sz.end());

            // Append the size and then the string
            //size will let use know how long the iterator will have to move while decoding
            ct = ct + sz + s;
        }

        // cout<<ct<<endl;
        return ct;
    }

    vector<string> decode(string ct) {
        vector<string> pt; //plain text

        int i = 0;
        while(i < ct.size()){
            //1) Caluclate the size();
            int sz = 0;
            for(int j=i; j<i+8; j++){
                if(ct[j] == '0'){
                    sz <<= 1;
                }
                else{
                    sz <<= 1;
                    sz |= 1;
                }
            }
            i = i+8;

            //2) iterate till sz
            string s = "";
            for(int j=i; j<i+sz; j++){
                s += ct[j];
            }
            i = i + sz;

            //insert answer
            pt.pb(s);
        }

        return pt;
    }
};
