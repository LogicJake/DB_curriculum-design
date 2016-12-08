#include <iostream>
#include <fstream>
using namespace std;
#include <stack>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define MAXSIZE 100	//MAZESIZE*2+1 < MAXSIZE 
#define MAZESIZE 10	//迷宫大小 = MAZESIZE*2+1 
typedef int Status;
typedef int PosType[2];
typedef struct{
	int ord;	 //通道块在路径上的“序号” 
	PosType seat;//通道块在迷宫中的“坐标位置” 
	int di;		 //从此通道块走向下一通道块的“方向” 
}SElemType;
int fy[MAXSIZE][MAXSIZE];
int d[][2] = {{0,1},{1,0},{0,-1},{-1,0}}, w = MAZESIZE, h = MAZESIZE, u = w*2+1, v = h*2+1;	//u:宽度 v:高度 
stack<SElemType>s;	//存放路径 
int Createmaze(int y, int x)
{
    if(x < 1 || y < 1 || x >= u-1 || y >= v-1 || fy[y][x])
        return 0;
    else fy[y][x] = 1;
    for (int f = rand()%4, i=0, p = rand()&1?3:1; i < 4; ++i,f = (f+p)%4)
        if(Createmaze(y+*d[f]*2,x+d[f][1]*2)) 
			fy[y+*d[f]][x+d[f][1]] = 1;
    return 1;
}
void Initmaze()
{
	fstream fp;
    fp.open("maze.txt",ios::out);
    srand(time(NULL));
	Createmaze(1,1);
    for (int y = 0; y < v; ++y)
    {    
		for (int x = 0; x < u; ++x)
        {
      	  	cout<<(fy[y][x]?"  ":"█");
     	    fp<<(fy[y][x]?"  ":"█");
        }
		puts("");
		fp<<endl;
    }
    fp.close();
}
void Print()
{
	SElemType e;
	system("cls");
	for (int y = 0; y < v; ++y)
    {    
		for (int x = 0; x < u; ++x)
        {
        	if(fy[y][x] == 1 || fy[y][x] == -1){
        		cout<<"  ";
        	}
        	if(fy[y][x] == 0){
      	 		cout<<"█";
			}
			if(fy[y][x] == 2){
      	 		cout<<"○";
     		}
        }
		puts("");
    }
	//getchar();
	Sleep(90);	//休眠1s后更新迷宫数据 
}
void save_solve()
{
	fstream fp;
  	fp.open("maze_solve.txt",ios::out);
	SElemType e;
	for (int y = 0; y < v; ++y)
    {    
		for (int x = 0; x < u; ++x)
        {
        	if(fy[y][x] == 1 || fy[y][x] == -1){
        		fp<<"  ";
        	}
        	if(fy[y][x] == 0){
      	 		fp<<"█";
			}
			if(fy[y][x] == 2){
      	 		fp<<"○";
     		}
        }
		fp<<endl;
    }
    fp.close();
}
void Nextpos(PosType &curpos, int i)
{
	switch(i)
	{
		case 1:curpos[0] = curpos[0];curpos[1] = curpos[1]+1;break;
		case 2:curpos[0] = curpos[0];curpos[1] = curpos[1]-1;break;
		case 3:curpos[0] = curpos[0]+1;curpos[1] = curpos[1];break;
		case 4:curpos[0] = curpos[0]-1;curpos[1] = curpos[1];break;
	}
}

Status Pass(PosType pos)
{
	if(fy[pos[0]][pos[1]] == 1)
		return 1;
	else
		return 0;
} 
Status mazepath(PosType start,PosType end)
{
	fstream fp;
    fp.open("log.txt",ios::out);
	SElemType e;
	PosType curpos;
	int curstep = 1;
	curpos[0] = start[0];
	curpos[1] = start[1];
	do{
		if(Pass(curpos)){
			fp<<"走到("<<curpos[0]<<","<<curpos[1]<<")位置"<<endl; 
			fy[curpos[0]][curpos[1]] = 2;	//代表走过 
			Print();
			e.ord = curstep;
			e.seat[0] = curpos[0];
			e.seat[1] = curpos[1];
			e.di = 1;
			s.push(e);
			if(curpos[0] == end[0] && curpos[1] == end[1])
				return 1;
			Nextpos(curpos,1);
			fp<<"向右走,";
			curstep++; 
		}
		else{
			fp<<"位置("<<curpos[0]<<","<<curpos[1]<<")不通,尝试后退"<<endl;
			if(!s.empty())
			{
				e = s.top();
				s.pop();
				fp<<"回退到("<<e.seat[0]<<","<<e.seat[1]<<")"<<endl;
				while(e.di == 4 && !s.empty())
				{
					fp<<"位置("<<e.seat[0]<<","<<e.seat[1]<<")不通"<<endl;
					fy[e.seat[0]][e.seat[1]] = -1;	//代表走过
					Print();
					e = s.top();
					s.pop();
					fp<<"回退到("<<e.seat[0]<<","<<e.seat[1]<<")"<<endl;
				}
				if(e.di < 4){
					e.di++;
					s.push(e);
					curpos[0] = e.seat[0];
					curpos[1] = e.seat[1];
					Nextpos(curpos,e.di);
					switch(e.di)
					{
						case 1:fp<<"向右走,";break;
						case 2:fp<<"向左走,";break;
						case 3:fp<<"向下走,";break;
						case 4:fp<<"向上走,";break;
					 }  
				}
			}
		}
	}while(!s.empty());
	return 0;
} 
int main()
{
	Initmaze();
	PosType start,end; 
//	fy[1][0] = fy[v-2][0] = 1;
	start[0] = 1;
	start[1] = 0;
	end[0] = v-2;
	end[1] = u-1;
	fy[start[0]][start[1]] = fy[end[0]][end[1]] = 1;	//初始化出入口 
	if(mazepath(start,end))
	{
		save_solve();
		cout<<"success!";
		getchar(); 
	}
	else 
		cout<<"fail!";
}
