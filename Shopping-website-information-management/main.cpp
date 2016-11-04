#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
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
	int goods[6];		//商品编码
}Shop;
typedef Shop ElemType;
istream& operator>>(istream& in, Items& s)
{
    in>>s.ItemsName>>s.price>>s.Sales;
    return in;
}
ostream& operator<<(ostream& out, const Items& s)
{
    out<<s.ItemsName<<" "<<s.price<<" "<<s.Sales<<endl; 
    return out;
}
istream& operator>>(istream& in, Shop& s)
{
    in>>s.number>>s.ShopName>>s.CreditWorthiness>>s.goods[0]>>s.goods[1]>>s.goods[2]>>s.goods[3]>>s.goods[4]>>s.goods[5];
    return in;
}
ostream& operator<<(ostream& out, const Shop& s)
{
    out<<s.number<<" "<<s.ShopName<<" "<<s.CreditWorthiness<<" "<<s.goods; 
    return out;
}
typedef int Status;
typedef struct Node
{
    ElemType data;
    struct Node *next;
}Node;
typedef struct Node *LinkList; 
Status ReadData()
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
	p=L->next;  
    while(p)  
    {  
        cout<<p->data; 
        p=p->next; 
    }  
}
int main()
{
	ReadData(); 
	return 0;
}
