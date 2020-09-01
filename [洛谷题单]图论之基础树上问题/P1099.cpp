#include <iostream>
#include <vector>
#include <climits>

using namespace std;
const int MAXN=300;
const int INF=0x7ffffff;
int n,s;
struct Edge
{
    int v;
    int w;
};
vector<Edge> tree[MAXN+1];
int dis[MAXN+1][MAXN+1];

void floyd(){
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                if (k!=i&&i!=j&&j!=k&&dis[i][k]+dis[k][j]<dis[i][j]) dis[i][j]=dis[i][k]+dis[k][j];
            }
}

int dp[MAXN+1][2];
int dp_path[MAXN+1][2];
int parent[MAXN+1];

void tree_dp(int u){
    for(int k=0;k<tree[u].size();k++){
        int v=tree[u][k].v;
        int w=tree[u][k].w;
        if (v!=parent[u]){
            parent[v]=u;
            tree_dp(v);
            int t=dp[v][0]+w;
            if (t>dp[u][0]){
                dp[u][1]=dp[u][0];
                dp_path[u][1]=dp_path[u][0];
                dp[u][0]=t;
                dp_path[u][0]=v;
            }else if (t>dp[u][1]){
                dp[u][1]=t;
                dp_path[u][1]=v;
            }
        }
    }
}
int zhiji[MAXN];
int min_dis_zhiji[MAXN+1];

int main(){
    cin>>n>>s;
    for(int i=1;i<=n;i++) 
        for(int j=1;j<=n;j++) {
            if (i==j) dis[i][j]=0;
            else  dis[i][j]=INF;
        }
           
    
    for(int i=1;i<=n-1;i++){
        int u,v,w;
        cin>>u>>v>>w;
        tree[u].push_back({v,w});
        tree[v].push_back({u,w});
        dis[u][v]=dis[v][u]=w;
    }
    tree_dp(1);
    int max_len=0;
    int max_len_node;

    for(int u=1;u<=n;u++){
        if (dp[u][0]+dp[u][1]>max_len){
            max_len=dp[u][0]+dp[u][1];
            max_len_node=u;
        }
    }
    int k=0;
    int u=dp_path[max_len_node][0];
    while(u>0){
        zhiji[k]=u;
        k++;
        u=dp_path[u][0];
    }
    for(int i=0;i<k/2;i++){
        swap(zhiji[i],zhiji[k-i-1]);
    }
    zhiji[k]=max_len_node;
    k++;
    u=dp_path[max_len_node][1];
    while(u>0){
        zhiji[k]=u;
        k++;
        u=dp_path[u][0];
    }
    // for(int i=0;i<k;i++) cout<<zhiji[i]<<" ";
    // cout<<endl;
    floyd();
    
    int left,right;
    for(int i=1;i<k;i++){
        if (2*dis[zhiji[0]][zhiji[i]]==max_len){
            left=right=i;
            break;
        }else if (2*dis[zhiji[0]][zhiji[i]]>max_len){
            if (dis[zhiji[0]][zhiji[i-1]]>dis[zhiji[i]][zhiji[k-1]]){
                left=right=i-1;
            }else {
                left=right=i;
            }
            break;
        }
    }
    //cout<<left<<endl;

    for(int i=1;i<=n;i++) min_dis_zhiji[i]=INF;

    while(dis[zhiji[left]][zhiji[right]]<=s){
        for(int i=1;i<=n;i++){
            if (dis[i][zhiji[left]]<min_dis_zhiji[i]) min_dis_zhiji[i]=dis[i][zhiji[left]];
            if (dis[i][zhiji[right]]<min_dis_zhiji[i]) min_dis_zhiji[i]=dis[i][zhiji[right]];
        }
        if (dis[zhiji[0]][zhiji[left]]>dis[zhiji[right]][zhiji[k-1]]&&left-1>=0&&dis[zhiji[left-1]][zhiji[right]]<=s) left--;
        else if (right+1<k&&dis[zhiji[left]][zhiji[right+1]]<=s) right++;
        else break;
    }
    int ecc=0;
    for(int i=1;i<=n;i++) if (min_dis_zhiji[i]>ecc) ecc=min_dis_zhiji[i];
    cout<<ecc;
    system("pause");
}