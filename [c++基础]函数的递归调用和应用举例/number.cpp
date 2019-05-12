#include <iostream>
using namespace std;

int n;
int yzh(int x){
    int ret=0;
    for(int i=2;i<=x/2;i++){
        if (x%i==0) ret+=i;
    }
    return ret;
}
int main(){
    cin>>n;
    for(int a=2;a<=n;a++){
        int b=yzh(a);
        if (b<=n&&yzh(b)==a) cout<<a<<' '<<b<<endl;
    }
    //system("pause");
}