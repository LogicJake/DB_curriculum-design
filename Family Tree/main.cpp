#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;
typedef struct
{
	int year;
	int month;
	int day;
}Day; 
typedef struct person
{
	string name;
	Day bday;
	int married;
	string address;
	int alive;  
	Day dday;
	int generation;
	string fathername;
	struct person *firstchild, *nextsibling, *father;
}person,*family;
typedef struct
{
	person *p;
	int num;
}Temp;
istream& operator >> (istream& input, family &p)
{
	input>>p->name>>p->bday.year>>p->bday.month>>p->bday.day>>p->married>>p->address>>p->alive;
	if(!p->alive)
		input>>p->dday.year>>p->dday.month>>p->dday.day; 
	input>>p->generation>>p->fathername;
	return input;
}
ostream& operator << (ostream& output, family &p)
{
	output<<"������"<<p->name<<"\t�������ڣ�"<<p->bday.year<<"��"<<p->bday.month<<"��"<<p->bday.day<<"��\t"<<"\t��ַ��"<<p->address;
	if(p->married)
		output<<"\t�ѻ�";
	else
		output<<"\tδ��";
	if(!p->alive)
		output<<"\t�������ڣ�"<<p->dday.year<<"��"<<p->dday.month<<"��"<<p->dday.day<<"��"; 
	else
		output<<"\t����"; 
	output<<endl;
	return output;
}
person* search(family &f,string name)
{
	person *p = f, *q;
	if(!f)
		return NULL;
	queue<person*> Q;
	Q.push(p);
	q = p->nextsibling;
	while(q)
	{
		Q.push(q);
		q = q->nextsibling;	
	}	
	while(!Q.empty())
	{
		p = Q.front();
		Q.pop();
		if(p->name == name)
			return p;
		q = p->firstchild;
		while(q)
		{
			Q.push(q);
			q = q->nextsibling;	
		}
	}
}
void Print(family &T,int t)
{
	int i;
	if(T)
	{
		for(i = 0; i < t-5; i++){
			if(i%5==0)
				cout<<"��";
			else 
				cout<<" ";
		}
		if(t >= 5)
			cout<<"�d�T";
        cout<<T->name<<endl;
    	Print(T->firstchild,t+5);
		Print(T->nextsibling,t);
	}
}
void InitFamilyTree(family &f)
{
	fstream fp;
	fp.open("FamilyTree.txt",ios::in);
	f = new(person);
	fp>>f;
	f->father = NULL;
	f->firstchild = NULL;
	f->nextsibling = NULL;
	person *p,*q,*r;
	while(!fp.eof())
	{
		p = new(person); 
		fp>>p;
		p->father = NULL;
		p->firstchild = NULL;
		p->nextsibling = NULL;
		if(p->fathername != "NULL")
		{
			q = search(f,p->fathername);
			p->father = q;
			r = q->firstchild;
			if(r == NULL)
				q->firstchild = p;
			else
			{
				while(r->nextsibling)
					r = r->nextsibling;
				r->nextsibling = p;
			}
		}
	}
	fp.close();
}
void printgenerationperson(family f)
{
	int i;
	int find = 0;
	cout<<"��������Ҫ�鿴�Ĵ�����";
	cin>>i;
	person *p = f, *q;
	queue<person*> Q;
	Q.push(p);
	q = p->nextsibling;
	while(q)
	{
		Q.push(q);
		q = q->nextsibling;	
	}	
	while(!Q.empty())
	{
		p = Q.front();
		Q.pop();
		if(p->generation == i)
		{
			find = 1;
			cout<<p;
		}
		q = p->firstchild;
		while(q)
		{
			Q.push(q);
			q = q->nextsibling;	
		}
	}
	if(find == 0)
		cout<<"������˵���Ϣ��\n";
}
void printinformation(family f)
{
	string name;
	person *p,*q;
	cout<<"��������Ҫ���ҵ�������";
	cin>>name;
	p = search(f,name);
	if(p == NULL)
	{
		cout<<"���޴��ˣ�"<<endl;
		return;
	}
	cout<<"������Ϣ��"<<endl;
	cout<<p;
	if(p->father)
	{
		cout<<"������Ϣ��"<<endl;
		cout<<p->father;
	}
	q = p->firstchild;
	if(q)
	{
		cout<<"������Ϣ��"<<endl;
		while(q)
		{
			cout<<q;
			q = q->nextsibling;
		}
	}
 } 
