//#1012. 「一本通 5.2 练习 1」加分二叉树 
#include <fstream>
using namespace std;
ifstream fin("TREE.in");
ofstream fout("TREE.out");

const int MAXN=30;
long dp_max[MAXN+1][MAXN+1];
int dp_path[MAXN+1][MAXN+1];

int a[MAXN+1];
int n;

long dp(int i,int j){
    if (dp_max[i][j]>0) return dp_max[i][j];
    if (i>j) return 1;
    if (i==j) return a[i];
    for(int r=i;r<=j;r++){
        long t=dp(i,r-1)*dp(r+1,j)+a[r];
        if (t>dp_max[i][j]){
            dp_max[i][j]=t;
            dp_path[i][j]=r;
        }
    }
    return dp_max[i][j];
}
void root_first_visit(int i,int j){
    if (i>j) return;
    if (i==j) fout<<i<<' ';
    else {
        int r=dp_path[i][j];
        fout<<r<<' ';
        root_first_visit(i,r-1);
        root_first_visit(r+1,j);
    }
}
int main(){
    fin>>n;
    for(int i=1;i<=n;i++) fin>>a[i];
    fout<<dp(1,n)<<endl;
    root_first_visit(1,n);
}