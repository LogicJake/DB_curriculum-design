#include <iostream>
#include <vector>
#include <math.h>
#include <map>
using namespace std;
int main()
{
    map<pair<int,int>,int> line;     //����ߣ�key���������value�Ƿ���
    map<int,int> net;     //��������ͨ����
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++)     //��������
    {
        int a,b,c;
        cin>>a>>b>>c;
        line.insert(pair<pair<int,int>,int>(pair<int,int>(a,b),c));
    }
    line.find(pair<1,2>);
    net[1]=0;     //����ͨ���������1
    int ans=0;
    int x;
    map<pair<int,int>,int>::iterator it;
    while(net.size()<n){     //������ͨ����û��ȫ����
        int min=10001;     //������Сֵ
        int field=1;     //����Ҫ��ӵ���
        for(it = line.begin();it!=line.end();it++)
        {     //������Ѱ������ӵĽڵ㣨����ӵ���������С�ķ��õĵ�
            int a = it->first.first;
            int b = it->first.second;
            if((net.find(a)!=net.end() && net.find(b)==net.end())     //�µ㲻Ӧ��net����ж�
                    || (net.find(a)==net.end() && net.find(b)!=net.end()))
            {
                int temp = it->second;
                if(temp<min)     //������Сֵ
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
        net[field]=0;     //����µ㣨�
    //    cout<<"����"<<x<<"������"<<field<<",";
        ans+=min;     //�����ܷ���
    }
    cout<<ans;
    return 0;
}
