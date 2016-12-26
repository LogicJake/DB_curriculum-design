//通过邻接矩阵实现 
#include <iostream>	
#include <string.h>
#include <fstream>
using namespace std;
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFINITY 1000000000		//最大值 
#define MAX_VERTEX_NUM 20
typedef string VertexType;
typedef int VRType;
typedef int Status;
typedef struct AreCell
{
	VRType adj;				//路径长度 
}AreCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
{
	VertexType vexs[MAX_VERTEX_NUM];		//顶点向量	
	AdjMatrix arcs;							//邻接矩阵 
	int vexnum,arcnum;						//景点个数和路径数 
}MGraph;
int NumUnZero(int *a, int n)
{
	int num = 0;
	for(int i = 1; i <= n; i++)
	{
		if(a[i] != 0)
			num++;
	}
	return num;
}
int LocateVex(MGraph G, VertexType v1)
{
	for(int i = 1; i <= G.vexnum; i++)
	{
		if(G.vexs[i] == v1)
			return i;
	}
}

Status CreateGraph(MGraph &G,fstream &fp)
{
	int i,j,k;
	VertexType v1,v2;
	VRType value;
	fp>>G.vexnum>>G.arcnum;
	for(i = 1; i <= G.vexnum; i++)
		fp>>G.vexs[i];
	for(i = 1; i <= G.vexnum; i++)
	{
		for(j = 1; j <= G.vexnum; j++)
		if(i == j)
			G.arcs[i][j].adj = 0;
		else
			G.arcs[i][j].adj = INFINITY;
	}
	for(k = 1; k <= G.arcnum; k++)
	{
		fp>>v1>>v2>>value;
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		G.arcs[i][j].adj = value;
		G.arcs[j][i].adj = G.arcs[i][j].adj;
	}
	return OK;
}
/*********************最短路径************************/
void ShortPath(MGraph G, string start, int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM], int *D)	//P为路径 D为长度 
{
	int i,v,w,min;
	int v0 = LocateVex(G,start);
	int final[MAX_VERTEX_NUM];
	for(v = 1; v <= G.vexnum; v++)
	{
		final[v] = FALSE;
		D[v] = G.arcs[v0][v].adj;
		for(w = 1; w <= G.vexnum; w++)
			P[v][w] = FALSE;	//空路径 
		if(D[v] < INFINITY){
			P[v][v0] = 1;
			P[v][v] = 2;
		} 
	}
	D[v0] = 0;
	final[v0] = TRUE;
	for(i = 1; i < G.vexnum; i++)
	{
		min = INFINITY;
		for(w = 1; w <= G.vexnum; w++)
		{
			if(!final[w])
				if(D[w] < min)
				{
					v = w;
					min = D[v];
				}
		}
		final[v] = TRUE;
		for(w = 1; w <= G.vexnum; w++)
		{
			if(!final[w]&&(min + G.arcs[v][w].adj < D[w])){
				D[w] = min + G.arcs[v][w].adj;
				for(int i = 1; i <= G.vexnum; i++)
					P[w][i] = P[v][i];	
				P[w][w] = NumUnZero(P[w],G.vexnum)+1;
			}
		}
	}
} 

