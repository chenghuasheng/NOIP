#include<fstream>
using namespace std;
ifstream fin("chorus.in");
ofstream fout("chorus.out");
const int MAXN=1000;
int n;
int high[MAXN];
int dp[2][MAXN]; //dp[0][i] 表示编号 0——i-1 的学生中，以第i个学生身高为末尾的最长递增子序列
                //dp[1][i] 表示编号 i-1——n-1 的学生中，以第i个学生身高为起点的最长递减子序列
int ans;

int main(){
    fin>>n;
    for(int i=0;i<n;i++) fin>>high[i];
    for(int i=0;i<n;i++) {
        dp[0][i]=1;
        dp[1][i]=1;
    }

    for(int i=1;i<n;i++)
        for(int k=0;k<i;k++) 
            if (high[k]<high[i]) dp[0][i]=max(dp[0][k]+1,dp[0][i]);
    for(int i=n-2;i>=0;i--)
        for(int k=n-1;k>i;k--)
            if (high[k]<high[i]) dp[1][i]=max(dp[1][k]+1,dp[1][i]);
    
    for(int i=0;i<n;i++){
        int s=dp[0][i]+dp[1][i]-1;
        if (s>ans) ans=s;
    }
    fout<<n-ans;
}
