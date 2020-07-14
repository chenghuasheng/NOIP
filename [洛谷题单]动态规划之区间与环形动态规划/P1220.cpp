#include <iostream>
#include <cmath>
using namespace std;
const int MAXN=50;
int n,c;
int w[MAXN+1],p[MAXN+1];
int sumw[MAXN+1];
int dp[MAXN+1][MAXN+1][2];//dp[i][j]表示关掉区间[i,j]里的灯时，所有的灯耗费的电量

int main(){
    cin>>n>>c;
    for(int i=1;i<=n;i++) {
        cin>>p[i]>>w[i];
        sumw[i]=sumw[i-1]+w[i];
    }
    for(int i=1;i<=n;i++){
        int t=abs(p[i]-p[c]);
        dp[i][i][0]=t*sumw[n];
        dp[i][i][1]=t*sumw[n];
    }
    
    for(int len=2;len<=n;len++){
        for(int i=1;i<=n-len+1;i++){
            int j=i+len-1;
            int v1=dp[i+1][j][0]+(p[i+1]-p[i])*(sumw[i]+sumw[n]-sumw[j]);
            int v2=dp[i+1][j][1]+(p[j]-p[i])*(sumw[i]+sumw[n]-sumw[j]);
            dp[i][j][0]=min(v1,v2);
            v1=dp[i][j-1][0]+(p[j]-p[i])*(sumw[i-1]+sumw[n]-sumw[j-1]);
            v2=dp[i][j-1][1]+(p[j]-p[j-1])*(sumw[i-1]+sumw[n]-sumw[j-1]);
            dp[i][j][1]=min(v1,v2);
        }
    }
    cout<<min(dp[1][n][0],dp[1][n][1]);
}