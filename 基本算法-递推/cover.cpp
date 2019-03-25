#include <fstream>
using namespace std;
ifstream fin("cover.in");
ofstream fout("cover.out");

const int MAXN=1001;
int s[MAXN];
int n;

int main(){
    fin>>n;
    s[0]=1;
    s[1]=1;
    for(int i=2;i<=n;i++) s[i]=(s[i-1]+s[i-2]*2) % 12345;
    fout<<s[n];
}