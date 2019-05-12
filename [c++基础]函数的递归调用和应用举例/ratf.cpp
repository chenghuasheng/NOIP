#include <iostream>
using namespace std;

int n,k;

int fzs(int x){
    if (x<k+2){
        return 1;
    }else if ((x-k)%2==0) {
        int a=(x-k)/2;
        int b=a+k;
        return fzs(a)+fzs(b);
    }
    else return 1;
}
int main(){
    cin>>n>>k;
    cout<<fzs(n);
    //system("pause");
}