#include <fstream>
#include<iostream>
using namespace std;
ifstream fin("getnum.in");
ofstream fout("getnum.out");
const int MAXN=10;
int n;
int dp[MAXN*2][MAXN][MAXN];
int cell[MAXN][MAXN];

int main(){
    fin>>n;
    int a,b,c;
    
    fin>>a>>b>>c;
    while(a>0&&b>0){
        cell[a-1][b-1]=c;
        fin>>a>>b>>c;
    }

    for(int d=1;d<2*n-1;d++)
        for(int i1=0;i1<=min(d,n-1);i1++)
            for(int i2=0;i2<=min(d,n-1);i2++){
                int j1=d-i1;
                int j2=d-i2;
                if (i1==i2){
                    if (i1-1>=0)
                        dp[d][i1][i1]=dp[d-1][i1-1][i1]+cell[i1][j1];
                }else {
                    if (i1-1>=0&&i2-1>=0)
                        dp[d][i1][i2]=max(dp[d-1][i1-1][i2-1]+cell[i1][j1]+cell[i2][j2],dp[d][i1][i2]);
                    if (i2-1>=0)
                        dp[d][i1][i2]=max(dp[d-1][i1][i2-1]+cell[i1][j1]+cell[i2][j2],dp[d][i1][i2]);
                    if (i1-1>=0)
                        dp[d][i1][i2]=max(dp[d-1][i1-1][i2]+cell[i1][j1]+cell[i2][j2],dp[d][i1][i2]);
                    dp[d][i1][i2]=max(dp[d-1][i1][i2]+cell[i1][j1]+cell[i2][j2],dp[d][i1][i2]);
                }
            }
    fout<<dp[2*n-2][n-1][n-1];
    //system("pause");
}