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
	output<<"姓名："<<p->name<<"\t出生日期："<<p->bday.year<<"年"<<p->bday.month<<"月"<<p->bday.day<<"日\t"<<"\t地址："<<p->address;
	if(p->married)
		output<<"\t已婚";
	else
		output<<"\t未婚";
	if(!p->alive)
		output<<"\t死亡日期："<<p->dday.year<<"年"<<p->dday.month<<"月"<<p->dday.day<<"日"; 
	else
		output<<"\t健在"; 
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
				cout<<"‖";
			else 
				cout<<" ";
		}
		if(t >= 5)
			cout<<"╠═";
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
	cout<<"请输入你要查看的代数：";
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
		cout<<"无这代人的信息！\n";
}
void printinformation(family f)
{
	string name;
	person *p,*q;
	cout<<"请输入你要查找的姓名：";
	cin>>name;
	p = search(f,name);
	if(p == NULL)
	{
		cout<<"查无此人！"<<endl;
		return;
	}
	cout<<"本人信息："<<endl;
	cout<<p;
	if(p->father)
	{
		cout<<"父亲信息："<<endl;
		cout<<p->father;
	}
	q = p->firstchild;
	if(q)
	{
		cout<<"孩子信息："<<endl;
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
	cout<<"请输入你要查询的出生日期(以空格隔开年月日)：";
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
		cout<<"没有在此日期出生的人！\n";
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
	cout<<"请输入父亲姓名：";
	cin>>father;
	person *child,*r;
	child = new(person);
	child->father = search(f,father);
	if(child->father == NULL)
	{
		cout<<"查无此人！";
		return; 
	}
	cout<<"请输入孩子信息"<<endl;
	cout<<"姓名：";
	cin>>child->name;
	cout<<"出生日期(以空格隔开年月日)：";
	cin>>child->bday.year>>child->bday.month>>child->bday.day;
	cout<<"地址：";
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
		if(p->firstchild) 	// p有长子
       		deleteson(f,p->firstchild); // 销毁p的长子为根结点的子树
    	if(p->nextsibling) 	// p有下一个兄弟
      		deleteson(f,p->nextsibling); // 销毁p的下一个兄弟为根结点的子树
     	delete(p); 			// 释放根结点
	}
}
void deleteperson(family &f, person *p)
{
	if(p)
	{
		if(p->firstchild) 	// p有长子
       		deleteson(f,p->firstchild); // 销毁p的长子为根结点的子树
     	delete(p); 			// 释放根结点
	}
}
void Delete(family &f)
{
	string name;
	cout<<"请输入你要删除的成员姓名：";
	cin>>name;
	person *p = search(f,name);
	if(p == NULL)
	{
		cout<<"查无此人！";
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
	cout<<"请输入你要修改的成员姓名：";
	cin>>name;
	person *p = search(f,name);
	if(p == NULL)
	{
		cout<<"查无此人！";
		return;
	}
	cout<<"请确认成员信息"<<endl; 
	cout<<p;
	cout<<"请输入修改后信息"<<endl;
	cout<<"姓名：";
	cin>>p->name;
	cout<<"出生日期(以空格隔开年月日)：";
	cin>>p->bday.year>>p->bday.month>>p->bday.day;
	cout<<"是否结婚：";
	cin>>p->married;
	cout<<"地址："; 
	cin>>p->address;
	cout<<"是否健在：";
	cin>>p->alive;
	if(!p->alive)
	{
		cout<<"去世日期(以空格隔开年月日)：";
		cin>>p->dday.year>>p->dday.month>>p->dday.day; 
	 } 
	cout<<"代数：";
	cin>>p->generation;
	cout<<"父亲姓名：";
	cin>>p->fathername;
	saveTofile(f);
}
bool Sort( const Temp &t1, const Temp &t2) 
{  
    return t1.num < t2.num;//升序排列  
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
        cout<<"姓名："<<(iter->p)->name<<"     "<<(iter->p)->bday.year<<"年"<<(iter->p)->bday.month<<"月"<<(iter->p)->bday.day<<"日"<<endl;
}
void checkbirthday(family f)
{
	time_t tt = time(NULL);//这句返回的只是一个时间cuo
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
			cout<<"特别提醒：今天是"<<p->name<<"的生日！"<<endl; 
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
	cout<<"请输入第一个人的名字：";
	cin>>nameA;
	A = search(f,nameA);
	if(A == NULL)
	{
		cout<<"查无此人！" ;
		return;
	}
	cout<<"请输入第二个人的名字：";
	cin>>nameB;
	B = search(f,nameB);
	if(B == NULL)
	{
		cout<<"查无此人！" ;
		return;
	}
	if(A->generation > B->generation)
		cout<<A->name<<"是"<<B->name<<"的长辈！\n";
	if(A->generation < B->generation)
		cout<<B->name<<"是"<<A->name<<"的长辈！\n";
	if(A->generation == B->generation)
		cout<<B->name<<"和"<<A->name<<"平辈！\n";
}

void displaymenu()
{
	cout<<"\t\t\t\t家谱管理系统\n\n";
	cout<<"1>显示家谱\t2>显示第n代人\t3>按姓名查询\t4>按出生日期查询\t5>确定两人关系\n6>添加孩子\t7>删除成员\t8>修改成员\t9>按出生日期排序\t10>退出\n"; 
	cout<<"请输入您的选择："; 
}
int main()
{
	int choice; 
	system("title 家谱管理系统");
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
			default:cout<<"输入有误!\n";system("pause");system("cls");displaymenu();fflush(stdin);cin>>choice;break;
		}
	}
 } 
