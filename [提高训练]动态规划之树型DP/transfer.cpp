//#1009. 「一本通 5.2 例 3」数字转换
#include<fstream>
using namespace std;
ifstream fin("transfer.in");
ofstream fout("transfer.out");

const int MAXN=50000;
int factorSum[MAXN+1];
int maxLen[MAXN+1],secondMaxLen[MAXN+1];//maxLen[i]表示以i为根的子树中，
                //i到叶子结点的最长路径,secondMaxLen[i]是i到叶子结点的次长路径

int n;

int main(){
    fin>>n;
    for(int i=1;i<=n;i++)
     for(int j=2;j<=n/i;j++)
        factorSum[i*j]+=i;
    for(int i=n;i>=1;i--){//大的数总是挂在小的数下，所以从大到小遍历计算
        if (factorSum[i]<i){
            int p=factorSum[i];
            if (maxLen[i]+1>maxLen[p]){
                secondMaxLen[p]=maxLen[p];
                maxLen[p]=maxLen[i]+1;
            }else if (maxLen[i]+1>secondMaxLen[p]){
                secondMaxLen[p]=maxLen[i]+1;
            }
        }
    }
    int ans=0;
    for(int i=n;i>=1;i--){
        if (maxLen[i]+secondMaxLen[i]>ans) ans=maxLen[i]+secondMaxLen[i];
    }
    fout<<ans;
}