void searchAtbirthday(family f)
{
	Day day;
	int find = 0;
	cout<<"��������Ҫ��ѯ�ĳ�������(�Կո����������)��";
	cin>>day.year>>day.month>>day.day;
	person *p = f, *q;
	queue<person*> Q;
	Q.push(p);
	q = p->nextsibling;
	while(q)
	{
		Q.push(q);
		q = q->nextsibling;	
	}	
	while(!Q.empty())
	{
		p = Q.front();
		Q.pop();
		if(p->bday.year == day.year&&p->bday.month == day.month&&p->bday.day == day.day)
		{
			find = 1;
			cout<<p;
		}
		q = p->firstchild;
		while(q)
		{
			Q.push(q);
			q = q->nextsibling;	
		}
	}
	if(find == 0)
		cout<<"û���ڴ����ڳ������ˣ�\n";
}
void saveTofile(family f)
{
	fstream fp;
	fp.open("FamilyTree.txt",ios::out);
	person *p = f, *q;
	queue<person*> Q;
	Q.push(p);
	q = p->nextsibling;
	while(q)
	{
		Q.push(q);
		q = q->nextsibling;	
	}	
	while(!Q.empty())
	{
		p = Q.front();
		Q.pop();
		fp<<p->name<<" "<<p->bday.year<<" "<<p->bday.month<<" "<<p->bday.day<<" "<<p->married<<" "<<p->address<<" "<<p->alive;
		if(!p->alive)
			fp<<" "<<p->dday.year<<" "<<p->dday.month<<" "<<p->dday.day;
		fp<<" "<<p->generation<<" "<<p->fathername<<endl;
		q = p->firstchild;
		while(q)
		{
			Q.push(q);
			q = q->nextsibling;	
		}
	}
	fp.close();
}
void addchild(family &f)
{
	
	string father;
	cout<<"�����븸��������";
	cin>>father;
	person *child,*r;
	child = new(person);
	child->father = search(f,father);
	if(child->father == NULL)
	{
		cout<<"���޴��ˣ�";
		return; 
	}
	cout<<"�����뺢����Ϣ"<<endl;
	cout<<"������";
	cin>>child->name;
	cout<<"��������(�Կո����������)��";
	cin>>child->bday.year>>child->bday.month>>child->bday.day;
	cout<<"��ַ��";
	cin>>child->address;
	child->alive = 1;
	child->fathername = father;
	child->generation = child->father->generation+1;
	child->firstchild = NULL;
	child->nextsibling = NULL;
	child->married = 0;
	r = child->father->firstchild;
	if(r == NULL)
		child->father->firstchild = child;
	else
	{
		while(r->nextsibling)
			r = r->nextsibling;
		r->nextsibling = child;
	}
	saveTofile(f);
}
void deleteson(family &f, person *p)
{
	if(p)
	{
		if(p->firstchild) 	// p�г���
       		deleteson(f,p->firstchild); // ����p�ĳ���Ϊ����������
    	if(p->nextsibling) 	// p����һ���ֵ�
      		deleteson(f,p->nextsibling); // ����p����һ���ֵ�Ϊ����������
     	delete(p); 			// �ͷŸ����
	}
}
void deleteperson(family &f, person *p)
{
	if(p)
	{
		if(p->firstchild) 	// p�г���
       		deleteson(f,p->firstchild); // ����p�ĳ���Ϊ����������
     	delete(p); 			// �ͷŸ����
	}
}
void Delete(family &f)
{
	string name;
	cout<<"��������Ҫɾ���ĳ�Ա������";
	cin>>name;
	person *p = search(f,name);
	if(p == NULL)
	{
		cout<<"���޴��ˣ�";
		return;
	}
	person *father = p->father;
	person *son = father->firstchild;
	if(son->name == name)
		father->firstchild = NULL;
	else
	{
		while(son->nextsibling->name != name)
			son = son->nextsibling;
		son->nextsibling = NULL;
	}
	deleteperson(f,p);
	saveTofile(f);
}
void modify(family &f)
{
	string name;
	cout<<"��������Ҫ�޸ĵĳ�Ա������";
	cin>>name;
	person *p = search(f,name);
	if(p == NULL)
	{
		cout<<"���޴��ˣ�";
		return;
	}
	cout<<"��ȷ�ϳ�Ա��Ϣ"<<endl; 
	cout<<p;
	cout<<"�������޸ĺ���Ϣ"<<endl;
	cout<<"������";
	cin>>p->name;
	cout<<"��������(�Կո����������)��";
	cin>>p->bday.year>>p->bday.month>>p->bday.day;
	cout<<"�Ƿ��飺";
	cin>>p->married;
	cout<<"��ַ��"; 
	cin>>p->address;
	cout<<"�Ƿ��ڣ�";
	cin>>p->alive;
	if(!p->alive)
	{
		cout<<"ȥ������(�Կո����������)��";
		cin>>p->dday.year>>p->dday.month>>p->dday.day; 
	 } 
	cout<<"������";
	cin>>p->generation;
	cout<<"����������";
	cin>>p->fathername;
	saveTofile(f);
}
bool Sort( const Temp &t1, const Temp &t2) 
{  
    return t1.num < t2.num;//��������  
} 
void SortbyBirthday(family &f)
{
	vector<Temp> t;
	Temp temp;
	person *p = f, *q;
	queue<person*> Q;
	Q.push(p);
	q = p->nextsibling;
	while(q)
	{
		Q.push(q);
		q = q->nextsibling;	
	}	
	while(!Q.empty())
	{
		p = Q.front();
		Q.pop();
		temp.p = p;
		temp.num = p->bday.year*10000+p->bday.month*100+p->bday.day;
		t.push_back(temp);
		q = p->firstchild;
		while(q)
		{
			Q.push(q);
			q = q->nextsibling;	
		}
	}
	sort(t.begin(),t.end(),Sort);  
	vector<Temp>::iterator iter;  
	for (iter = t.begin();iter != t.end(); iter++)  
        cout<<"������"<<(iter->p)->name<<"     "<<(iter->p)->bday.year<<"��"<<(iter->p)->bday.month<<"��"<<(iter->p)->bday.day<<"��"<<endl;
}
void checkbirthday(family f)
{
	time_t tt = time(NULL);//��䷵�ص�ֻ��һ��ʱ��cuo
	tm* t= localtime(&tt);
	int month,day;
	month = t->tm_mon+1;
	day = t->tm_mday;
	person *p = f, *q;
	queue<person*> Q;
	Q.push(p);
	q = p->nextsibling;
	while(q)
	{
		Q.push(q);
		q = q->nextsibling;	
	}	
	while(!Q.empty())
	{
		p = Q.front();
		Q.pop();
		if(p->bday.month == month && p->bday.day == day && p->alive)
			cout<<"�ر����ѣ�������"<<p->name<<"�����գ�"<<endl; 
		q = p->firstchild;
		while(q)
		{
			Q.push(q);
			q = q->nextsibling;	
		}
	}
}
void checkrelationship(family f)
{
	person *A,*B;
	string nameA;
	string nameB;
	cout<<"�������һ���˵����֣�";
	cin>>nameA;
	A = search(f,nameA);
	if(A == NULL)
	{
		cout<<"���޴��ˣ�" ;
		return;
	}
	cout<<"������ڶ����˵����֣�";
	cin>>nameB;
	B = search(f,nameB);
	if(B == NULL)
	{
		cout<<"���޴��ˣ�" ;
		return;
	}
	if(A->generation > B->generation)
		cout<<A->name<<"��"<<B->name<<"�ĳ�����\n";
	if(A->generation < B->generation)
		cout<<B->name<<"��"<<A->name<<"�ĳ�����\n";
	if(A->generation == B->generation)
		cout<<B->name<<"��"<<A->name<<"ƽ����\n";
}

