//#1002. 「一本通 5.1 例 2」能量项链
#include <fstream>
using namespace std;
ifstream fin("energy.in");
ofstream fout("energy.out");

const int MAXN=1000;
int head[MAXN*2];
int dp_max[MAXN*2][MAXN+1];//dp_max[i][j]表示以第i颗珠子为起始的，长度为j的区间(即[i,i+j-1])里，所有珠子合并所能得到的最大能量
int n;

int main(){
    fin>>n;
    for(int i=0;i<n;i++) {
        fin>>head[i];
        head[i+n]=head[i];
    }
    int m=2*n-1;
    for(int j=2;j<=n;j++) //j为区间长度
        for(int i=0;i<m-j+1;i++)
            for(int k=1;k<j;k++){
                dp_max[i][j]=max(dp_max[i][j],dp_max[i][k]+dp_max[i+k][j-k]+head[i]*head[i+k]*head[i+j]);
            }
        
    int lastMax=0;
    for(int i=0;i<n;i++)
        if (dp_max[i][n]>lastMax) lastMax=dp_max[i][n];
    fout<<lastMax;
}