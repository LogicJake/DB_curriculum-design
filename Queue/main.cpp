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
#define M 3 		//Ӫҵ������ 
#define N 100		//�����˿��� 
#define VIPNum 10		//vip���� 1/VIPNum 
#define VIPHighDegree 3   //vip��ߵȼ� 
#define Leaveradio 10	//��;�뿪��1/Leaveradio
#define MaxServeTime 10		//������ʱ��MaxServeTime/10 
using namespace std;
queue<string> Info; 		//��Ϣ���� 
typedef int Status;
typedef struct Customer
{
	int No;					//�˿ͱ�� 
	double arrTime;			//����ʱ�䣬��ȷ��С����һλ 
	double serveTime;		//��Ҫ����ʱ�� 
	int Status;				//״̬0:�ȴ�  1��������
	int prior;				//��ֵԽ�����ȼ�Խ�� 
	double servedTime; 		//�ѽ��շ���ʱ��
	double waitTime;    	//�ȴ�ʱ��; 
	struct Customer *next;	//��һλ�˿� 
}Customer,*QueuePtr;
typedef Customer ElemType;
typedef struct
{
	QueuePtr front;		//��ͷָ��
	QueuePtr rear;		//��βָ��
}LinkQueue;
Status InitQueue(LinkQueue &Q){
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(Customer));		//����ͷ 
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
	p->Status = 0;		//��ʼ��Ϊ�ȴ� 
	p->servedTime = 0;
	p->waitTime = 0;
	if(p->prior != 0 && Q.front->next)	//vip�˿͵�ǰ����� 
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
		if(p->next == NULL)	//ʹ��β
			Q.rear = p; 
	} 
	else				//��ͨ�˿�ֱ�ӵ�����Ŷ� 
	{
		p->next = NULL;
		Q.rear->next = p;
		Q.rear = p;
	}
	if(p->prior != 0){
		sprintf(buf,"%d",p->prior);
		temp = "��ӭVIP";
		string temp2;
		temp2 = temp + buf;
		temp = "���˿�";
		temp = temp2 + temp; 
	}
	else 
		temp = "��ӭ�˿�"; 
	sprintf(buf,"%d",p->No);
	info = temp+buf;
	temp = "������������";
	temp = info + temp;
	sprintf(buf,"%d",i+1);
	info = temp + buf;
	temp = "�Ŷ�";
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
		if (Q.rear == p)	//���ӽ��Ϊ��β���
			Q.rear = Q.front;
		sprintf(buf,"%d",p->No);
		temp = "�˿�"; 
		info = temp+buf;
		temp = "��������뿪���ܹ��ȴ�ʱ��";
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
int whichQueue(LinkQueue Q[])		//ѡ����鳤����С�Ķ������ 
{
	typedef struct{
		int no;			//������
		int qlength; 	//���鳤�� 
	}length;
	length L[M],temp;
	int i,j,flag;
	for(i = 0; i < M; i++){
		L[i].no = i; 
		L[i].qlength = QueueLength(Q[i]);
	}
	for (j = 0; j < M - 1; j++)		//�ȶ���ð������ 
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
    	int prior =  (rand()%VIPNum);			//1/VIPNum��vip 
    	while(temp == 0)
    		temp = (rand()%MaxServeTime)/10.0;
    	fp<<a[i]<<" "<<temp<<" ";
    	if(prior == 0)		
    		fp<<(rand()%VIPHighDegree+1)<<endl;			//�������vip�ȼ� 1`VIPHighDegree 
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
			if(p->Status == 0)	//�ڵȴ� 
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
		p = Q[i].front->next;			//�����׵����Ƿ������� 
		if(p){							//���ײ�Ϊ�� 
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
	QueuePtr p = Q.front->next->next,q = Q.front->next;		//p��Ҫ�뿪�Ĺ˿�,q��¼p��ǰ�� 
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
	temp = "�˿�"; 
	info = temp+buf;
	temp = "��;�뿪���ܹ��ȴ�ʱ��";
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
		cout<<"����"<<i+1<<":";
		fp<<"����"<<i+1<<":";
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
	LinkQueue Q[M];				//����Ӫҵ���ڶ���
	for(i = 0; i < M; i++)
		InitQueue(Q[i]);
	CreateCustomer();			//��������˿� 
	queue<Customer> qtemp = Addcustomer();
	for(time = 8.0; time < 18.1; time = time+0.1)	//ģ��һ��(8.0~18.0)
	{
		if(time > 0)									//���ӵȴ�ʱ��ͷ���ʱ�� 
			addTime(Q);
		CheckLeave(Q);									//����Ƿ����˷���ʱ������뿪	
		if(rand()%Leaveradio == 0)					//һ������������;�뿪 
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
			while((customer.arrTime-time) < 0.00001)		//�й˿���Ϯ 
			{
				qtemp.pop();							//ɾ�� 	
				int QueueInsert = whichQueue(Q);
				EnQueue(Q[QueueInsert],customer,QueueInsert);		//����� 
				if(qtemp.empty())
					break;
				customer = qtemp.front();
			}
		}	
		for(i = 0; i < M; i++){
			if(Q[i].front->next)						//���ײ�Ϊ�� 
				Q[i].front->next->Status = 1;				//�����׵Ĺ˿ͱ�Ϊ����״̬	
		}
		cout<<"Time:"<<time<<endl;
		if(Info.empty()){ 
			cout<<"��ӭ���٣�"<<endl;
			fp<<time<<":��ӭ���٣�"<<endl;
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
			cout<<"�˿�"<<p->No<<"�Բ���Ӫҵʱ���ѵ���������������"<<endl;
			fp<<"�˿�"<<p->No<<"�Բ���Ӫҵʱ���ѵ���������������"<<endl;
			p = p->next;
		}
	}
	fp.close();
	return 0;
 } 
