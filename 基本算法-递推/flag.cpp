#include <fstream>
using namespace std;
ifstream fin("flag.in");
ofstream fout("flag.out");
const int MAXN=46;
int s[MAXN];
int n;
int main(){
    fin>>n;
    s[1]=2;
    s[2]=2;
    for(int i=3;i<=n;i++) s[i]=s[i-1]+s[i-2];
    fout<<s[n];
}