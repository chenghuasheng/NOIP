#include <fstream>
#include <cstring>
using namespace std;

ifstream fin("apple.in");
ofstream fout("apple.out");
const int MAXN=100;
int lc[MAXN+1];
int rc[MAXN+1];
int lw[MAXN+1];
int rw[MAXN+1];
int apple[MAXN+1][MAXN+1];
int dp_max[MAXN+1][MAXN+1];

int n,q;

void build_tree(int i){
    for(int j=1;j<=n;j++){
        if (apple[i][j]>=0){
            if (lc[i]==0){
                lc[i]=j;
                lw[i]=apple[i][j];
            }else {
                rc[i]=j;
                rw[i]=apple[i][j];
            }
            apple[i][j]=-1;
            apple[j][i]=-1;
            build_tree(j);
        }
    }
}
void dp(int i){
    if (lc[i]>0) dp(lc[i]);
    if (rc[i]>0) dp(rc[i]);
    for(int j=1;j<=q;j++){
        dp_max[i][j]=dp_max[lc[i]][j-1]+lw[i];//无右子树
        dp_max[i][j]=max(dp_max[i][j],dp_max[rc[i]][j-1]+rw[i]);//无左子树
        if (j>=2){
            for(int k=0;k<=j-2;k++){
                dp_max[i][j]=max(dp_max[i][j],dp_max[lc[i]][k]+dp_max[rc[i]][j-k-2]+lw[i]+rw[i]);
            }
        }
    }
}
int main(){
    fin>>n>>q;
    memset(apple,-1,sizeof(apple));
    for(int i=1;i<=n-1;i++){
        int a,b,c;
        fin>>a>>b>>c;
        apple[a][b]=c;
        apple[b][a]=c;
    }
    build_tree(1);
    dp(1);
    fout<<dp_max[1][q];
}