#include <fstream>
#include <algorithm>
using namespace std;
ifstream fin("book.in");
ofstream fout("book.out");
const int MAXM=500;
const int INF=0x7fffffff;
int m,k;
int page[MAXM+1];
int totalPage[MAXM+1][MAXM+1];
int dp[MAXM+1][MAXM+1];//dp[i][j] 表示前i本书籍分配给前j个人所花的最短抄写时间

int main(){
    fin>>m>>k;
    for(int i=1;i<=m;i++) fin>>page[i];

    for(int i=1;i<=m;i++)
        for(int j=i;j<=m;j++)
            totalPage[i][j]=totalPage[i][j-1]+page[j];
    
    for(int i=1;i<=m;i++)
        for(int j=1;j<=i;j++) dp[i][j]=INF;
        
    for(int i=1;i<=m;i++) dp[i][1]=totalPage[1][i];
    for(int i=2;i<=m;i++)
        for(int j=2;j<=i;j++)
            for(int p=j-1;p<i;p++) {
                dp[i][j]=min(max(dp[p][j-1],totalPage[p+1][i]),dp[i][j]);
        }
    fout<<dp[m][k];
}