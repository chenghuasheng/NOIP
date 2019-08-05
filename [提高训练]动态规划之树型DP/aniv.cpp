//#1014. 「一本通 5.2 练习 3」周年纪念晚会 
#include<fstream>
#include<vector>
using namespace std;
ifstream fin("aniv.in");
ofstream fout("aniv.out");

const int MAXN=6000;
int happy[MAXN+1];
vector<int> graph[MAXN+1];
int dp_max[MAXN+1][2];
int n;
int parent[MAXN+1];

void dp(int x){
    int s=graph[x].size();
    int s0=0,s1=0;
    for(int k=0;k<s;k++){
        int y=graph[x][k];
        dp(y);
        s0+=max(dp_max[y][0],dp_max[y][1]);
        s1+=dp_max[y][0];
    }
    dp_max[x][0]=s0;
    dp_max[x][1]=s1+happy[x];
}
int main(){
    fin>>n;
    for(int i=1;i<=n;i++) fin>>happy[i];
    int l,k;
    fin>>l>>k;
    while(l>0&&k>0){
        graph[k].push_back(l);
        parent[l]=k;
        fin>>l>>k;
    }

    int cur=1;
    while(parent[cur]>0) cur=parent[cur];
    int root=cur;
    dp(root);
    fout<<max(dp_max[root][0],dp_max[root][1]);
}