void displaymenu()
{
	cout<<"\t\t\t\t���׹���ϵͳ\n\n";
	cout<<"1>��ʾ����\t2>��ʾ��n����\t3>��������ѯ\t4>���������ڲ�ѯ\t5>ȷ�����˹�ϵ\n6>��Ӻ���\t7>ɾ����Ա\t8>�޸ĳ�Ա\t9>��������������\t10>�˳�\n"; 
	cout<<"����������ѡ��"; 
}
int main()
{
	int choice; 
	system("title ���׹���ϵͳ");
	system("mode con cols=94 lines=40");
	family f;
	InitFamilyTree(f);
	checkbirthday(f);
	displaymenu();
	cin>>choice;
	while(choice != 10)
	{
		switch(choice)
		{
			case 1:Print(f,0);system("pause");system("cls");displaymenu();fflush(stdin);cin>>choice;break;
			case 2:printgenerationperson(f);system("pause");system("cls");displaymenu();fflush(stdin);cin>>choice;break;
			case 3:printinformation(f);system("pause");system("cls");displaymenu();fflush(stdin);cin>>choice;break;
			case 4:searchAtbirthday(f);system("pause");system("cls");displaymenu();fflush(stdin);cin>>choice;break;
			case 5:checkrelationship(f);system("pause");system("cls");displaymenu();fflush(stdin);cin>>choice;break;
			case 6:addchild(f);system("pause");system("cls");displaymenu();fflush(stdin);cin>>choice;break;
			case 7:Delete(f);system("pause");system("cls");displaymenu();fflush(stdin);cin>>choice;break;
			case 8:modify(f);system("pause");system("cls");displaymenu();fflush(stdin);cin>>choice;break;
			case 9:SortbyBirthday(f);system("pause");system("cls");displaymenu();fflush(stdin);cin>>choice;break;
			default:cout<<"��������!\n";system("pause");system("cls");displaymenu();fflush(stdin);cin>>choice;break;
		}
	}
 } 
