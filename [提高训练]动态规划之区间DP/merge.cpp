//#1001. 「一本通 5.1 例 1」石子合并 
#include<fstream>
using namespace std;
ifstream fin("merge.in");
ofstream fout("merge.out");
const int MAXN=200;
int stones[MAXN*2];
int totalStones[MAXN*2][MAXN];
int dp_min[MAXN*2][MAXN+1];//dp_min[i][j]表示以第i颗石子为起始，长度为j的区间（即[i,i+j-1])里的石子合并成一堆所能得到的最小得分
int dp_max[MAXN*2][MAXN+1];//同上类推
int n;
int main(){
    fin>>n;
    for(int i=0;i<n;i++) {
        fin>>stones[i];
        stones[i+n]=stones[i];
    }
    int m=n*2-1;
    for(int i=0;i<m;i++) totalStones[i][1]=stones[i];
    for(int i=0;i<m;i++) 
        for(int j=2;j<=n;j++) 
            totalStones[i][j]=totalStones[i][j-1]+stones[i+j-1];
    
    for(int j=2;j<=n;j++)
        for(int i=0;i<m-j+1;i++){
            dp_min[i][j]=dp_min[i][1]+dp_min[i+1][j-1]+totalStones[i][j];
            dp_max[i][j]=dp_max[i][1]+dp_max[i+1][j-1]+totalStones[i][j];
            for(int k=2;k<j;k++){
                dp_min[i][j]=min(dp_min[i][j],dp_min[i][k]+dp_min[i+k][j-k]+totalStones[i][j]);
                dp_max[i][j]=max(dp_max[i][j],dp_max[i][k]+dp_max[i+k][j-k]+totalStones[i][j]);
            }
        }
    
    int lastMin;
    int lastMax;
    lastMin=dp_min[0][n];
    lastMax=dp_max[0][n];
    for(int i=1;i<n;i++) {
        if (dp_min[i][n]<lastMin) lastMin=dp_min[i][n];
        if (dp_max[i][n]>lastMax) lastMax=dp_max[i][n];
    }
    fout<<lastMin<<endl<<lastMax; 
}