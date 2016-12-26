#include <iostream>
#include <stdlib.h>
#include <fstream> 
#include <time.h>
#include <windows.h>
#include <queue>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define M 3 		//营业窗口数 
#define N 100		//产生顾客数 
#define VIPNum 10		//vip比率 1/VIPNum 
#define VIPHighDegree 3   //vip最高等级 
#define Leaveradio 10	//中途离开率1/Leaveradio
#define MaxServeTime 10		//最大服务时间MaxServeTime/10 
using namespace std;
queue<string> Info; 		//消息队列 
typedef int Status;
typedef struct Customer
{
	int No;					//顾客编号 
	double arrTime;			//到达时间，精确到小数点一位 
	double serveTime;		//需要服务时间 
	int Status;				//状态0:等待  1：服务中
	int prior;				//数值越大优先级越高 
	double servedTime; 		//已接收服务时长
	double waitTime;    	//等待时长; 
	struct Customer *next;	//下一位顾客 
}Customer,*QueuePtr;
typedef Customer ElemType;
typedef struct
{
	QueuePtr front;		//队头指针
	QueuePtr rear;		//队尾指针
}LinkQueue;
Status InitQueue(LinkQueue &Q){
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(Customer));		//队列头 
	if (!Q.front)
		exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}
int QueueLength(LinkQueue Q){
	QueuePtr p;
	int i = 0;
	p = Q.front->next;
	while(p)
	{
		i++;
		p = p->next;
	}
	return i;
}
Status EnQueue(LinkQueue &Q, ElemType e, int i){
	string info,temp; 
	char buf[10];
	QueuePtr p = (QueuePtr)malloc(sizeof(Customer)),q;
	if(!p)
		exit(OVERFLOW);
	p->No = e.No;
	p->prior = e.prior;
	p->arrTime = e.arrTime;
	p->serveTime = e.serveTime;
	p->Status = 0;		//初始化为等待 
	p->servedTime = 0;
	p->waitTime = 0;
	if(p->prior != 0 && Q.front->next)	//vip顾客到前方插队 
	{
		q = Q.front->next;
		while(q->next)
		{
			if(q->next->prior < p->prior)
				break;
			q = q->next;
		}
		p->next = q->next;
		q->next = p;
		if(p->next == NULL)	//使队尾
			Q.rear = p; 
	} 
	else				//普通顾客直接到最后排队 
	{
		p->next = NULL;
		Q.rear->next = p;
		Q.rear = p;
	}
	if(p->prior != 0){
		sprintf(buf,"%d",p->prior);
		temp = "欢迎VIP";
		string temp2;
		temp2 = temp + buf;
		temp = "级顾客";
		temp = temp2 + temp; 
	}
	else 
		temp = "欢迎顾客"; 
	sprintf(buf,"%d",p->No);
	info = temp+buf;
	temp = "，请您到窗口";
	temp = info + temp;
	sprintf(buf,"%d",i+1);
	info = temp + buf;
	temp = "排队";
	info += temp;
	Info.push(info);
	return OK;
}
Status DeQueue(LinkQueue &Q){
	string info,temp; 
	char buf[10];
	QueuePtr p;
	if (Q.front == Q.rear)
		return ERROR;
	else
	{
		p = Q.front->next;
		Q.front->next = p->next;
		if (Q.rear == p)	//出队结点为队尾结点
			Q.rear = Q.front;
		sprintf(buf,"%d",p->No);
		temp = "顾客"; 
		info = temp+buf;
		temp = "服务完成离开，总共等待时长";
		info += temp;
		sprintf(buf,"%.1f",p->waitTime);
		info += buf;
		temp = "h";
		info += temp;
		Info.push(info);
		free (p);
		return OK;
	}
}
int whichQueue(LinkQueue Q[])		//选择队伍长度最小的队伍插入 
{
	typedef struct{
		int no;			//队伍编号
		int qlength; 	//队伍长度 
	}length;
	length L[M],temp;
	int i,j,flag;
	for(i = 0; i < M; i++){
		L[i].no = i; 
		L[i].qlength = QueueLength(Q[i]);
	}
	for (j = 0; j < M - 1; j++)		//稳定的冒泡排序 
    {
    	flag = 0;
        for (i = 0; i < M - 1 - j; i++)
        {
            if(L[i].qlength > L[i + 1].qlength)
            {
            	flag = 1;
                temp.no = L[i].no;
                temp.qlength = L[i].qlength;
                L[i].no = L[i + 1].no;
                L[i].qlength = L[i + 1].qlength;
                L[i + 1].no = temp.no;
                L[i + 1].qlength = temp.qlength;
            }
        }
        if(flag == 0)
        	break;
    }
	return L[0].no; 
}
void CreateCustomer(){
	fstream fp;
	fp.open("Customer.txt",ios::out); 
	srand(time(0)); 
	int flag,i,j;
	double a[N],temp;
	for(i = 0; i < N; i++){
		a[i] = (rand()%181)/10.0;
		while(a[i] < 8.0)
			a[i] = (rand()%181)/10.0;
	}
	for (j = 0; j < N - 1; j++)
    {
    	flag = 0;
        for (i = 0; i < N - 1 - j; i++)
        {
            if(a[i] > a[i + 1])
            {
            	flag = 1;
                temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
            }
        }
        if(flag == 0)
        	break;
    }
    for(i = 0; i < N; i++){
    	double temp = (rand()%MaxServeTime)/10.0;
    	int prior =  (rand()%VIPNum);			//1/VIPNum的vip 
    	while(temp == 0)
    		temp = (rand()%MaxServeTime)/10.0;
    	fp<<a[i]<<" "<<temp<<" ";
    	if(prior == 0)		
    		fp<<(rand()%VIPHighDegree+1)<<endl;			//随机分配vip等级 1`VIPHighDegree 
    	else
    		fp<<0<<endl;
    }
    fp.close();
}
queue<Customer> Addcustomer(){
	fstream fp;
	Customer temp;
	int prior;
	int no = 1;
	fp.open("Customer.txt",ios::in);
	queue<Customer> qtemp;
	temp.No = no;
	no++;
	fp>>temp.arrTime>>temp.serveTime>>temp.prior;
	while(!fp.eof()) 
	{	
		qtemp.push(temp);
		temp.No = no;
		no++;
		fp>>temp.arrTime>>temp.serveTime>>temp.prior;
	}
	return qtemp;
	fp.close();
}
void addTime(LinkQueue Q[]) {
	int i;
	QueuePtr p;
	for(i = 0; i < M; i++)
	{
		p = Q[i].front->next;
		while(p)
		{
			if(p->Status == 0)	//在等待 
				p->waitTime += 0.1;
			else
				p->servedTime += 0.1; 
			p = p->next;
		}
	}
}
void CheckLeave(LinkQueue Q[]){
	int i;
	QueuePtr p;
	for(i = 0; i < M; i++)
	{
		p = Q[i].front->next;			//检查队首的人是否服务完成 
		if(p){							//队首不为空 
			if((p->serveTime-p->servedTime) < 0.00001){
		//		cout<<p->serveTime<<" "<<p->servedTime<<endl;
				DeQueue(Q[i]);
			}
		}
	}
}
void Leave(LinkQueue &Q, int i){
	int j = 0;
	string info,temp; 
	char buf[10];
	QueuePtr p = Q.front->next->next,q = Q.front->next;		//p是要离开的顾客,q记录p的前驱 
	while(p && j != i)
	{
		q = p;
		p = p->next;
		j++;
	}
	q->next = p->next;
	if(q->next == NULL)
		Q.rear = q;
	sprintf(buf,"%d",p->No);
	temp = "顾客"; 
	info = temp+buf;
	temp = "中途离开，总共等待时长";
	info += temp;
	sprintf(buf,"%.1f",p->waitTime);
	info += buf;
	temp = "h";
	info += temp;
	Info.push(info);
	free(p);
}
Display(LinkQueue Q[],fstream &fp){
	int i;
	QueuePtr p;
	for(i = 0; i < M; i++)
	{
		cout<<"窗口"<<i+1<<":";
		fp<<"窗口"<<i+1<<":";
		p = Q[i].front->next;
		while(p){
			cout<<p->No<<" ";
			fp<<p->No<<" ";
			p = p->next;
		}
		cout<<endl;
		fp<<endl;
	}
	fp<<endl; 
}
int main()
{
	int i,j;
	double time;
	fstream fp;
	fp.open("Log.txt",ios::out);
	Customer customer;
	LinkQueue Q[M];				//产生营业窗口队列
	for(i = 0; i < M; i++)
		InitQueue(Q[i]);
	CreateCustomer();			//产生随机顾客 
	queue<Customer> qtemp = Addcustomer();
	for(time = 8.0; time < 18.1; time = time+0.1)	//模拟一天(8.0~18.0)
	{
		if(time > 0)									//增加等待时间和服务时间 
			addTime(Q);
		CheckLeave(Q);									//检查是否有人服务时间结束离开	
		if(rand()%Leaveradio == 0)					//一定几率有人中途离开 
		{
			for(i = 0; i < M; i++)
			{
				if(QueueLength(Q[i]) > 1)
				{
					Leave(Q[i],rand()%(QueueLength(Q[i])-1));
					break;
				}
			 } 
		} 	
		if(!qtemp.empty()){
			customer = qtemp.front();
			while((customer.arrTime-time) < 0.00001)		//有顾客来袭 
			{
				qtemp.pop();							//删除 	
				int QueueInsert = whichQueue(Q);
				EnQueue(Q[QueueInsert],customer,QueueInsert);		//入队列 
				if(qtemp.empty())
					break;
				customer = qtemp.front();
			}
		}	
		for(i = 0; i < M; i++){
			if(Q[i].front->next)						//队首不为空 
				Q[i].front->next->Status = 1;				//将队首的顾客变为服务状态	
		}
		cout<<"Time:"<<time<<endl;
		if(Info.empty()){ 
			cout<<"欢迎光临！"<<endl;
			fp<<time<<":欢迎光临！"<<endl;
		} 
		while(!Info.empty())
		{
			cout<<Info.front()<<endl;
			fp<<time<<":"<<Info.front()<<endl;
			Info.pop();
		}
		Display(Q,fp);
		Sleep(100);
		system("cls");
	}
	for(i = 0; i < M; i++)
	{
		QueuePtr p = Q[i].front->next;
		while(p)
		{
			cout<<"顾客"<<p->No<<"对不起，营业时间已到，请明日再来！"<<endl;
			fp<<"顾客"<<p->No<<"对不起，营业时间已到，请明日再来！"<<endl;
			p = p->next;
		}
	}
	fp.close();
	return 0;
 } 
