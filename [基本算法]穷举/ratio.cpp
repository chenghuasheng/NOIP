#include<fstream>
using namespace std;

ifstream fin("ratio.in");
ofstream fout("ratio.out");

int A,B,L;
int A_,B_;

int main(){
    fin>>A>>B>>L;
    A_=2*L;B_=1;
    for(int b=1;b<=L;b++){
        for(int a=1;a<=L;a++){
            if (a*B>=b*A){
                if (a*B_<b*A_){
                    A_=a;
                    B_=b;
                }
                break;
            }
        }
    }
    fout<<A_<<' '<<B_;
}
