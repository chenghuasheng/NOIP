#include<fstream>
using namespace std;
ifstream fin("digtriangle.in");
ofstream fout("digtriangle.out");

const int MAXN=100;
int n;
int number[MAXN][MAXN];
int dp[MAXN][MAXN];
int ans;

int main(){
    fin>>n;
    for(int i=0;i<n;i++)
        for(int j=0;j<=i;j++) fin>>number[i][j];
    dp[0][0]=number[0][0];
    for(int i=1;i<n;i++){
        dp[i][0]=dp[i-1][0]+number[i][0];
        for(int j=1;j<=i;j++)
            dp[i][j]=max(dp[i-1][j],dp[i-1][j-1])+number[i][j];
    }

    for(int j=0;j<n;j++)
        if (dp[n-1][j]>ans) ans=dp[n-1][j];
    fout<<ans;
}