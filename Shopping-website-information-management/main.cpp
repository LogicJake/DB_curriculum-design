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
	cout<<"\t\t购物网站信息管理\n\n";
	cout<<"<1>读取商铺信息\t\t<2>对商铺进行操作\t<3>修改商品价格\n";
	cout<<"<4>查询商品\t\t<5>购买商品\t\t<6>退出"<<endl; 
	cout<<"输入选择：";
}
int GetLength(LinkList L)	//求链表的长度 
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
		cout<<"打开失败！";
		return ERROR;
	}
	LinkList L,p,q;
	L=(LinkList)malloc(sizeof(Node)); /* 产生头结点,并使L指向此头结点 */
    if(L==NULL) /* 存储分配失败 */
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
		q = q->next;	//循环到链表
	int i,num;
	cout<<"请输入增加的商铺信息\n";
	i = GetLength(L);
	i++;
	p->data.number = i;
	cout<<"商铺名：";
	cin>>p->data.ShopName;
	cout<<"信誉度：";
	cin>>p->data.CreditWorthiness;
	cout<<"请输入商品个数：";
	cin>>num;
	for(i = 0; i < num; i++) 
	{
		cout<<"商品名称：";
		cin>>p->data.goods[i].ItemsName; 
		cout<<"商品价格：";
		cin>>p->data.goods[i].price;
		cout<<"商品销量："; 
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
			case 1:Shop = ReadData();cout<<"读取商铺信息完毕!"<<endl;system("pause");system("cls");DisplayMenu();cin>>choice;break;
			case 2:
			
			{
				cout<<"(1)增加商铺\t\t(2)删除商铺\n输入选择：";
				cin>>choice;
				if(choice == 1)
					AddShop(Shop);
				if(choice == 2)
					DeleteShop(Shop);
				else
					cout<<"输入有误!\n";
				system("pause");
				system("cls");
				DisplayMenu();cin>>choice;
				break;
			}
		}
	}
	return 0;
}
