#include <iostream>
using namespace std;

const int MAXN=1000000;
int height[MAXN];
int n,m,k;
int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++) cin>>height[i];
    for(int i=0;i<m;i++){
        cin>>k;
        int left=0;
        int right=n-1;
        int c=0;
        while(left<=right){
            int mid=(left+right)/2;
            if (height[mid]==k){
                c=1;
                for(int p=mid-1;p>=0&&height[p]==k;p--) c++;
                for(int p=mid+1;p<n&&height[p]==k;p++) c++;
                break;
            }else if (height[mid]<k) left=mid+1;
            else right=mid-1;
        }
        cout<<c<<' ';
    }
    system("pause");
}