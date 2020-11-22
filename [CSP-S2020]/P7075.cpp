#include <iostream>
#include <cmath>
using namespace std;
const int BC=((4713-1)/4+1)+4713*365;
const int RURUI=1582/4+1582*365-31-30-27;
const int YEAR1600=RURUI+78+18*365+5;
const int YEAR2000=YEAR1600+400*365+97;
const int YEARS400=400*365+97;
const int total=BC+YEAR2000+1;
int ping[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int year[total],month[total],day[total];
int curR,curYear,curMonth,curDay;
int main(){
    curR=0;
    curYear=-4713;
    bool isRun;
    while(curR<BC+YEAR2000){
        if (curYear<0) isRun=(abs(curYear)-1)%4==0;
        else if (curR<BC+RURUI) isRun=curYear%4==0;
        else {
            isRun=(curYear%400==0)||(curYear%4==0&&curYear%100!=0);
        }
        curMonth=1;
        while(curMonth<=12){
            int monthDays=ping[curMonth];
            if (isRun&&curMonth==2) monthDays++;
            curDay=1;
            while(curDay<=monthDays){
                year[curR]=curYear;
                month[curR]=curMonth;
                day[curR]=curDay;
                if (curR==BC+RURUI-1) curDay+=11;
                else curDay++;
                curR++; 
            }
            curMonth++;
        }
        curYear++;
        if (curYear==0) curYear=1;
    }
    long long r;
    int q;
    cin>>q;
    for(int i=1;i<=q;i++){
        cin>>r;
        int yearinc=0;
        if (r>=BC+YEAR2000){
            r-=BC+YEAR1600;
            yearinc=(r/YEARS400)*400;
            r=r%YEARS400;
            r=BC+YEAR1600+r;
        }
        cout<<day[r]<<" "<<month[r]<<" "<<abs(year[r])+yearinc;
        if (year[r]<0) cout<<" BC";
        cout<<endl;
    }
}