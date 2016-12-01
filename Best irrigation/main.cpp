#include <iostream>
#include "Graph.h" 
using namespace std;
typedef struct {
	VertexType adjvex;
	VRType lowcost;
}nod;
int minimum(nod *closedge, int n){
	int min = INT_MAX;
	int x; 
	for(int i = 0; i < n ; i++)
	{
		if(closedge[i].lowcost < min && closedge[i].lowcost != 0)
		{
			min = closedge[i].lowcost;
			x = i;
		}	
	}
	return x; 
}
void MiniSpanTree_PRIM(MGraph G, VertexType u)
{
	int load[G.arcnum][2];		//辅助数组记录水渠路径 
	int loadnum = 0; 			//记录水渠数 
	int length = 0;  			//记录水渠长度 
	nod closedge[MAX_VERTEX_NUM];
	int k = LocateVex(G,u); 
	int i,j;
	for(j = 0; j < G.vexnum; j++)
		if(j != k)
		{
			closedge[j].adjvex = u;
			closedge[j].lowcost = G.arcs[k][j].adj;
		}
	closedge[k].lowcost = 0;
	for(i = 1; i < G.vexnum; i++)
	{
		k = minimum(closedge,G.vexnum);
		length += closedge[k].lowcost; 
		load[loadnum][0] = closedge[k].adjvex;
		load[loadnum][1] = G.vexs[k];
		loadnum++;
		closedge[k].lowcost = 0;
		for(j = 0; j < G.vexnum; j++)
			if(G.arcs[k][j].adj < closedge[j].lowcost)
			{
				closedge[j].adjvex = G.vexs[k];
				closedge[j].lowcost = G.arcs[k][j].adj;
			}
	}
	cout<<length<<"\t说明：建立一下"<<loadnum<<"条水渠：";
	for(i = 0; i < loadnum; i++)
		cout<<"麦田"<<load[i][0]<<"和麦田"<<load[i][1]<<" ";
}
int main()
{
	MGraph G; 
	CreateGraph(G); 
	MiniSpanTree_PRIM(G,1);
	return 0;
}
/* 
6 10 
1 2 6
1 3 1
1 4 5
2 3 5
3 4 5
2 5 3
3 5 6
3 6 4
4 6 2
5 6 6 
*/ 
