#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
# define INFEASIBLE -1
# define OVERFLOW -2
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int ElemType;
typedef int Status;
typedef struct Node
{
	ElemType data;
	struct Node *next;
}StackNode;
typedef struct Node *Stack; 
Status InitStack(Stack &top)
{
	top = (Stack)malloc(sizeof(StackNode));
	if (top == NULL)
		exit(OVERFLOW);
	else
	{
		top->next = NULL;
		return OK;
	}
}
Status StackEmpty(Stack top)
{
	if (!top)
		return INFEASIBLE;
	else if (top->next == NULL)
		return TRUE;
	else
		return FALSE;
}
Status GetTop(Stack top, ElemType &e)
{
	if (!top)
		return INFEASIBLE;
	else 
	{
		if(top->next != NULL)
		{
			e = top->next->data;
			return OK;
		}
		else
			return ERROR;
	}
}
Status Push(Stack &top, ElemType e)
{
	if (!top)
		return INFEASIBLE;
	else
	{
		Stack p = (Stack)malloc(sizeof(StackNode));
		p->data = e;
		p->next = top->next;
		top->next = p;
		return OK;
	}
}
Status Pop(Stack &top, ElemType &e)
{
	Stack p;
	if (!top||!top->next)
		return INFEASIBLE;
	else
	{
		p = top->next;
		top->next = p->next;
		e = p->data;
		free(p);
		return OK;
	}
}
Status StackTraverse(Stack top, int flag)
{
	Stack p = top->next; 
	while(p)
	{
		if(flag == 1)
			printf("%d ",p->data);
		else
			printf("%c ",p->data);
		p = p->next;
	}
}
Status IsOperator(char c)
{
	if(c == '#'||c == '('||c == '+'||c == '-'||c == '*'||c == '/'||c == ')')
		return TRUE;
	else
		return FALSE; 
}
Status IsOperator2(char c)
{
	if(c == '+'||c == '-'||c == '*'||c == '/')
		return TRUE;
	else
		return FALSE; 
}
Status Prior(char c1,char c2)
{
	char ch[] = "#(+-*/)";
	int i = 0,j = 0;
	while(ch[i] && ch[i] != c1) i++;
	if(i == 3) i--;	
	if(i == 5) i--;	
	while(ch[j] && ch[j] != c2) j++;
	if(j == 3) j--;
	if(j == 5) j--;
	if(i >= j) 
		return TRUE;
	else 
		return FALSE;
}
void PlayStack(Stack s1, Stack s2)
{
	cout<<"*******************\n";
	cout<<"* s1:";
	StackTraverse(s1,1);
	if(s2 == NULL)
		return;
	cout<<"\n* s2:";
	StackTraverse(s2,2);
	cout<<"\n";
	cout<<"*******************\n";
	system("pause");
}
void Operate(Stack &s1, Stack s2, ElemType e)
{
	if(e == '#')
		return;
	int e1,e2;
	Pop(s1,e1);
	PlayStack(s1,s2);
	Pop(s1,e2);
	PlayStack(s1,s2);
	int x;
	switch(e)
	{
		case '+':Push(s1,e1+e2);PlayStack(s1,s2);break;
		case '-':Push(s1,e2-e1);PlayStack(s1,s2);break;
		case '*':Push(s1,e1*e2);PlayStack(s1,s2);break;
		case '/':Push(s1,e2/e1);PlayStack(s1,s2);break;
	}
}
void EvaluateExpression(char buff[])
{
	Stack s1,s2;	//s1运算数栈，s2运算符栈
	InitStack(s1);
	InitStack(s2);
	PlayStack(s1,s2);
	int value = 0;
	int flag = 0;
	int i = 0;
	Push(s2,buff[i]);
	PlayStack(s1,s2);
	i++;
	ElemType e;
	while(buff[i] != '#')
	{
		if (!IsOperator(buff[i]))
		{	
			value = value * 10 + buff[i] - '0';
			flag = 1;
		}
		else
		{
			if(flag == 1)
			{
				Push(s1,value);
				PlayStack(s1,s2);
				flag = 0;
				value = 0;
			}
			if (buff[i] == '(' || StackEmpty(s2))
			{
				Push(s2,buff[i]);
				PlayStack(s1,s2);
			}
			else
			{
				if (buff[i] == ')')
				{
					Pop(s2,e);
					PlayStack(s1,s2);
					while(e != '(')
					{
						Operate(s1,s2,e);
						Pop(s2,e);
						PlayStack(s1,s2);
					}
				}
				else
				{
					GetTop(s2,e);
					while(Prior(e,buff[i]))
					{
						Pop(s2,e);
						PlayStack(s1,s2);
						Operate(s1,s2,e);
						GetTop(s2,e);
						if(StackEmpty(s2))
							break;
					}
					Push(s2,buff[i]);
					PlayStack(s1,s2);
				}
			}
		}
		i++;
	}
	if (flag)
	{
		Push(s1,value);
		PlayStack(s1,s2);
	}
    while (!StackEmpty(s2))
    {
        Pop(s2,e);
        PlayStack(s1,s2);
        Operate(s1,s2,e);
        GetTop(s1,value); 
    }
    GetTop(s1,value); 
	cout<<"\n"<<buff<<"="<<value<<endl;
}
Status Exame(char * buff)			//判断表达式是否有误 
{
	int i;
	ElemType e;
	Stack s;
	InitStack(s);
	int length = strlen(buff); 
	if(IsOperator2(buff[length-2]))//末位不能为运算符 
	{
		cout<<"错误：末位不能为运算符！";
		return FALSE;  
	}
	if(IsOperator(buff[1]))			//第一位不能为运算符 
	{
		cout<<"错误：首位不能为运算符！";
		return FALSE;  
	} 
	for(i = 1; i < length; i++)
	{
		if(buff[i] == '/' && buff[i+1] == '0')
		{
			cout<<"错误：除数不能为0！";
			return FALSE; 	
		}
		if(IsOperator(buff[i]) && IsOperator(buff[i+1]))
		{
			cout<<"错误：运算符不能相连！";
			return FALSE; 	
		}
		if(buff[i] == '(')
			Push(s,buff[i]);
		if(buff[i] == ')')
		{
			if(StackEmpty(s))
			{
				cout<<"错误：括号不匹配！";
				return FALSE;
			}
			else
				Pop(s,e);
		}
	} 
	if(!StackEmpty(s))
	{
		cout<<"错误：括号不匹配！"; 
		return FALSE;
	 } 
	return TRUE;
}
int main()
{
//	char buff[] = "#9+(3-1)*3+10/2#";
	char buff[255];
	int choice = 2; 
	cout<<"\t1.从键盘读取\t2.从文件读取"<<endl;
	cout<<"请输入选择:";
	cin>>choice;
	if(choice == 1)
		gets(buff);
	else if (choice == 2)
	{
		fstream fp;
		fp.open("test.txt",ios::in);
		fp.getline(buff,255);
	}
	if(Exame(buff))
	{
		system("cls");
		cout<<"\ts1为运算数栈，s2为运算符栈，内容显示如下：\n\n";
		EvaluateExpression(buff);
	}
}
