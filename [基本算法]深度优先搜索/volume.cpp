#include <fstream>
using namespace std;
ifstream fin("volume.in");
ofstream fout("volume.out");

const int MAXN=20;
int v[MAXN];
int n,c;
bool vflag[1001];

void dfs(int i,int sumv){
    if (i>=n){
        vflag[sumv]=true;
    }else {
        dfs(i+1,sumv);
        dfs(i+1,sumv+v[i]);
    }
}
int main(){
    fin>>n;
    for(int i=0;i<n;i++){
        fin>>v[i];
    }
    dfs(0,0);
    c=0;
    for(int i=1;i<1001;i++) if (vflag[i]) c++;
    fout<<c;
}