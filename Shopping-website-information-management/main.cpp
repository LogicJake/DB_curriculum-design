#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define goodsNumber 6	//��Ʒ��������� 
#define ShopNumber 16
using namespace std;
char FileName[] = "Shops.txt";
typedef struct Items
{
	char ItemsName[10];
	float price;
	int Sales;
}Items;
typedef struct Shop
{
	int number;
	char ShopName[20];
	int CreditWorthiness;
	int ItemsNumber;		//�̵�������Ʒ���������� 
	Items goods[goodsNumber];
}Shop;
typedef Shop ElemType;
 istream& operator>>(istream& in, Items& s)
 {
     in>>s.ItemsName>>s.price>>s.Sales;
     return in;
 }
 ostream& operator<<(ostream& out, const Items& s)
 {
     out<<s.ItemsName<<" "<<s.price<<" "<<s.Sales<<" "; 
     return out;
 }
istream& operator>>(istream& in, Shop& s)
{
    in>>s.number>>s.ShopName>>s.CreditWorthiness>>s.ItemsNumber;
    for (int i = 0; i < s.ItemsNumber; ++i)
    	in>>s.goods[i];
	return in;
}
ostream& operator<<(ostream& out, const Shop& s)
{
	int i;
    out<<s.number<<" "<<s.ShopName<<" "<<s.CreditWorthiness<<" "<<s.ItemsNumber<<" "; 
    for (i = 0; i < s.ItemsNumber - 1; ++i)
    	out<<s.goods[i];
    out<<s.goods[i].ItemsName<<" "<<s.goods[i].price<<" "<<s.goods[i].Sales;
	return out;
}
typedef int Status;
typedef struct Node
{
    ElemType data;
    struct Node *next;
}Node;
typedef struct Node *LinkList; 
typedef struct DuLNode
{
    ElemType data;
    struct DuLNode *prior;
    struct DuLNode *next;
}DuLNode,*DuLinkList;
typedef struct Node *LinkList; 
void DisplayMenu()
{
	cout<<"\t\t������վ��Ϣ����\n\n";
	cout<<"<1>��ȡ������Ϣ\t\t<2>�����̽��в���\t<3>�޸���Ʒ�۸�\n";
	cout<<"<4>��ѯ��Ʒ\t\t<5>������Ʒ\t\t<6>�˳�"<<endl; 
	cout<<"����ѡ��";
}
int GetLength(LinkList L)	//������ĳ��� 
{
	LinkList p = L->next;
	int i = 0;
	while(p)
	{
		i++;
		p = p->next;
	}
	return i;
}
LinkList ReadData()
{
	fstream fp;
	fp.open(FileName,ios::in);
	if(fp.fail())
	{
		cout<<"��ʧ�ܣ�";
		return ERROR;
	}
	LinkList L,p,q;
	L = (LinkList)malloc(sizeof(Node)); /* ����ͷ���,��ʹLָ���ͷ��� */
    if(L == NULL) /* �洢����ʧ�� */
            return ERROR;
    q = L;
	while(!fp.eof())
	{	
		p = (LinkList)malloc(sizeof(Node));
	 	fp>>p->data;
	 	q->next = p;
	 	p->next = NULL;	
		q = p;	
	}
	fp.close();
	p = L->next;  
   	while(p)  
   	{  
       cout<<p->data<<endl; 
       p = p->next; 
  	}  
  	return L;
}
void play(LinkList L)
{
	LinkList p;
	p = L->next;
	while(p)  
   	{  
       cout<<p->data<<endl; 
       p=p->next; 
  	}  
}
void sort(DuLinkList &L, int flag)		//��˫��ѭ���������� 
{
	DuLinkList p,q,r,temp;
	DuLinkList first;
	fstream fp;
	int i,j;
	char FileName[20];
	strcpy(FileName,L->next->data.goods[0].ItemsName);
	for(i = 0; i < 20; i++)
	{
		if(FileName[i] == '\0')
			break;
	}
	j = i;
	FileName[j] = '.';
	FileName[j+1] = 't';
	FileName[j+2] = 'x';
	FileName[j+3] = 't';
	FileName[j+4] = '\0';
	fp.open(FileName,ios::out);
	first = L->next->next;
	L->next->next = L;
	L->prior = L->next;
	while(first != L)
	{
		p = L->next;
		temp = first;
		first = first->next;
		temp->next = NULL;
		while(p->next != L && p->data.goods[0].Sales > temp->data.goods[0].Sales)
			p = p->next;
		if(p->data.goods[0].Sales <= temp->data.goods[0].Sales)
		{
			p->prior->next = temp;
			temp->prior = p->prior;
			temp->next = p;
			p->prior = temp; 
		}
		else 
		{
			temp->next = L;
			temp->prior = p;
			p->next = temp;
			L->prior = temp;
		}
	}
	r = L->next;
	while(r != L)
	{
		fp<<r->data<<endl;
		if(flag == 1)
			cout<<r->data<<endl;
		r = r->next;
	}
}
void AddShop(LinkList &L)
{
	fstream fp;
	LinkList p,q;
	int i,num;
	fp.open(FileName,ios::out|ios::app);
	if(fp.fail())
	{
		cout<<"��ʧ�ܣ�";
		exit(0);	
	}
	q = L->next;
	while(q->next)
		q = q->next;	//ѭ���������β 
	cout<<"���������ӵ�������Ϣ\n";
	i = GetLength(L);
	i++;
	p = (LinkList)malloc(sizeof(Node));
	p->data.number = i;
	cout<<"��������";
	cin>>p->data.ShopName;
	cout<<"�����ȣ�";
	cin>>p->data.CreditWorthiness;
	cout<<"��������Ʒ������";
	cin>>p->data.ItemsNumber;
	for(i = 0; i < p->data.ItemsNumber; i++) 
	{
		cout<<"��Ʒ���ƣ�";
		cin>>p->data.goods[i].ItemsName; 
		cout<<"��Ʒ�۸�";
		cin>>p->data.goods[i].price;
		cout<<"��Ʒ������"; 
		cin>>p->data.goods[i].Sales;
	}
	fp<<endl;
	fp<<p->data; 
	q->next = p;
	p->next = NULL;
	play(L);
	fp.close();
}
void DeleteShop(LinkList &L)
{
	fstream fp;
	int choice;
	LinkList p;
	p = L->next;
	fp.open(FileName,ios::out);
	if(fp.fail())
	{
		cout<<"��ʧ�ܣ�";
		exit(0);	
	}
	cout<<"��������Ҫɾ�����̵ı��:";
	cin>>choice;
	while(p->next->data.number != choice)
		p = p->next; 	//pָ��Ҫɾ������ǰһ��
	p->next = p->next->next;
	p = p->next;
	while(p)
	{
		p->data.number--;
		p = p->next;
	}
	p = L->next;
	while(p->next)		//�洢�ļ� 
	{
		fp<<p->data;
		fp<<endl;
		p = p->next;
	}
	fp<<p->data;
	fp.close();
}
void AddItems(LinkList &L)
{
	int Object,i;
	fstream fp;
	LinkList p;
	cout<<"���������̵ı�ţ�";
	cin>>Object;
	p = L->next;
	while(p->data.number != Object)
		p = p->next;
	cout<<"\n��ţ�"<<p->data.number<<"\t"<<"������"<<p->data.ShopName<<endl;
	cout<<"ӵ����Ʒ��";
	for(i = 0; i < p->data.ItemsNumber; i++)
		cout<<p->data.goods[i].ItemsName<<"  "; 
	p->data.ItemsNumber++;
	cout<<endl<<"������Ҫ���ӵ���Ʒ���ͼ۸�"<<endl;
	cout<<"��Ʒ����";
	cin>>p->data.goods[p->data.ItemsNumber-1].ItemsName;
	cout<<"�۸�";
	cin>>p->data.goods[p->data.ItemsNumber-1].price;
	p->data.goods[p->data.ItemsNumber-1].Sales = 0;
	fp.open(FileName,ios::out);
	if(fp.fail())
	{
		cout<<"��ʧ�ܣ�";
		exit(0);	
	}
	p = L->next;
	while(p->next)		//�洢�ļ� 
	{
		fp<<p->data;
		fp<<endl;
		p = p->next;
	}
	fp<<p->data;
	fp.close();
}
void DeleteItems(LinkList &L)
{
	int Object,i,j;
	char ItemsName[10];
	fstream fp;
	LinkList p;
	cout<<"���������̵ı�ţ�";
	cin>>Object;
	p = L->next;
	while(p->data.number != Object)
		p = p->next;
	cout<<"\n��ţ�"<<p->data.number<<"\t"<<"������"<<p->data.ShopName<<endl;
	cout<<"ӵ����Ʒ��";
	for(i = 0; i < p->data.ItemsNumber; i++)
		cout<<p->data.goods[i].ItemsName<<"  ";
	cout<<endl<<"������Ҫɾ������Ʒ����";
	cin>>ItemsName;
	i = 0;
	while(strcmp(ItemsName,p->data.goods[i].ItemsName) != 0)
		i++;
	for(j = i; j < p->data.ItemsNumber - 1; j++)
		p->data.goods[j] = p->data.goods[j+1];
	p->data.ItemsNumber--;
	fp.open(FileName,ios::out);
	if(fp.fail())
	{
		cout<<"��ʧ�ܣ�";
		exit(0);	
	}
	p = L->next;
	while(p->next)		//�洢�ļ� 
	{
		fp<<p->data;
		fp<<endl;
		p = p->next;
	}
	fp<<p->data;
	fp.close();
}
void ChangePrice(LinkList &L)
{
	char ItemsName[10];
	fstream fp;
	int i;
	int Price;
	cout<<"������Ҫ�޸ĵ���Ʒ���ͼ۸�"<<endl;
	cout<<"��Ʒ����"; 
	cin>>ItemsName;
	cout<<"�۸�";
	cin>>Price;
	LinkList p;
	p = L->next;
	while(p)
	{
		i = 0;
		while(strcmp(ItemsName,p->data.goods[i].ItemsName) != 0)
			i++;
		if(i < p->data.ItemsNumber)
			p->data.goods[i].price = Price;
		p = p->next;
	}
	fp.open("out.txt",ios::out);
	if(fp.fail())
	{
		cout<<"��ʧ�ܣ�";
		exit(0);	
	}
	p = L->next;
	while(p->next)		//�洢�ļ� 
	{
		fp<<p->data;
		fp<<endl;
		p = p->next;
	}
	fp<<p->data;
	fp.close(); 
} 
void BuyItmes(LinkList &L,DuLinkList &D);
DuLinkList SearchItems(LinkList L)
{
	char ItemsName[10];
	LinkList p;
	int i;
	DuLinkList newbase,q,r;
	newbase = (DuLinkList)malloc(sizeof(DuLNode));
	newbase->next = NULL;
	newbase->prior = NULL;
	r = newbase;
	cout<<"��Ʒ����";
	cin>>ItemsName;
	p = L->next;
	int flag;
	while(p)
	{
		flag = 0;
		for(i = 0; i < p->data.ItemsNumber; i++)
		{
			if(strcmp(p->data.goods[i].ItemsName,ItemsName) == 0)
			{
				flag = 1;
				break;
			}
		}
		if(flag == 1)
		{
			q = (DuLinkList)malloc(sizeof(DuLNode));
			strcpy(q->data.ShopName,p->data.ShopName);
			q->data.number = p->data.number;
			q->data.CreditWorthiness = p->data.CreditWorthiness;
			q->data.ItemsNumber = 1;
			q->data.goods[0] = p->data.goods[i];
			r->next = q;
			q->prior = r;
			q->next = NULL;
			r = q;
		}
		p = p->next;
	 } 
	r->next = newbase;
	newbase->prior = r;
	sort(newbase,1);//���������� 
	return newbase;
}
void BuyItmes(LinkList &L,DuLinkList &D)
{
	char ShopName[10];
	char ItemsName[10];
	fstream fp;
	int i;
	if(D != NULL)
	{
		cout<<"��������Ҫ�������Ʒ�ĵ�������"<<endl;
		cout<<"��������";
		cin>>ShopName;
		strcpy(ItemsName,D->next->data.goods[0].ItemsName);
	}
	else	
	{
		D = SearchItems(L);
		cout<<"��������Ҫ�������Ʒ����������"<<endl;
		cout<<"��������";
		cin>>ShopName; 
		strcpy(ItemsName,D->next->data.goods[0].ItemsName);
	}
	LinkList p = L->next;
	while(strcmp(p->data.ShopName,ShopName) != 0)
		p = p->next;
	i = 0;
	while(strcmp(ItemsName,p->data.goods[i].ItemsName) != 0)
		i++;
	p->data.goods[i].Sales++;
	fp.open(FileName,ios::out);
	if(fp.fail())
	{
		cout<<"��ʧ�ܣ�";
		exit(0);	
	}
	p = L->next;
	while(p->next)		//�洢�ļ� 
	{
		fp<<p->data;
		fp<<endl;
		p = p->next;
	}
	fp<<p->data;
	fp.close(); 
	DuLinkList q;
	q = D->next;
	while(strcmp(q->data.ShopName,ShopName) != 0)
		q = q->next;
	q->data.goods[0].Sales++;
	sort(D,2);
}
int main()
{
	LinkList Shop;
	DuLinkList Goods;
	int choice;
	DisplayMenu();
	cin>>choice;
	while(choice != 6)
	{
		switch(choice)
		{
			case 1:Shop = ReadData();cout<<"��ȡ������Ϣ���!"<<endl;system("pause");system("cls");DisplayMenu();cin>>choice;break;
			case 2:
			{
				cout<<"(1)��������\t\t(2)ɾ������\n(3)������������Ʒ\t(4)ɾ����������Ʒ\n����ѡ��";
				cin>>choice;
				switch(choice)
				{
				case 1:AddShop(Shop);cout<<"�������̳ɹ�!"<<endl;fflush(stdin);break;
				case 2:DeleteShop(Shop);cout<<"ɾ�����̳ɹ�!"<<endl;fflush(stdin);break;
				case 3:AddItems(Shop);cout<<"������������Ʒ�ɹ�!"<<endl;fflush(stdin);break; 
				case 4:DeleteItems(Shop);cout<<"ɾ����������Ʒ�ɹ�!"<<endl;fflush(stdin);break; 
				default:cout<<"��������!\n";break;	
				}
				system("pause");
				system("cls");
				DisplayMenu();
				cin>>choice;
				break;
			}
			case 3:ChangePrice(Shop);cout<<"�޸���Ʒ�۸����!"<<endl;system("pause");system("cls");DisplayMenu();cin>>choice;break;
			case 4:
			{	
				Goods = SearchItems(Shop);
				char c;
				cout<<"�Ƿ������Ʒ��(y or n)";
				cin>>c; 
				if(c == 'y')
					BuyItmes(Shop,Goods);
				system("pause");
				system("cls");
				DisplayMenu();
				cin>>choice;
				break;
			}
			case 5:Goods = NULL;BuyItmes(Shop,Goods);cout<<"����ɹ�!"<<endl;system("pause");system("cls");DisplayMenu();cin>>choice;break;
		}
	}
	return 0;
}
