// #include<bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// const ll MOD = 1e9 + 7;

// ll q_pow(ll a, ll n){
//     ll ans = 1;
//     while(n){
//         if(n & 1) ans *= a;
//         a *= a;
//         n >>= 1;
//     }
//     return ans;
// }

// int main(){
//     int N;
//     if(!(cin >> N)) return 0;
//     vector<ll> A(N);
//     for(int i = 0; i < N; i++) cin >> A[i];

//     // 如果 N 过大，暴力法会超时/内存溢出，此处仅针对 N 较小的情况
//     ll perms = q_pow(3, N - 1);
//     string ops = "+-^";
//     ll total_sum = 0;

//     for(int i = 0; i < perms; i++){
//         // 1. 生成当前方案的操作符
//         vector<char> current_ops(N - 1);
//         int num = i;
//         for(int j = 0; j < N - 1; j++){
//             current_ops[j] = ops[num % 3];
//             num /= 3;
//         }

//         // 2. 优先级处理：先算所有的 XOR (^)
//         // 把数字和 + - 存进两个临时列表
//         vector<ll> nums_after_xor;
//         vector<char> ops_after_xor;
        
//         ll current_val = A[0];
//         for(int j = 0; j < N - 1; j++){
//             if(current_ops[j] == '^'){
//                 current_val ^= A[j+1]; // 遇到异或直接算
//             } else {
//                 nums_after_xor.push_back(current_val); // 遇到加减，把之前的算好的结果存了
//                 ops_after_xor.push_back(current_ops[j]);
//                 current_val = A[j+1]; // 开启下一个待运算段
//             }
//         }
//         nums_after_xor.push_back(current_val);

//         // 3. 处理剩下的加减
//         ll res = nums_after_xor[0];
//         for(int j = 0; j < ops_after_xor.size(); j++){
//             if(ops_after_xor[j] == '+') res += nums_after_xor[j+1];
//             else res -= nums_after_xor[j+1];
//         }
        
//         // 4. 累加总和（取模处理负数）
//         total_sum = (total_sum + res) % MOD;
//     }

//     // 纠正负数取模
//     cout << (total_sum + MOD) % MOD << endl;
//     return 0;
// }

#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

ll q_pow(ll a, ll n) {
    ll ans = 1;
    a %= MOD;
    while (n) {
        if (n & 1) ans = (ans * a) % MOD;
        a = (a * a) % MOD;
        n >>= 1;
    }
    return ans;
}

int main() {
    int N;
    cin >> N;
    vector<ll> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    ll total_sum = 0;
    ll current_xor_sum = 0;

    for (int k = 1; k <= N; k++) {
        // 计算前 k 个数的异或和: A[0] ^ A[1] ^ ... ^ A[k-1]
        current_xor_sum ^= A[k - 1];

        ll count;
        if (k < N) {
            // 前 k-1 个位置固定为 ^，第 k 个位置选 + 或 - (2种)，其余自由
            count = 2 * q_pow(3, N - 1 - k) % MOD;
        } else {
            // k == N，所有位置都固定为 ^
            count = 1;
        }

        // 贡献累加
        ll contribution = (current_xor_sum % MOD * count) % MOD;
        total_sum = (total_sum + contribution) % MOD;
    }

    cout << (total_sum + MOD) % MOD << endl;
    return 0;
}