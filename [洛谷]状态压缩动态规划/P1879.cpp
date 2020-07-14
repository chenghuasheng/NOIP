#include <iostream>
#include <cmath>

using namespace std;
const int MAXM=12;
const int MAXN=12;
const int MAXS=4095;//2^12-1
const int K=100000000;
int dp[MAXM+1][MAXS+1];
int flag[MAXM+1];
int m,n;
int lastS;
bool can(int s,int i){
    if (s&(s>>1)) return false;
    else if ((~flag[i])&s) return false;
    else return true;
}
bool conflict(int s1,int s2){
    if (s1&s2) return true;
    return false;
}

int main(){
    cin>>m>>n;
    lastS=pow(2,n)-1;
    for(int i=1;i<=m;i++){
        int mi=1;
        for(int j=1;j<=n;j++){
            int c;
            cin>>c;
            flag[i]+=mi*c;
            mi=mi*2;
        }
    }
    dp[0][0]=1;
    for(int i=1;i<=m;i++){
        for(int s1=0;s1<=lastS;s1++){
            if (!can(s1,i)) continue;
            for(int s2=0;s2<=lastS;s2++){
                if (!can(s2,i-1)) continue;
                if (!conflict(s1,s2)) dp[i][s1]=(dp[i][s1]+dp[i-1][s2]) % K;
            }
        }
    }
    int ans=0;
    for(int s=0;s<=lastS;s++) ans=(ans+dp[m][s])%K;
    cout<<ans;
}