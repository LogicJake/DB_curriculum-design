#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define goodsNumber 6	//商品的最大数量 
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
	int ItemsNumber;		//商店所有商品的种类数量 
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
	fp.open(FileName,ios::in);
	if(fp.fail())
	{
		cout<<"打开失败！";
		return ERROR;
	}
	LinkList L,p,q;
	L = (LinkList)malloc(sizeof(Node)); /* 产生头结点,并使L指向此头结点 */
    if(L == NULL) /* 存储分配失败 */
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
	fp.open(FileName,ios::out|ios::app);
	if(fp.fail())
	{
		cout<<"打开失败！";
		exit(0);	
	}
	q = L->next;
	while(q->next)
		q = q->next;	//循环到链表表尾 
	cout<<"请输入增加的商铺信息\n";
	i = GetLength(L);
	i++;
	p = (LinkList)malloc(sizeof(Node));
	p->data.number = i;
	cout<<"商铺名：";
	cin>>p->data.ShopName;
	cout<<"信誉度：";
	cin>>p->data.CreditWorthiness;
	cout<<"请输入商品个数：";
	cin>>p->data.ItemsNumber;
	for(i = 0; i < p->data.ItemsNumber; i++) 
	{
		cout<<"商品名称：";
		cin>>p->data.goods[i].ItemsName; 
		cout<<"商品价格：";
		cin>>p->data.goods[i].price;
		cout<<"商品销量："; 
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
		cout<<"打开失败！";
		exit(0);	
	}
	cout<<"请输入你要删除商铺的编号:";
	cin>>choice;
	while(p->next->data.number != choice)
		p = p->next; 	//p指向要删除结点的前一个
	p->next = p->next->next;
	p = p->next;
	while(p)
	{
		p->data.number--;
		p = p->next;
	}
	p = L->next;
	while(p->next)		//存储文件 
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
	cout<<"请输入商铺的编号：";
	cin>>Object;
	p = L->next;
	while(p->data.number != Object)
		p = p->next;
	cout<<"\n编号："<<p->data.number<<"\t"<<"店名："<<p->data.ShopName<<endl;
	cout<<"拥有商品：";
	for(i = 0; i < p->data.ItemsNumber; i++)
		cout<<p->data.goods[i].ItemsName<<"  "; 
	p->data.ItemsNumber++;
	cout<<endl<<"请输入要增加的商品名和价格"<<endl;
	cout<<"商品名：";
	cin>>p->data.goods[p->data.ItemsNumber-1].ItemsName;
	cout<<"价格：";
	cin>>p->data.goods[p->data.ItemsNumber-1].price;
	p->data.goods[p->data.ItemsNumber-1].Sales = 0;
	fp.open(FileName,ios::out);
	if(fp.fail())
	{
		cout<<"打开失败！";
		exit(0);	
	}
	p = L->next;
	while(p->next)		//存储文件 
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
	cout<<"请输入商铺的编号：";
	cin>>Object;
	p = L->next;
	while(p->data.number != Object)
		p = p->next;
	cout<<"\n编号："<<p->data.number<<"\t"<<"店名："<<p->data.ShopName<<endl;
	cout<<"拥有商品：";
	for(i = 0; i < p->data.ItemsNumber; i++)
		cout<<p->data.goods[i].ItemsName<<"  ";
	cout<<endl<<"请输入要删除的商品名：";
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
		cout<<"打开失败！";
		exit(0);	
	}
	p = L->next;
	while(p->next)		//存储文件 
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
			case 1:Shop = ReadData();cout<<"读取商铺信息完毕!"<<endl;system("pause");system("cls");DisplayMenu();cin>>choice;break;
			case 2:
			{
				cout<<"(1)增加商铺\t\t(2)删除商铺\n(3)增加商铺中商品\t(4)删除商铺中商品\n输入选择：";
				cin>>choice;
				switch(choice)
				{
				case 1:AddShop(Shop);fflush(stdin);break;
				case 2:DeleteShop(Shop);fflush(stdin);break;
				case 3:AddItems(Shop);fflush(stdin);break; 
				case 4:DeleteItems(Shop);fflush(stdin);break; 
				default:cout<<"输入有误!\n";break;	
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
