#include <fstream>
#include <iomanip>
using namespace std;
ifstream fin("car.in");
ofstream fout("car.out");

const float e=0.001;
float s,a,b;


int main(){
    fin>>s>>a>>b;
    float left=0;
    float right=s/b;
    while(left<right){
        float  mid=(left+right)/2;
        float t1=mid+(s-mid*b)/a;
        float t2=s/b+2*mid*(b-a)/(b+a);
        if (t2-t1>e) right=mid;
        else if (t1-t2>e) left=mid;
        else {
            fout<<fixed<<setprecision(2)<<mid;
            break;
        }
    }
}