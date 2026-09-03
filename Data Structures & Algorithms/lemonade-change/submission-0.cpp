class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int n = bills.size();

        int b5 = 0, b10 = 0;
        for(auto b : bills){
            if(b == 5){
                b5++;
            }
            else if(b == 10){
                if(b5) b5--, b10++;
                else return false;
            }
            else{
                if(b10 >= 1 && b5 >= 1){
                    b10--;
                    b5--;
                }
                else if(b5 >= 3){
                    b5 -= 3;
                }
                else return false;
            }
        }

        return true;
    }
};