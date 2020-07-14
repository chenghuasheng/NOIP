#include <iostream>
#include <cmath>

using namespace std;
const int MAXN=9;
const int MAXK=MAXN*MAXN;
const int MAXS=511;//2^9-1
long long dp[MAXN+1][MAXK+1][MAXS+1];
int n,k;
bool can(int s){
    if (s&(s>>1)) return false;
    return true;
}
bool conflict(int s1,int s2){
    if (s1&s2) return true;
    else if ((s1>>1)&s2) return true;
    else if ((s1<<1)&s2) return true;
    else return false;
}
int num[MAXS+1];

int lastS;
int main(){
    cin>>n>>k;
    lastS=pow(2,n)-1;
    for(int s=0;s<=lastS;s++){
        int st=s;
        while(st>0){
            num[s]+=st&1;
            st=st>>1;
        }
    }
    
    dp[0][0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=k;j++){
            if (j>n*i) break;
            for(int s1=0;s1<=lastS;s1++){
                if (!can(s1)) continue;
                for(int s2=0;s2<=lastS;s2++){
                    if (!can(s2)) continue;
                    if (!conflict(s1,s2)&&(j-num[s1]>=0)){
                        dp[i][j][s1]+=dp[i-1][j-num[s1]][s2];
                    }
                }
            }
        }
    }
    long long ans=0;
    for(int s=0;s<=lastS;s++) ans+=dp[n][k][s];
    cout<<ans;
}