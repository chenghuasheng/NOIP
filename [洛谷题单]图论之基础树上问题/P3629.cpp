//P3629 [APIO2010]巡逻
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
const int MAXN=100000;
int n,k;
struct Edge{
    int to,weight;
};
vector<Edge> G[MAXN+1];
int maxlen[MAXN+1];
int maxlen_to[MAXN+1];
int second_maxlen[MAXN+1];
int second_maxlen_to[MAXN+1];

void tree_dp(int u,int fa){
    for(int k=0;k<G[u].size();k++){
        int v=G[u][k].to;
        int w=G[u][k].weight;
        if (v!=fa) {
            tree_dp(v,u);
            int v_w=w+maxlen[v];
            if (v_w>maxlen[u]){
                second_maxlen[u]=maxlen[u];
                second_maxlen_to[u]=maxlen_to[u];
                maxlen[u]=v_w;
                maxlen_to[u]=v;
            }else if (v_w>second_maxlen[u]){
                second_maxlen[u]=v_w;
                second_maxlen_to[u]=v;
            }
        }
    }
}
void adjust(int u){
    for(int k=0;k<G[u].size();k++){
        int v=G[u][k].to;
        if (v==maxlen_to[u]){
                G[u][k].weight=-1;
                adjust(v);
                break;
        }
    }
}
int main(){
    cin>>n>>k;
    for(int i=1;i<n;i++){
        int a,b;
        cin>>a>>b;
        G[a].push_back({b,1});
        G[b].push_back({a,1});
    }
    tree_dp(1,0);//选定1为根结点后，求出以节点i为根结点的子树中最长路径和次长路径
    //第一次求树的最长路径（即直径）
    int d=0;
    int d_u;
    for(int u=1;u<=n;u++){
        if (maxlen[u]+second_maxlen[u]>d){
            d=maxlen[u]+second_maxlen[u];
            d_u=u;
        }
    }
    int ans=2*(n-1)-d+1;//将树的直径的两个末端点相连，可使用巡逻少（d-1)
    if (k==2) {//修建第二条
        //找到树的一条直径，将上面的每一条边的weight由1调整为-1；
        for(int k=0;k<G[d_u].size();k++){
            int v=G[d_u][k].to;
            if (v==maxlen_to[d_u]||v==second_maxlen_to[d_u]){
                G[d_u][k].weight=-1;
                adjust(v);
            }
        }
        //再一次求树的直径
        memset(maxlen,0,sizeof(maxlen));
        memset(second_maxlen,0,sizeof(second_maxlen));
        tree_dp(1,0);
        d=0;
        for(int u=1;u<=n;u++){
            if (maxlen[u]+second_maxlen[u]>d){
                d=maxlen[u]+second_maxlen[u];
            }
        }
        ans=ans-d+1;
    }
    cout<<ans;
    system("pause");
}