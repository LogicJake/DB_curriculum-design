#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#define OK 1
#define ERROR -1
#define m 3 //3����
#define N 16 //����Ԫ�ظ���
using namespace std;
typedef int KeyType;
//struct Others  //��¼����������
//{
//	string info;
//};
struct Record
{
	KeyType key; //�ؼ���
	char info[10]; //��������
};
typedef struct BTNode
{
	int keynum; //����йؼ��ָ���
	BTNode *parent;//ָ��˫�׽ڵ�
   	struct Node  //�����������
	{
		KeyType key; //�ؼ�������
   		BTNode *ptr;//����ָ������
   		const Record *recptr; //��¼����ָ��
   	}node[m+1];
}BTNode,*BTree;
struct Result //B���Ĳ��ҽ������ 
{
	BTNode *pt; //ָ���ҵ��Ľ��
	int i;
	int tag; //1��ʾ���ҳɹ���0��ʾ����ʧ�ܡ�
};

int InitDSTable(BTree &DT)
{
	DT = NULL;
	return OK;
}

void DestroyDSTable(BTree &DT)
{
	int i;
	if(DT)
    {
    	for(i=0;i<=DT->keynum;i++)
        	DestroyDSTable(DT->node[i].ptr);
    	free(DT);
    	DT = NULL;
    }
}

int Search(BTree p,KeyType K)
{
    int i=0,j;
    for(j=1; j <= p->keynum; j++)
        if(p->node[j].key <= K)
            i = j;
    return i;
}

void Insert(BTree &q,int i,const Record *r,BTree ap)
{
    int j;
    for(j=q->keynum;j>i;j--)
    	q->node[j+1]=q->node[j];
    q->node[i+1].key=r->key;
    q->node[i+1].ptr=ap;
    q->node[i+1].recptr=r;
    q->keynum++;
}

void NewRoot(BTree &T,const Record *r,BTree ap)
{
	BTree p;
	p = (BTree)malloc(sizeof(BTNode));
    p->node[0].ptr = T;
	T = p;
	if(T->node[0].ptr)
    	T->node[0].ptr->parent = T;
	T->parent=NULL;
	T->keynum=1;
	T->node[1].key=r->key;
	T->node[1].recptr=r;
	T->node[1].ptr=ap;
	if(T->node[1].ptr)
    	T->node[1].ptr->parent=T;
}

void split(BTree &q,BTree &ap)
{
	int i,s=(m+1)/2;
	ap=(BTree)malloc(sizeof(BTNode));
	ap->node[0].ptr=q->node[s].ptr;
	for(i=s+1;i<=m;i++)
   	{
   		ap->node[i-s]=q->node[i];
   		if(ap->node[i-s].ptr)
       		ap->node[i-s].ptr->parent=ap;
   }
   ap->keynum=m-s;
   ap->parent=q->parent;
   q->keynum=s-1;
}

void InsertBTree(BTree &T,const Record *r,BTree q,int i)
{
	BTree ap=NULL;
	int finished = false;
	int s;
	const Record *rx;
	rx=r;
	while(q&&!finished)
   	{
   		Insert(q,i,rx,ap);
    	if(q->keynum<m)
        	finished = true;
  		else
    	{
      		s=(m+1)/2;
     		rx=q->node[s].recptr;
     		split(q,ap);
      		q=q->parent;
      		if(q)
          		i=Search(q,rx->key);
     	}
   }
	if(!finished) 
		NewRoot(T,rx,ap);    
}

Result SearchBTree(BTree T,KeyType K)
{
	BTree p=T,q=NULL;
	int found=false;
	int i=0;
	Result r;
	while(p&&!found)
   	{
   		i=Search(p,K);
   		if(i>0&&p->node[i].key==K)
       		found=true;
   		else 
     	{
     		q=p;
    		p=p->node[i].ptr;
     	}
    }
   	r.i=i;
   	if(found)
    {
    	r.pt=p;
      	r.tag=1;
    }
   	else 
    {
    	r.pt=q;
    	r.tag=0;
    }
    return r;
}

