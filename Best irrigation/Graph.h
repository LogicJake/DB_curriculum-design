//无向带权网的基本操作
#include <iostream>
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
typedef struct AreCell
{
	VRType adj;
}AreCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
{
	VertexType vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	int vexnum,arcnum;
}MGraph;
int LocateVex(MGraph G, VertexType v1)
{
	for(int i = 0; i < G.vexnum; i++)
	{
		if(G.vexs[i] == v1)
			return i;
	}
}
Status CreateGraph(MGraph &G)
{
	int i,j,k;
	VertexType v1,v2;
	VRType value;
	cin>>G.vexnum>>G.arcnum;
	for(i = 0; i < G.vexnum; i++)
		G.vexs[i] = i+1;
	for(i = 0; i < G.vexnum; i++)
	{
		for(j = 0; j < G.vexnum; j++)
			G.arcs[i][j].adj = INFINITY;
	}
	for(k = 0; k < G.arcnum; k++)
	{
		cin>>v1>>v2>>value;
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		G.arcs[i][j].adj = value;
		G.arcs[j][i].adj = G.arcs[i][j].adj;
	}
	return OK;
}
