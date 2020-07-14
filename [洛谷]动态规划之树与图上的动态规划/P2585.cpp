#include <iostream>
#include <vector>
#include <climits>

using namespace std;
const int MAXN=500000;
string s;
vector<int> tree[MAXN+1];
int dp_max[MAXN+1][3],dp_min[MAXN+1][3];
int index;
int n;
void buildTree(int u){
    int childNum=s[u-1]-'0';
    for(int k=0;k<childNum;k++){
        index++;
        tree[u].push_back(index);
        buildTree(index);
    }
}
void dp(int u){
    int childNum=s[u-1]-'0';
    if (childNum==0) {
        dp_max[u][1]=1;
        dp_max[u][0]=dp_max[u][2]=0;
        dp_min[u][1]=1;
        dp_min[u][0]=dp_min[u][2]=0;
    }else if (childNum==1){
        int v=tree[u][0];
        dp(v);
        dp_max[u][1]=max(dp_max[v][0],dp_max[v][2])+1;
        dp_max[u][0]=max(dp_max[v][1],dp_max[v][2]);
        dp_max[u][2]=max(dp_max[v][0],dp_max[v][1]);
        dp_min[u][1]=min(dp_min[v][0],dp_min[v][2])+1;
        dp_min[u][0]=min(dp_min[v][1],dp_min[v][2]);
        dp_min[u][2]=min(dp_min[v][0],dp_min[v][1]);
    }else if (childNum==2){
        int v1=tree[u][0];
        int v2=tree[u][1];
        dp(v1);dp(v2);
        dp_max[u][1]=max(dp_max[v1][0]+dp_max[v2][2],dp_max[v1][2]+dp_max[v2][0])+1;
        dp_max[u][0]=max(dp_max[v1][1]+dp_max[v2][2],dp_max[v1][2]+dp_max[v2][1]);
        dp_max[u][2]=max(dp_max[v1][0]+dp_max[v2][1],dp_max[v1][1]+dp_max[v2][0]);
        dp_min[u][1]=min(dp_min[v1][0]+dp_min[v2][2],dp_min[v1][2]+dp_min[v2][0])+1;
        dp_min[u][0]=min(dp_min[v1][1]+dp_min[v2][2],dp_min[v1][2]+dp_min[v2][1]);
        dp_min[u][2]=min(dp_min[v1][0]+dp_min[v2][1],dp_min[v1][1]+dp_min[v2][0]);
    }
}
int main(){
    cin>>s;
    n=s.length();
    index=1;
    buildTree(1);
    // for(int u=1;u<=n;u++){
    //     cout<<u<<":";
    //     for(int k=0;k<tree[u].size();k++) {
    //         cout<<tree[u][k]<<" ";
    //     }
    //     cout<<endl;
    // }
    for(int u=1;u<=n;u++) for(int i=0;i<3;i++) dp_min[u][i]=INT_MAX;
    dp(1);
    cout<<max(dp_max[1][0],max(dp_max[1][1],dp_max[1][2]))<<" ";
    cout<<min(dp_min[1][0],min(dp_min[1][1],dp_min[1][2]));
}