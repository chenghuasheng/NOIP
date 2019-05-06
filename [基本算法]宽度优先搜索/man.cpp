#include<fstream>
#include<queue>
#include<vector>
#include<iostream>
using namespace std;

ifstream fin("man.in");
ofstream fout("man.out");

const int MAXN=20;
int n,m;
int walls[MAXN][MAXN];
char map[MAXN][MAXN];
int x1,y1,x2,y2,x3,y3;
struct State
{
    int id;
    int pid;
    int action;
    int times;
    int x1,y1;
    int x2,y2;
    int stoptime;
};
vector<State> states;
queue<int> qe;

string actionNames[4]={"up","left","right","down"};//每个执行动作的名称，其实就是方向的名称
int dir_off[4][2]={{-1,0},{0,-1},{0,1},{1,0}};//每个方向的偏移量
int dir_wall[4]={1,2,4,8};//每个方向的墙标志
int rev_dir[4]={3,2,1,0};//每个方向的反方向

bool visited[MAXN][MAXN][MAXN][MAXN][4];

void print(State s){
    int pid=s.pid;
    if (pid>0) print(states[pid]);
    fout<<actionNames[s.action]<<endl;
}
bool hasWall(int x,int y,int d){
    return (dir_wall[d]&walls[x][y])>0;
}

bool canWalk(int x,int y,int d,int newx,int newy){
    if (hasWall(x,y,d)||hasWall(newx,newy,rev_dir[d])) return false;
    else return true;
}

int main(){
    fin>>n>>m;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++) fin>>walls[i][j];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            fin>>map[i][j];
            if (map[i][j]=='S'){
                x1=i;y1=j;
                map[i][j]='.';
            }else if (map[i][j]=='M'){
                x2=i;y2=j;
                map[i][j]='.';
            }else if (map[i][j]=='E'){
                x3=i;y3=j;
                map[i][j]='.';
            }
        }
    if (x1==x3&&y1==y3){
        fout<<"total steps:"<<0;
        return 0;
    }

    int k=0;
    State start={0,-1,-1,0,x1,y1,x2,y2,0};
    states.push_back(start);
    k++;
    qe.push(0);
    visited[x1][y1][x2][y2][0]=true;

    while(!qe.empty()){
        int curId=qe.front();
        State cur=states[curId];
        for(int d=0;d<4;d++){
            int newx1=cur.x1+dir_off[d][0];
            int newy1=cur.y1+dir_off[d][1];
            if (newx1<0||newx1>=n||newy1<0||newy1>=m) continue;//越界
            if (canWalk(cur.x1,cur.y1,d,newx1,newy1)){//检查是否能走过去
                if (map[newx1][newy1]=='W') continue;//掉入陷阱
                //决断是否到达目标地点，到达了不用管是否被怪兽吃掉
                State next={k,cur.id,d,cur.times+1,newx1,newy1,0,0,0};
                bool succeed=(next.x1==x3&&next.y1==y3);
                if (succeed) {
                    print(next);
                    fout<<"total steps: "<<next.times;
                    return 0;
                }
                //怪兽走两步
                int stoptime,newx2,newy2;
                newx2=cur.x2;
                newy2=cur.y2;
                if (cur.stoptime==0){
                    stoptime=0;
                    int step=0;
                    int dds[2];//存放怪兽朝勇士走去可能要走的两个方向
                    //决定水平走方向
                    if (newy1<newy2) dds[0]=1;
                    else dds[0]=2;
                    //决定竖直走方向
                    if (newx1<newx2) dds[1]=0;
                    else dds[1]=3;
                    for(int i=0;i<2;i++){
                        int dd=dds[i];
                        while(step<2&&stoptime==0){
                            if (i==0&&newy2==newy1) break;//水平方向怪兽与勇士一致时，水平方向不再走
                            if (i==1&&newx2==newx1) break;//竖直方向怪兽与勇士一致时，竖直方向不再走
                            int xt=newx2+dir_off[dd][0];
                            int yt=newy2+dir_off[dd][1];
                            if (!canWalk(newx2,newy2,dd,xt,yt)) break;
                            newx2=xt;
                            newy2=yt;
                            step++;
                            if (map[newx2][newy2]=='W'){
                                stoptime=3;
                                break;
                            }
                        }
                    }
                }else {
                    stoptime=cur.stoptime-1;
                }
                //更新怪兽的新位置和停止时间
                next.x2=newx2;
                next.y2=newy2;
                next.stoptime=stoptime;
                //决断怪兽是否吃掉勇士
                bool eated=(next.x1==next.x2&&next.y1==next.y2);
                if (eated) continue;
                //判重，在状态不重复的情况下，将新状态保存下来，并将状态ID入队列
                if (!visited[next.x1][next.y1][next.x2][next.y2][next.stoptime]){
                    states.push_back(next);
                    k++;
                    qe.push(next.id);
                    visited[next.x1][next.y1][next.x2][next.y2][next.stoptime]=true;
                }
            }
        }
        qe.pop();
    }
    fout<<"impossible";
}