//#1016. 「一本通 5.2 练习 5」骑士
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("knight.in");
ofstream fout("knight.out");

const int MAXN=1000000;
int fight[MAXN+1];
long long dp_max[MAXN+1][2][2];//dp_max[u][i][j] 表示结点u的子树的选出的最大战力，
//其中i=0表示子树中的结点不与根结点冲突，i=1表示子树中的结点可能与根结点冲突
//j=0表示当前结点u不被选中，j=1表示当前结点u被选中
bool visited[MAXN+1];
bool flag[MAXN+1];
vector<int> graph[MAXN+1];
int hate[MAXN+1];
int n;
long long ans;
int root;
void dp(int u){
    visited[u]=true;
    int count=graph[u].size();
    long long s00=0,s01=0,s10=0,s11=0;
    for(int k=0;k<count;k++){
        int v=graph[u][k];
        if (!visited[v]){
            dp(v);
            s00+=max(dp_max[v][0][0],dp_max[v][0][1]);
            s01+=dp_max[v][0][0];
            s10+=max(dp_max[v][1][0],dp_max[v][1][1]);
            s11+=dp_max[v][1][0];
        }
    }
    
    dp_max[u][0][0]=s00;
    dp_max[u][0][1]=fight[u]+s01;
    if (u==hate[root]) dp_max[u][0][1]=s01;
    dp_max[u][1][0]=s10;
    dp_max[u][1][1]=fight[u]+s11;
    
}
int get_root(int i){
    while(!flag[i]){
        flag[i]=true;
        i=hate[i];
    }
    return i;
}
int main(){
    fin>>n;
    for(int i=1;i<=n;i++){
        fin>>fight[i]>>hate[i];
        graph[hate[i]].push_back(i);
    }
    ans=0;
    for(int i=1;i<=n;i++){
        if (!visited[i]){
            int r=get_root(i);
            root=r;
            dp(r);
            ans+=max(max(dp_max[r][0][0],dp_max[r][0][1]),dp_max[r][1][0]);
        }
    }
    fout<<ans<<endl;
}