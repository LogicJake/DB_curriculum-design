#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define goodsNumber 6	//��Ʒ��������� 
#define ShopNumber 16
using namespace std;
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
	fp.open("Shops.txt",ios::in);
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
void AddShop(LinkList &L)
{
	fstream fp;
	LinkList p,q;
	int i,num;
	fp.open("Shops.txt",ios::out|ios::app);
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
	fp.open("Shops.txt",ios::out);
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
int main()
{
	LinkList Shop;
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
				cout<<"(1)��������\t\t(2)ɾ������\n����ѡ��";
				cin>>choice;
				switch(choice)
				{
				case 1:AddShop(Shop);fflush(stdin);break;
				case 2:DeleteShop(Shop);fflush(stdin);break;
				default:cout<<"��������!\n";break;	
				}
				system("pause");
				system("cls");
				DisplayMenu();
				cin>>choice;
				break;
			}
		}
	}
	return 0;
}
