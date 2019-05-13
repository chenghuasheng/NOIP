#include <fstream>
using namespace std;
ifstream fin("decompose.in");
ofstream fout("decompose.out");

int s[21];
int n;
int count;

void dfs (int dep,int k,int r){
    for(int i=k;i<=r;i++){
        s[dep]=i;
        int r1=r-i;
        if (r1==0) {
            for(int j=0;j<=dep;j++){
                if (j>0) fout<<'+'<<s[j];
                else fout<<s[j];
            }
            fout<<endl;
            count++;
        }else dfs(dep+1,i,r1);
    }
}
int main(){
    fin>>n;
    dfs(0,1,n);
    fout<<"total="<<count;
}