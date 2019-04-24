#include <fstream>
using namespace std;

ifstream fin("triangle.in");
ofstream fout("triangle.out");

int n;

int main(){
    fin>>n;
    long ans=0;
    for(int c=1;c<=n/2;c++){
        for(int a=1;a<=c;a++){
            int b=n-c-a;
            if (b>c||b<a) continue;
            if (a+b>c) ans++;
        }
    }
    fout<<ans;
}