#include<fstream>
#include<algorithm>
using namespace std;

ifstream fin("kaj.in");
ofstream fout("kaj.out");

const int MAXN=30000;
int w,n;
int t[MAXN];
int ship[MAXN];

int main(){
    fin>>w>>n;
    for(int i=0;i<n;i++) fin>>t[i];
    sort(t,t+n,greater<int>());
    int cnt=1;
    ship[0]=w;
    for(int i=0;i<n;i++){
        bool can=false;
        for(int k=0;k<cnt;k++)
            if (ship[k]>=t[i]){
                if (ship[k]!=w) ship[k]=0;
                else ship[k]-=t[i];
                can=true;
                break;
            }
        if (!can){
            cnt++;
            ship[cnt-1]=w-t[i];
        }
    }
    fout<<cnt;
}
