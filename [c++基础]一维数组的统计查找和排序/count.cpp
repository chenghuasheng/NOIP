#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN=200000;
int num[MAXN];
int n;
int main(){
    //输入
    cin>>n;
    for(int i=0;i<n;i++) cin>>num[i];
    //从小到大排序
    sort(num,num+n);
    //统计个数并输出
    int prev=num[0];
    int k=1;
    for(int i=1;i<n;i++)
        if (num[i]!=prev){
            cout<<prev<<' '<<k<<endl;
            prev=num[i];
            k=1;
        }else k++;
    cout<<prev<<' '<<k<<endl;
}
