#include<fstream>
#include<vector>
using namespace std;
ifstream fin("guard.in");
ofstream fout("guard.out");

const int MAXN=1500;
const int INF=0x7fffffff;
vector<int> graph[MAXN+1];
int cost[MAXN+1];
int dp_min[MAXN+1][3];//dp_min[i][j] j=0表示不驻守可不观察根结点i j=1表示不驻守必须可观察根结点i j=2表示驻守必然可观赛根结点i
int n;

void dp(int x){
    int size=graph[x].size();
    int s2=0,s0=0;
    int min_deta=INF;
    for(int k=0;k<size;k++){
        int y=graph[x][k];
        dp(y);
        s2+=min(dp_min[y][0],dp_min[y][2]);//驻守时，子结点可驻守也可不驻守
        //这里注意，dp_min[y][1]总是大于等于dp_min[y][0]的
        s0+=min(dp_min[y][1],dp_min[y][2]);//不驻守不观察时，子结点必须可观察
        //不驻守但要可观察，则子结点必须至少有一个驻守，这里计算最少的增量
        int deta=dp_min[y][2]-min(dp_min[y][1],dp_min[y][2]);
        if (deta<min_deta) min_deta=deta;
    }
    dp_min[x][2]=cost[x]+s2;
    dp_min[x][0]=s0;
    dp_min[x][1]=s0+min_deta;
}
int main(){
    fin>>n;
    int root;
    bool first=true;
    for(int i=0;i<n;i++){
        int x,c,m;
        fin>>x>>c>>m;
        if (first){
            root=x;
            first=false;
        }
        cost[x]=c;
        for(int k=0;k<m;k++){
            int y;
            fin>>y;
            graph[x].push_back(y);
        }
    }
    dp(root);
    fout<<min(dp_min[root][1],dp_min[root][2]);
}