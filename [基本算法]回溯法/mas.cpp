#include <fstream>
using namespace std;
ifstream fin("mas.in");
ofstream fout("mas.out");

int u;
bool used[10];
int ans[10];
int sum[10][2];
int pailei[10][10];

void dfs(int i){
   if (i>=u){
       bool can=true;
       for(int j=0;j<u;j++){
            int s1=0,s2=0;
            for(int k=0;k<u;k++){
                if (pailei[j][k]==ans[k]) s1+=ans[k];
                else {
                    if (used[pailei[j][k]]) s2+=pailei[j][k];
                }
            }
            if (s1!=sum[j][0]||s2!=sum[j][1]) {
                can=false;
                break;
            }
       }
       if (can) {
           for(int k=0;k<u;k++) fout<<ans[k]<<' ';
           exit(0);
       }
   }else {
       for(int j=1;j<=9;j++)
           if (!used[j]){
               ans[i]=j;
               used[j]=true;
               dfs(i+1);
               used[j]=false;
           }
   }
}
int main(){
    fin>>u;
    for(int i=0;i<u;i++){
        fin>>sum[i][0]>>sum[i][1];
        for(int j=0;j<u;j++) fin>>pailei[i][j];
    }
    dfs(0);
    system("pause");
}