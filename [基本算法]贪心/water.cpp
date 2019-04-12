#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;
ifstream fin("water.in");
ofstream fout("water.out");

struct person{
    int id;
    int time;

    bool operator<(const person other) const{
        return time<other.time;
    }
};

const int MAXN=10000;
person p[MAXN];
int n;
int main(){
    fin>>n;
    for(int i=0;i<n;i++) {
        p[i].id=i+1;
        fin>>p[i].time;
    }
    sort(p,p+n);
    float totalwait=0;
    float wait=0;
    for(int i=0;i<n;i++){
        fout<<p[i].id<<' ';
        totalwait+=wait;
        wait+=p[i].time;
    }
    fout<<endl;
    float avgwait=totalwait/n;
    fout<<fixed<<setprecision(2)<<avgwait;
}