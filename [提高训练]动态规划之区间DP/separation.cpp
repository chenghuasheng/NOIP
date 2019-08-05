//#1005. 「一本通 5.1 练习 2」分离与合体
#include <fstream>
#include <iostream>

using namespace std;
ifstream fin("separation.in");
ofstream fout("separation.out");
const int MAXN=300;
int dp_max[MAXN+1][MAXN+1];
int dp_path[MAXN+1][MAXN+1];

int a[MAXN+1];
int n;
void print(int i,int j){
    if (i>=j) return;
    else {
        int k=dp_path[i][j];
        fout<<k<<' ';
        cout<<i<<'-'<<j<<':'<<k<<endl;
        print(i,k);
        print(k+1,j);
    }
}
int main(){
    fin>>n;
    for(int i=1;i<=n;i++) fin>>a[i];
    
    for(int len=2;len<=n;len++){
        for(int i=1;i<=n-len+1;i++){
            int j=i+len-1;
            for(int k=i;k<j;k++){
                int t=dp_max[i][k]+dp_max[k+1][j]+(a[i]+a[j])*a[k];
                if (t>dp_max[i][j]){
                    dp_max[i][j]=t;
                    dp_path[i][j]=k;
                }
            }
        }
    }
    fout<<dp_max[1][n]<<endl;
    print(1,n);
}