void print(BTNode c,int i) 
{
    cout<<"("<<c.node[i].key<<","<<c.node[i].recptr->info<<")"<<endl;
 }
void TraverseDSTable(BTree DT,void(*Visit)(BTNode,int))
{
	int i; 
	if(DT)
    {
    	if(DT->node[0].ptr)
        	TraverseDSTable(DT->node[0].ptr,Visit);
      	for(i=1;i<=DT->keynum;i++)
        {
         	Visit(*DT,i);
         	if(DT->node[i].ptr)
         		TraverseDSTable(DT->node[i].ptr,Visit);
        }
    }
}

void InputBR(BTree &t,const Record &r)
{
	Result s;    
    s = SearchBTree(t,r.key);
    if(!s.tag)
       	InsertBTree(t,&r,s.pt,s.i);
}

void UserSearch(BTree t)
{
	int i;
	Result s;
	cout<<"����������Ҽ�¼�Ĺؼ���: ";
	cin>>i;
	s = SearchBTree(t,i);
	if(s.tag)
		print(*(s.pt),s.i);
	else
		cout<<"û�ҵ�";
	cout<<endl;
}
void DeleteIt(BTree t,BTNode *dnode,int id)
{
	if(dnode->keynum>=ceil(m/2))
   	{
    	dnode->keynum--;
    	dnode->node[id].ptr=NULL;
   	}//if��ɾ�ؼ���Ki���ڽ��Ĺؼ�����Ŀ��С��ceil(m/2)����ֻ��ӽ����ɾ��Ki����Ӧָ��Ai�������������ֲ��䡣
	else if((dnode->keynum==(ceil(m/2)-1))&&((id+1)<(m-1))&&dnode->parent->node[id+1].ptr->keynum>(ceil(m/2)-1))
   	{
    	for(int i=1;i<m&&dnode->parent->node[i].key < dnode->parent->node[id+1].ptr->node[1].key;i++)
        	dnode->node[i].key=dnode->parent->node[i].key;
    	dnode->parent->node[1].key=dnode->parent->node[id+1].ptr->node[1].key;
    	(dnode->parent->node[id+1].ptr->keynum)--;
   	}//else if ��ɾ�ؼ���Ki���ڽ��Ĺؼ�����Ŀ����ceil(m/2)-1���������������Ϊ�����ֵܵ���
	else if((dnode->keynum==(ceil(m/2)-1))&&((id-1)>0    )&&dnode->parent->node[id-1].ptr->keynum>(ceil(m/2)-1))
   	{
   		for(int i=1;i<m&&dnode->parent->node[i].key > dnode->parent->node[id-1].ptr->node[dnode->parent->node[id-1].ptr->keynum].key;i++)
        	dnode->node[i].key=dnode->parent->node[i].key;
    	dnode->parent->node[1].key=dnode->parent->node[id-1].ptr->node[dnode->parent->node[id-1].ptr->keynum].key;
    	(dnode->parent->node[id-1].ptr->keynum)--;
   	}//2-else if��ɾ�ؼ���Ki���ڽ��Ĺؼ�����Ŀ����ceil(m/2)-1���������������Ϊ�����ֵܵ���	
	else if((dnode->keynum==(ceil(m/2)-1))&&((id+1)<(m-1))&&dnode->parent->node[id+1].ptr->keynum==(ceil(m/2)-1))
   	{
    	do
      	{
        	BTree tmp;
        	tmp=dnode;
       		dnode->parent->node[id+1].ptr->node[2]=dnode->parent->node[id+1].ptr->node[1];
       		dnode->parent->node[id+1].ptr->node[1]=dnode->parent->node[1];
      		dnode->parent->node[id+1].ptr->keynum++;
      		dnode->parent->node[id+1].ptr->node[0].ptr=dnode->node[1].ptr;
       		dnode->parent->keynum--;
       		dnode->parent->node[id].ptr=NULL;
       		tmp=dnode;
       		if(dnode->parent->keynum>=(ceil(m/2)-1))
           		dnode->parent->node[1]=dnode->parent->node[2];
       		dnode=dnode->parent;
     		free(tmp);
      	}while(dnode->keynum<(ceil(m/2)-1));    //˫����keynum<
   	}//3-else if��ɾ�ؼ���Ki���ڽ����������ֵܽ���еĵĹؼ�����Ŀ������ceil(m/2)-1�����μ������ֵܴ��� 
	else if((dnode->keynum==(ceil(m/2)-1))&&(id-1)>0      &&dnode->parent->node[id-1].ptr->keynum==(ceil(m/2)-1))
  	{ 
    	do
      	{
       		BTree tmp;
        	tmp=dnode;
       		dnode->parent->node[id-1].ptr->node[2]=dnode->parent->node[id-1].ptr->node[1];
       		dnode->parent->node[id-1].ptr->node[1]=dnode->parent->node[1];
       		dnode->parent->node[id-1].ptr->keynum++;
      	 	dnode->parent->node[id-1].ptr->node[0].ptr=dnode->node[1].ptr;
       		dnode->parent->keynum--;
       		dnode->parent->node[id].ptr=NULL;
       		tmp=dnode;
      		if(dnode->parent->keynum>=(ceil(m/2)-1))
           		dnode->parent->node[1]=dnode->parent->node[2];
       		dnode=dnode->parent;
       		free(tmp);
      	}while(dnode->keynum<(ceil(m/2)-1));
   }//4-else if��ɾ�ؼ���Ki���ڽ����������ֵܽ���еĵĹؼ�����Ŀ������ceil(m/2)-1�����μ������ֵܴ��� 
	else cout<<"Error!";
}
void UserDelete(BTree t)
{
	KeyType temp;
	Result s;
	cout<<"����������Ҫɾ���Ĺؼ��֣�:\n";
	cin>>temp;
	s = SearchBTree(t,temp);
	if(!s.tag)  
		cout<<"����ʧ��!\n";
	else 
   		DeleteIt(t,s.pt,s.i);
}
void displaymenu()
{
	cout<<"\t\tB-Treeϵͳ"<<endl<<endl;
	cout<<"\t"<<setw(20)<<left<<"1)����"<<setw(20)<<left<<"2)ɾ��"<<endl;
	cout<<"\t"<<setw(20)<<left<<"3)��ѯ"<<setw(20)<<left<<"4)��ʾ"<<endl; 
	cout<<"\t���������ѡ��";
 } 
