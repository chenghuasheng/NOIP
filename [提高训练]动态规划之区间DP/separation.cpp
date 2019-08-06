//#1005. 「一本通 5.1 练习 2」分离与合体
#include <fstream>
#include <vector>

using namespace std;
ifstream fin("separation.in");
ofstream fout("separation.out");
const int MAXN=300;
int dp_max[MAXN+1][MAXN+1];
int dp_path[MAXN+1][MAXN+1];

int a[MAXN+1];
int n;
vector<int> tree[MAXN];

void search(int i,int j,int deep){
    if (i>=j) return;
    else {
        int k=dp_path[i][j];
        tree[deep].push_back(k);
        search(i,k,deep+1);
        search(k+1,j,deep+1);
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
    search(1,n,0);
    for(int i=0;i<n;i++){
        int s=tree[i].size();
        for(int j=0;j<s;j++) fout<<tree[i][j]<<' ';
    }
}