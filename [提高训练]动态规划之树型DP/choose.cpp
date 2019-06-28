#include <fstream>
#include <vector>
using namespace std;
ifstream fin("choose.in");
ofstream fout("choose.out");
const int MAXN=100;
vector<int> graph[MAXN+1];
int dp_max[MAXN+1][MAXN+1];
int score[MAXN+1];
int n,m;
void dp(int i){
    dp_max[i][1]=score[i];
    int s=graph[i].size();
    for(int k=0;k<s;k++){
        int j=graph[i][k];
        dp(j);
        for(int w=m+1;w>0;w--)
            for(int v=w-1;v>0;v--)
            dp_max[i][w]=max(dp_max[i][w],dp_max[i][w-v]+dp_max[j][v]);
    }
}
int main(){
    fin>>n>>m;
    for(int i=1;i<=n;i++){
        int a,b;
        fin>>a>>b;
        graph[a].push_back(i);
        score[i]=b;
    }
    dp(0);
    fout<<dp_max[0][m+1];    
}
