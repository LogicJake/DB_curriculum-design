#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define goodsNumber 6
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
	Items goods[6];
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
    in>>s.number>>s.ShopName>>s.CreditWorthiness;
    for (int i = 0; i < goodsNumber; ++i)
    	in>>s.goods[i];
	return in;
}
ostream& operator<<(ostream& out, const Shop& s)
{
    out<<s.number<<" "<<s.ShopName<<" "<<s.CreditWorthiness<<" "; 
    for (int i = 0; i < goodsNumber; ++i)
    	out<<s.goods[i];
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
	L=(LinkList)malloc(sizeof(Node)); /* ����ͷ���,��ʹLָ���ͷ��� */
    if(L==NULL) /* �洢����ʧ�� */
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
//	p=L->next;  
//   	while(p)  
//   	{  
//       cout<<p->data<<endl; 
//       p=p->next; 
//  	}  
  	return L;
}
void AddShop(LinkList &L)
{
	LinkList p,q;
	p = (LinkList)malloc(sizeof(Node));
	q = L->next;
	while(q->next)
		q = q->next;	//ѭ��������
	int i,num;
	cout<<"���������ӵ�������Ϣ\n";
	i = GetLength(L);
	i++;
	p->data.number = i;
	cout<<"��������";
	cin>>p->data.ShopName;
	cout<<"�����ȣ�";
	cin>>p->data.CreditWorthiness;
	cout<<"��������Ʒ������";
	cin>>num;
	for(i = 0; i < num; i++) 
	{
		cout<<"��Ʒ���ƣ�";
		cin>>p->data.goods[i].ItemsName; 
		cout<<"��Ʒ�۸�";
		cin>>p->data.goods[i].price;
		cout<<"��Ʒ������"; 
		cin>>p->data.goods[i].Sales;
	}
	q->next = p;
	p->next = NULL;
}
void DeleteShop(LinkList &L)
{
	
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
				if(choice == 1)
					AddShop(Shop);
				if(choice == 2)
					DeleteShop(Shop);
				else
					cout<<"��������!\n";
				system("pause");
				system("cls");
				DisplayMenu();cin>>choice;
				break;
			}
		}
	}
	return 0;
}
