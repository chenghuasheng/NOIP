#include<fstream>
using namespace std;
ifstream fin("flower.in");
ofstream fout("flower.out");
const int MAXN=100;
int n,m;
int a[MAXN+1];
int dp[MAXN+1][MAXN+1];//dp[i][j] 表示前i种花摆j盆的方案数

int main(){
    fin>>n>>m;
    for(int i=1;i<=n;i++) fin>>a[i];

    for(int j=0;j<=m&&j<=a[1];j++) dp[1][j]=1;
    for(int i=2;i<=n;i++)
        for(int j=0;j<=m;j++)
            for(int k=0;k<=j&&k<=a[i];k++){
                dp[i][j]+=dp[i-1][j-k];
                dp[i][j]=dp[i][j] % 1000007;
            }
    
    fout<<dp[n][m];  
}
