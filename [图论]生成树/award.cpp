//#1050. 「一本通 3.1 练习 5」最小生成树计数
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;
ifstream fin("award.in");
ofstream fout("award.out");

const int MAXN=100;
struct edge{
    int u,v,w;
    bool operator<(const edge other)const{
        return w<other.w;
    }
};
vector<edge> edges;
int w[MAXN+1][MAXN+1];
struct node{
    int head,next,last,length;
};
struct union_find_set{
    node ele[MAXN+1];
    void make_set(){
        for(int i=1;i<=MAXN;i++) ele[i]={i,0,i,1};
    }
    void union_set(int x,int y){
        int hx=find_set(x);
        int hy=find_set(y);
        if (hx!=hy){
            if (ele[hx].length<ele[hy].length) add_to(hx,hy);
            else add_to(hy,hx);
        }
    }
    int find_set(int x){
        return ele[x].head;
    }
    void add_to(int head_from,int head_to){
        ele[ele[head_to].last].next=head_from;
        ele[head_to].last=ele[head_from].last;
        ele[head_to].length+=ele[head_from].length;
        int cur=head_from;
        while(cur!=0){
            ele[cur].head=head_to;
            cur=ele[cur].next;
        }
    }
};
union_find_set ufs;
int n,m;
int main(){
    fin>>n>>m;
    for(int i=0;i<m;i++){
        int a,b,c;
        fin>>a>>b>>c;
        w[a][b]=c;
        w[b][a]=c;
        edges.push_back({a,b,c});
    }
    sort(edges.begin(),edges.begin()+edges.size());
    ufs.make_set();
    int ans=1;
    int c=0;
    for(int i=0;i<edges.size();i++){
        int ru=ufs.find_set(edges[i].u);
        int rv=ufs.find_set(edges[i].v);
        if (ru!=rv){
            int k=0;
            int nd1=ru;
            while(nd1!=0){
                int nd2=rv;
                while(nd2!=0){
                    if (w[nd1][nd2]==edges[i].w) k++;
                    nd2=ufs.ele[nd2].next;
                }
                nd1=ufs.ele[nd1].next;
            }
            ans=ans*k;
            ufs.union_set(ru,rv);
            c++;
        }
        if (c>=n-1) break;
    }
    fout<<ans;
}