int main()
{
	int choice;
	fstream fp;
	fp.open("Data.txt",ios::in);
	Record rtemp;
	BTree t;
	InitDSTable(t);
	Record r[N]={{24,"1"},{45,"2"},{53,"3"},{12,"4"},{37,"5"},
      			{50,"6"},{61,"7"},{90,"8"},{100,"9"},{70,"10"},
        		{3,"11"},{30,"12"},{26,"13"},{85,"14"},{3,"15"},
       			{7,"16"}};    
	for(int i = 0; i < N; i++) {
		InputBR(t,r[i]);
		}
	displaymenu();
	cin>>choice;
	while(choice != 5)
	{
		switch(choice)
		{
			case 1:{
				system("cls");
				string temp;
				cout<<"������Ҫ����ļ�¼����Ϣ"<<endl;
				cout<<"�ؼ��֣�";
				cin>>rtemp.key;
				cout<<"���֣�";
				cin>>rtemp.info;
				InputBR(t,rtemp);
				temp.clear();
				system("pause");
				system("cls");
				displaymenu();
				fflush(stdin);
				cin>>choice;
				break;
			}
			case 2:{
				system("cls");
				UserDelete(t);
				system("pause");
				system("cls");
				displaymenu();
				fflush(stdin);
				cin>>choice;
				break;
			}
			case 3:{
				system("cls");
				UserSearch(t);
				system("pause");
				system("cls");
				displaymenu();
				fflush(stdin);
				cin>>choice;
				break;
			} 
			case 4:
			{
				system("cls");
				TraverseDSTable(t,print);
				system("pause");
				system("cls");
				displaymenu();
				fflush(stdin);
				cin>>choice;
				break;
			}
		}
	}
	fp.close();
	return 1;
}
