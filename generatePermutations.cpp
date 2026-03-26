#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string chars;
    cin >> n;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        chars += c;
    }
    
    int total = 1;
    for (int i = 0; i < n; i++) {
        total *= n;  
    }
    
    for (int i = 0; i < total; i++) {
        int num = i;
        cout << num + 1 << ' ';
        for (int j = 0; j < n; j++) {
            cout << chars[num % n] << " ";
            num /= n;
        }
        cout << endl;
    }
    return 0;
}