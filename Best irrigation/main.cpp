#include <iostream>
#include <vector>
#include <math.h>
#include <map>
using namespace std;
int main()
{
    map<pair<int,int>,int> line;     //储存边，key是相连两田，value是费用
    map<int,int> net;     //定义已连通的网
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++)     //输入数据
    {
        int a,b,c;
        cin>>a>>b>>c;
        line.insert(pair<pair<int,int>,int>(pair<int,int>(a,b),c));
    }
    line.find(pair<1,2>);
    net[1]=0;     //已连通网里添加田1
    int ans=0;
    int x;
    map<pair<int,int>,int>::iterator it;
    while(net.size()<n){     //若已连通网里没有全部田
        int min=10001;     //定义最小值
        int field=1;     //定义要添加的田
        for(it = line.begin();it!=line.end();it++)
        {     //迭代搜寻与已添加的节点（田）连接的所具有最小的费用的点
            int a = it->first.first;
            int b = it->first.second;
            if((net.find(a)!=net.end() && net.find(b)==net.end())     //新点不应在net里的判断
                    || (net.find(a)==net.end() && net.find(b)!=net.end()))
            {
                int temp = it->second;
                if(temp<min)     //更新最小值
                {
                    min=temp;
                    if(net.find(a) == net.end())
                    {
                   	    field=a;
					}
                    if(net.find(b)==net.end())
                        field=b;
                }
                x = net.end()->first;
            }
        }
        cout<<field;
        net[field]=0;     //添加新点（田）
    //    cout<<"麦田"<<x<<"与麦田"<<field<<",";
        ans+=min;     //更新总费用
    }
    cout<<ans;
    return 0;
}
