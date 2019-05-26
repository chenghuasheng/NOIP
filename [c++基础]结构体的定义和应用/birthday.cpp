#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN=180;
struct Name{
    string content;
    int len;
    bool operator <(const Name other) const {
        if (len<other.len||len==other.len&&content<other.content) return true;
        else return false;
    }
};

struct Count{
    int num=0;
    Name stunames[MAXN];

    void add(string name){
        stunames[num].content=name;
        stunames[num].len=name.length();
        num++;
    }

    void output(){
        sort(stunames,stunames+num);
        for(int i=0;i<num;i++) cout<<stunames[i].content<<' ';
    }
};

Count counts[13][32];
string name;
int m,d;
int n;
int main(){
    cin>>n;
    for(int i=0;i<n;i++) {
        cin>>name>>m>>d;
        counts[m][d].add(name);
    }
    bool has=false;
    for(int i=1;i<=12;i++)
        for(int j=1;j<=31;j++){
            if (counts[i][j].num>=2) {
                has=true;
                cout<<i<<' '<<j<<' ';
                counts[i][j].output();
                cout<<endl;
            }
        }
    if (!has) cout<<"None";
    system("pause");
}