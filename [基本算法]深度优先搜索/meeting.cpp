#include <fstream>
using  namespace std;
ifstream fin("meeting.in");
ofstream fout("meeting.out");

const int MAXN=16;
int g_bls[MAXN+1][MAXN+1];
int g_als[MAXN+1][MAXN+1];

bool times[150010];

int n,m;
int min_time=150010;

void dfs_bls(int dep,int i,int time){
    if (i==n){
        times[time]=true;
    }else if (dep>n-1) return;
    else {
        for(int j=1;j<=n;j++){
            if (g_bls[i][j]>0) dfs_bls(dep+1,j,time+g_bls[i][j]);
        }
    }
}

void dfs_als(int dep,int i,int time){
    if (i==n){
        if (times[time]&&time<min_time){
            min_time=time;
        }
    }else if (dep>n-1) return;
    else {
        for(int j=1;j<=n;j++){
            if (g_als[i][j]>0) dfs_als(dep+1,j,time+g_als[i][j]);
        }
    }
}
int main(){
    fin>>n>>m;
    for(int i=0;i<m;i++){
        int a,b,c,d;
        fin>>a>>b>>c>>d;
        g_bls[a][b]=c;
        g_als[a][b]=d;
    }
    dfs_bls(1,1,0);
    dfs_als(1,1,0);
    if (min_time==150010) fout<<"IMPOSSIBLE";
    else fout<<min_time;
}
