#include <cstdio>
#include <queue>

using namespace std;
const int MAXN=1000000;
struct Snake{
    int id;
    int power;
    bool operator >(const Snake other)const{
        return (power>other.power)||(power==other.power&&id>other.id);
    }
    bool operator <(const Snake other)const{
        return (power<other.power)||(power==other.power&&id<other.id);
    }
    Snake eat(Snake other){
        Snake ret;
        ret.power=power-other.power;
        ret.id=id;
        return ret;
    }
};
deque<Snake> q1,q2;

int a[MAXN+1];
int maxa=-1;
int t,n,k;
Snake getMaxAndPop(){
    Snake ret={0,0};
    int t=0;
    if (q1.size()>0){
        ret=q1.back();
        t=1;
    }
    
    if (q2.size()>0&&q2.back()>ret){
        ret=q2.back();
        t=2;
    }
    if (t==1) q1.pop_back();
    else if (t==2) q2.pop_back();
    return ret;
}
Snake getMin(bool pop){
    Snake ret={n+1,maxa};
    int t=0;
    if (q1.size()>0) {
        ret=q1.front();
        t=1;
    }
    if (q2.size()>0&&q2.front()<ret){
        ret=q2.front();
        t=2;
    }
    if (pop){
        if (t==1) q1.pop_front();
        else if (t==2) q2.pop_front();
    }
    return ret;
}
void dowith(){
    q1.clear();q2.clear();
    for(int i=1;i<=n;i++) q1.push_back({i,a[i]});
    int len=n;
    Snake mins,maxs,news;
    while(len>1){
        mins=getMin(true);
        maxs=getMaxAndPop();
        news=maxs.eat(mins);
        if (news>getMin(false)){
           q2.push_front(news);
           len--; 
        }else break;
    }
    if (len>1) {
        int len1=len;
        int j=0;
        bool can=false;
        while(1){
            len1--;j++; 
            if (len1==1) can=true;
            else {
                if (news>getMin(false)) can=true;
            }
            //printf("%d %d %d\n",mins.power,maxs.power,j);
            if (can) break;
            mins=news;
            maxs=getMaxAndPop();
            news=maxs.eat(mins);
        }
        if (j%2!=0) len--;
    }
    printf("%d\n",len);
}

int main(){
    scanf("%d",&t);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=t;i++){
        if (i>1){
            scanf("%d",&k);
            for(int j=1;j<=k;j++){
                int x,y;
                scanf("%d %d",&x,&y);
                a[x]=y;
            }
        }
        for(int i=1;i<=n;i++) maxa=max(maxa,a[i]);
        dowith();
    }
}