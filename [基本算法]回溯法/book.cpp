#include <fstream>
using namespace std;
ifstream fin("book.in");
ofstream fout("book.out");

const int MAXN=20;
int n;
int favorit[MAXN+1][MAXN+1];
char c;
int ans;
bool flag[MAXN+1];

void dfs(int i){
    if (i>n) ans++;
    else {
        for(int j=1;j<=n;j++)
            if (!flag[j]&&favorit[i][j]){
                flag[j]=true;
                dfs(i+1);
                flag[j]=false;
            }
    }
}
int main(){
    fin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) {
            fin>>c;
            favorit[i][j]=c-'0';
        }
    ans=0;
    dfs(1);
    fout<<ans;
    system("pause");
}