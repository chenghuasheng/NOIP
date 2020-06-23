#include <iostream>
#include <algorithm>

using namespace std;
const int MAXN = 100000;
int n;
int high[MAXN];
int l1, l2;
int d1[MAXN], d2[MAXN];

int main() {
    int i=0;
    long a;
    while(cin>>a){
        high[i]=a;
        i++;
    }
    n=i;
    l1 = 1;
    d1[0] = high[0];
    l2 = 1;
    d2[0] = high[0];

    for (int i = 1; i < n; i++) {
        if (high[i] <= d1[l1 - 1])
            d1[l1++] = high[i];
        else {
            int k = upper_bound(d1, d1 + l1, high[i], greater<int>()) - d1;
            d1[k] = high[i];
        }
        if (high[i] > d2[l2 - 1])
            d2[l2++] = high[i];
        else {
            int k = lower_bound(d2, d2 + l2, high[i]) - d2;
            d2[k] = high[i];
        }
    }

    //输出
    cout << l1 << endl << l2;
}