#include <fstream>
#include <vector>

using namespace std;

ifstream fin("apple.in");
ofstream fout("apple.out");
const int MAXN=100;
struct node
{
    int next;
    int applenum;
};

vector<node> graph[MAXN+1];
int parent[MAXN+1];
int dp_max[MAXN+1][MAXN+1];
int n,q;
void dp(int x){
    int s=graph[x].size();
    for(int k=0;k<s;k++){
        node n=graph[x][k];
        int y=n.next;
        if (parent[x]!=y){
            parent[y]=x;
            dp(y);
            for(int w=q;w>0;w--)
                for(int v=w-1;v>=0;v--)
                    dp_max[x][w]=max(dp_max[x][w],dp_max[x][w-v-1]+dp_max[y][v]+n.applenum);
        }
    }
}

int main(){
    fin>>n>>q;
    for(int i=1;i<=n-1;i++){
        int a,b,c;
        fin>>a>>b>>c;
        node n1={b,c};
        graph[a].push_back(n1);
        node n2={a,c};
        graph[b].push_back(n2);
    }
    parent[1]=0;
    dp(1);
    //for(int i=0;i<=q;i++) cout<<dp_max[1][i]<<' ';
    fout<<dp_max[1][q];
}