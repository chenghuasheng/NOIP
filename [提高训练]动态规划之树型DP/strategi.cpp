#include <fstream>
#include <vector>
using namespace std;
ifstream fin("strategi.in");
ofstream fout("strategi.out");

const int MAXN=1500;
vector<int> graph[MAXN+1];
int dp_min[MAXN+1][2];
int n;

void dp(int x){
    int s=graph[x].size();
    int s0=0,s1=0;
    for(int k=0;k<s;k++){
        int y=graph[x][k];
        dp(y);
        s0+=dp_min[y][1];
        s1+=min(dp_min[y][0],dp_min[y][1]);
    }
    dp_min[x][0]=s0;
    dp_min[x][1]=1+s1;
}
int main(){
    fin>>n;
    for(int i=0;i<n;i++){
        int x,b;
        fin>>x>>b;
        for(int j=0;j<b;j++){
            int y;
            fin>>y;
            graph[x].push_back(y);
        }
    }
    dp(0);
    int ans=min(dp_min[0][0],dp_min[0][1]);
    fout<<ans;
}