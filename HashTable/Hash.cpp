#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <stdlib.h>       
#include <string.h>
using namespace std;
#define HASH_LEN 100 
#define MAXASL 2  	//���ƽ������        
typedef int Status;
typedef struct{
    string ID;    
    string name;
	string address; 
}Data;
Data DataTable[HASH_LEN];  
typedef struct HashNode{
	Data info;
	int si;   	//���Ҵ��� 
	struct HashNode *next;
}HashNode;
typedef struct{
	HashNode * first;
	int num;
}HashHead;
HashHead HashTable[HASH_LEN];
int p[10];		//ģ��ʱ�����ı��� 
int index = 0;      //����һ��p 
istream& operator>>(istream& in, Data& s){
    in>>s.ID>>s.name>>s.address;
    return in;
}
ostream& operator<<(ostream& out, const Data& s){
    out<<s.ID<<" "<<s.name<<" "<<s.address<<" "; 
    return out;
}
int TableLength(Data *a){
	int num = 0;
	int i = 0;
	while(1)
	{
		if(a[i].ID.length() != 0)
		{
			num++;
			i++;
		}
		else
			break;
	}
	return num;
}
bool prime(int x){
     int y;
     for(y=2;y<=sqrt(x);y++)
         if (x%y==0)
            return false;
     return true;
}
int ArrayLength(int *a){
	int num = 0;
	int i = 0;
	while(a[i] != 0)
	{
		num++;
		i++;
	}
	return num;	
}
void InitDataTable(){
	fstream fp;
	int i = 0;
	fp.open("data.txt",ios::in);
	if(fp.fail())
	{
		cout<<"���ļ�ʧ��ʧ�ܣ�";
		return;
	}
	while(!fp.eof())
	{	
		fp>>DataTable[i];
		i++; 
	}
	fp.close();
 } 
int Hash(string s){
	int sum = 0,i = 0,j;
	for(j = 0; j < s.size(); j = j+3)
	{
		sum += atoi(s.substr(j,3).c_str());
		i++;
	}
	return sum%p[index];
}
void CreateHashTable(){
	int i,j; 
	int sum,address;
	double ASL; 
	int Len = TableLength(DataTable);	//���ݳ��� 
	for(i = 0; i < HASH_LEN; i++)
	{
		HashTable[i].first = NULL;		//��ʼ������������
		HashTable[i].num = 0;
	}
	for(i = 0; i < Len; i++) 
	{
		address = Hash(DataTable[i].ID);
		HashNode *p = new(HashNode); 
		p->info.address = DataTable[i].address;
		p->info.ID = DataTable[i].ID;
		p->info.name = DataTable[i].name;
		p->next = HashTable[address].first;
		p->si = 1;
		HashTable[address].first = p;
		HashTable[address].num++;
	}
	sum = 0;
	for(i = 0; i < HASH_LEN; i++)		//��ASL 
	{
		for(j = 1; j <= HashTable[i].num; j++)
			sum += j;
	}
	ASL = 1.0*sum/Len;
	if(ASL > MAXASL)		//�������ƽ�����Ҳ��������½��� 
	{
		index++;
		CreateHashTable(); 
		cout<<index ;
	}
	else
		cout<<"��ϣ�������!    ASL:"<<ASL<<endl;
}
void Search(){
	string find;
	int address,i;
	HashNode *p;
	cout<<"������Ҫ��ѯ�����֤����:"; 
	cin>>find; 
	address = Hash(find);
	p = HashTable[address].first;
	if(p == NULL)
		cout<<"��ѯ����������!";
	else
	{
		i = 1;
		while(p != NULL)
		{
			if(find == p->info.ID)
			{
				cout<<p->info;
				cout<<"���Ҵ�����"<<i;
				break;
			}
			i++;
			p = p->next;
		}
		if(p == NULL)
			cout<<"��ѯ����������!";
	}
} 
int main()
{
	InitDataTable();
	int i,j = 0;
	for(i = HASH_LEN; i > 0; i--)	 //��p 
	{
		if(prime(i))
		{
			p[j] = i;
			j++;
		}
		if(j == 10)					//ֻҪ10�� 
			break;
	}
	CreateHashTable(); 
	Search();
	return 0;	
}
