#include <iostream>
#include <stack> 
#include <fstream>
#include <string.h>
#include <iomanip>
using namespace std;
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20
typedef int VertexType;
typedef int VRType;
typedef int Status;
typedef struct ArcNode{
	int adjvex;
	struct ArcNode *nextarc;
	int info;		//存储弧长； 
	string action;
}ArcNode;
typedef struct VNode{
	VertexType data;
	ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;	//邻接表 
	int vexnum,arcnum;
}ALGraph;
int LocateVex(ALGraph G, VertexType v1)
{
	for(int i = 0; i < G.vexnum; i++)
	{
		if(G.vertices[i].data == v1)
			return i;
	}
}
Status CreateGraph(ALGraph &G,fstream &fp)
{
	int i,j,k,value;
	string name;
	VertexType v1,v2;
	ArcNode *s;
	fp>>G.vexnum>>G.arcnum;
	for(i = 0; i < G.vexnum; i++)
	{
		fp>>G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}
	for(k = 0; k < G.arcnum; k++)
	{
		fp>>v1>>v2>>value>>name;
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		s = new ArcNode;
		s->info = value;
		s->action = name;
		s->adjvex = j;
		s->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = s;
	}
 } 
/******************改造拓扑排序求关键路径**********************************/
void FindInDegree(ALGraph G,int *indegree)
{
	int i;
	ArcNode *p;
	for(i = 0; i < G.vexnum; i++)
		indegree[i] = 0;
	for(i = 0; i < G.vexnum; i++)
	{
		p = G.vertices[i].firstarc;
        while (p)
        {
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
	}
}
stack<int> T;	//T为拓扑序列顶点栈，s为0入度顶点栈 
int ve[MAX_VERTEX_NUM]; 	//全局变量，各顶点事件的最早发生时间 
Status TopologicalOrder(ALGraph &G, stack<int> &T)
{
	int indegree[G.vexnum];
	int i,k;
	ArcNode *p; 
	FindInDegree(G,indegree);
	memset(ve,0,G.vexnum*sizeof(int));
 	stack<int> s;
 	for(i = 0; i < G.vexnum; i++)
 		if(!indegree[i])
 			s.push(i);
 	int count = 0;
 	while(!s.empty())
 	{
 		i = s.top();
 		s.pop();
 		T.push(i); 
 		count++;
 		for(p = G.vertices[i].firstarc; p; p = p->nextarc)
 		{
 			k = p->adjvex;
			if(!(--indegree[k]))
				s.push(k);	
			if(ve[i]+(p->info) > ve[k])
				ve[k] = ve[i]+(p->info);
		 }		
	 }
	if(count < G.vexnum)
		return ERROR;
	else
		return OK;
}
Status CriticalPath(ALGraph G,fstream &fp)
{
	int i,j,k,dut,ee,el;
	string name;
	char tag;
	ArcNode *p;
	if(!TopologicalOrder(G,T))
		return ERROR;
	int vl[G.vexnum];		//最迟开始时间 
	for(i = 0; i < G.vexnum-1; i++)
		vl[i] = INT_MAX;
	vl[G.vexnum-1] = ve[G.vexnum-1];
	while(!T.empty())	//按拓扑逆排序求各顶点vl值 
	{
		for(j = T.top(),T.pop(),p = G.vertices[j].firstarc; p; p = p->nextarc) 
		{
			k = p->adjvex;
			dut = p->info;
			if(vl[k] - dut < vl[j])
				vl[j] = vl[k] - dut;
		}
	}
	cout<<"关键活动\t持续时间\t最早开始时间\t最迟开始时间"<<endl; 
	fp<<setw(16)<<left<<"关键活动"<<setw(16)<<left<<"持续时间"<<setw(16)<<left<<"最早开始时间"<<setw(16)<<left<<"最迟开始时间"<<endl; 
	for(j = 0; j < G.vexnum; j++)
	{
		for(p = G.vertices[j].firstarc; p; p = p->nextarc)
		{
			name = p->action;
			k = p->adjvex;
			dut = p->info;
			ee = ve[j];
			el = vl[k] - dut;
			tag = (ee == el)?'*':' ';
			cout.widen(10);
			if(tag == '*'){
				cout<<setw(16)<<left<<name<<setw(16)<<left<<dut<<setw(16)<<left<<ee<<setw(16)<<left<<el<<endl;
				fp<<setw(16)<<left<<name<<setw(16)<<left<<dut<<setw(16)<<left<<ee<<setw(16)<<left<<el<<endl;
			}
		}
	}
}
int main()
{
	ALGraph G;
	fstream fp,fp2;
	fp.open("Project.txt",ios::in);
	fp2.open("CriticalPath.txt",ios::out);
	CreateGraph(G,fp);
	CriticalPath(G,fp2);
	fp.close();
	fp2.close();
	return 0;
 } 