void ShortestPathBetween(MGraph G, int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM],int D[MAX_VERTEX_NUM][MAX_VERTEX_NUM])
{
	int u,v,w,i,temp;
	for(v = 1; v <= G.vexnum; v++){
		for(w = 1; w <= G.vexnum; w++){
			D[v][w] = G.arcs[v][w].adj;
			for(u = 1; u <= G.vexnum; u++)
				P[v][w][u] = FALSE;
			if(D[v][w] < INFINITY){
				P[v][w][v] = TRUE;
				P[v][w][w] = TRUE;
			}
		}
	}
	for(u = 1; u <= G.vexnum; u++)
		for(v = 1; v <= G.vexnum; v++)
			for(w = 1; w <= G.vexnum; w++)
				if(D[v][u]+D[u][w] < D[v][w]){
					D[v][w] = D[v][u]+D[u][w];
					for(i = 1; i <= G.vexnum; i++)
						P[v][w][i] = P[v][u][i] || P[u][w][i];
				}
}
Display(int p[MAX_VERTEX_NUM][MAX_VERTEX_NUM],int *d,MGraph G,fstream &fp)
{
	cout<<"\t\t从南航出发到各景点的最短路径"<<endl<<endl<<"\t"; 
	fp<<"\t\t从南航出发到各景点的最短路径"<<endl<<endl<<"\t"; 
	for(int i = 2; i <= G.vexnum; i ++){
		int num = NumUnZero(p[i],G.vexnum);
		for(int j = 1; j < num; j++){
			for(int k = 1; k <= G.vexnum; k++)
			{
				if(p[i][k] == j){
					fp<<G.vexs[k]<<"-->";
					cout<<G.vexs[k]<<"-->";
				}
			}
		}
		for(int k = 1; k <= G.vexnum; k++)
		{
			if(p[i][k] == num){
				fp<<G.vexs[k];
				cout<<G.vexs[k];
			}
		}
		cout<<"          路径长度："<<d[i];
		fp<<"          路径长度："<<d[i];
		cout<<endl<<"\t";
		fp<<endl<<"\t";
 	} 
}
void Display2(int p[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM],int d[MAX_VERTEX_NUM][MAX_VERTEX_NUM],MGraph G,fstream &fp) 
{
	int u,v,w;
	for(u = 1; u <= G.vexnum; u++)
    {
        for(v = 1; v <= G.vexnum; v++){
        	if(v <= u)
        		continue;
        	cout<<G.vexs[u]<<"-->";
        	fp<<G.vexs[u]<<"-->";
       		for(w = 1; w <= G.vexnum; w++)
       		{
       			if(p[u][v][w] == 1 && w != u && w != v)
				{
					cout<<G.vexs[w]<<"-->";
					fp<<G.vexs[w]<<"-->";
				}	
       		}
       		cout<<G.vexs[v]<<"\t\t距离："<<d[u][v]<<endl;
       		fp<<G.vexs[v]<<"\t\t距离："<<d[u][v]<<endl;
		}
    }	
}
Displaymenu()
{
	cout<<"\t\t\t\t景点路径查询系统"<<endl<<endl;
	cout<<"1)查询景点之间的最短路径\t2)查看从学校到任意景点之间的距离\t3)退出系统\n";
	cout<<"请输入您的选择：";
}
int main()
{
	MGraph G;
	int choice;
	fstream fp,fp1,fp2;
	fp.open("Path.txt",ios::in);
	fp1.open("任意两点之间最短距离.txt",ios::out);
	fp2.open("学校到任意点的最短距离.txt",ios::out);
	int p[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int	p2[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int d[MAX_VERTEX_NUM];
	int d2[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	CreateGraph(G,fp);
	Displaymenu();
	cin>>choice;
	while(choice != 3)
	{
		switch(choice)
		{
			case 1:
			{
				system("cls");
				ShortestPathBetween(G,p2,d2);
				Display2(p2,d2,G,fp1);
    			for(int i = 0; i < MAX_VERTEX_NUM; i++)
					for(int j = 0; j < MAX_VERTEX_NUM; j++)
						memset(p2[i][j],0,sizeof(p2[i][j])/sizeof(int));
				for(int i = 0; i < MAX_VERTEX_NUM; i++)
					memset(d2[i],0,sizeof(d2[i])/sizeof(int));
    			system("pause");system("cls");Displaymenu();cin>>choice;;
				break;
			}
			case 2:
			{
			system("cls");string start = "南航";ShortPath(G,start,p,d);
			Display(p,d,G,fp2);
			for(int i = 1; i < MAX_VERTEX_NUM; i++)
				memset(p[i],0,sizeof(p[i])/sizeof(int));
			memset(d,0,sizeof(d)/sizeof(int));
			system("pause");system("cls");Displaymenu();cin>>choice;break;
			}
		}
	}
	fp.close();
	fp1.close();
	fp2.close();
}

