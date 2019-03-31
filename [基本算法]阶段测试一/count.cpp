#include <fstream>
using namespace std;

ifstream fin("count.in");
ofstream fout("count.out");

const int MAXN=1000;
int s[MAXN+1];
int n;

int solution(int k){
    if (s[k]>0) return s[k];
    int c=1;
    int mid=k/2;
    for(int i=1;i<=mid;i++) c+=solution(i);
    s[k]=c;
    return c;
}

int main(){
    fin>>n;
    fout<<solution(n);
}

