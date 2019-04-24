#include <fstream>
using namespace std;

ifstream fin("cow.in");
ofstream fout("cow.out");
const int MAXN=100001;
char s[MAXN];
int c[MAXN],w[MAXN];

int n;
long long ans; 
int main(){
    fin>>n;
    fin>>s;
    if (s[0]=='C') c[0]=1;
    else c[0]=0;
    for(int i=1;i<n;i++){
        if (s[i]=='C') c[i]=c[i-1]+1;
        else c[i]=c[i-1];
    }

    if (s[n-1]=='W') w[n-1]=1;
    else w[n-1]=0;
    for(int i=n-2;i>=0;i--){
        if (s[i]=='W') w[i]=w[i+1]+1;
        else w[i]=w[i+1];
    }
    ans=0;
    for(int i=0;i<n;i++){
        if (s[i]=='O'){
            ans+=c[i]*w[i];
        }
    }
    fout<<ans;
}