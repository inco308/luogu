#include<bits/stdc++.h>
using namespace std;
int main(){
    string s1, s2;
    cin >> s1 >> s2;
    int ans = 0, first = -1, last = -1;
    int len = s1.length();
    
    for(int i = 0; i < len; i++){
        if(s1[i] == '#' || s2[i] == '#'){
            if(first == -1) first = i;
            last = i;
        }
    }
    
    if(first == -1){
        cout << 0;
        return 0;
    } 
    
    int status = 0;
    if(s1[first] == '#' && s2[first] == '#') status = 3;
    else if(s1[first] == '#') status = 1;
    else status = 2;
    
    for(int i = first + 1; i <= last; i++){
        int cur = 0;
        if(s1[i] == '#') cur |= 1;
        if(s2[i] == '#') cur |= 2;
        if(cur == 0){
            ans++;
        } else if(cur == 3){
            status = 3;
        } else{
            if((cur == 1 && status == 2) || (cur == 2 && status == 1)){
                ans++;
                status = 3;
            } else{
                status = cur;
            }
        }
    }
    
    cout << ans;
    return 0;
}
