#include <iostream>
#include <fstream> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int Status;
typedef struct
{
	char ch;
	int count;
	char *HuffCode;
}Character;
typedef Character SElemType;
typedef struct Node
{
	SElemType data;
	struct Node *next;
}StackNode;
typedef struct Node *LinkStack; 
Status InitCharacterList(LinkStack &top)
{	
	top = (LinkStack)malloc(sizeof(StackNode));
	if (top == NULL)
		exit(OVERFLOW);
	else
	{
		top->next = NULL;
		return OK;
	}
}
Status PushCh(LinkStack &top, SElemType e)
{

	if (!top)
		return INFEASIBLE;
	else
	{
		LinkStack p = (LinkStack)malloc(sizeof(StackNode));
		p->data.ch = e.ch;
		p->data.count = e.count;
		p->next = top->next;
		top->next = p;
		return OK;
	}
}
Status CharacterListTraverse(LinkStack top)
{
	LinkStack p = top->next; 
	while(p)
	{
		cout<<p->data.ch<<":"<<p->data.count<<" "<<p->data.HuffCode<<endl;
		p = p->next;
	}
}
Status Existence(LinkStack &top, char ch)
{
	LinkStack p = top->next; 
	while(p)
	{
		if(p->data.ch == ch)
		{
			p->data.count++;
			return TRUE;
		}
		else
			p = p->next;	
	}	
	return FALSE;
}
void CountCharacter(LinkStack List)
{
	fstream file;
	file.open("test.txt",ios::in);
	if(!file)
		exit(0);
	char c;
	while(1)
    {
        c = file.get();
        if(c == EOF) break;
        if(!Existence(List,c))
        {
        	SElemType temp;
        	temp.ch = c;
        	temp.count = 1;
        	PushCh(List,temp);
		}
    }
   	file.close();
}
int size(LinkStack top)
{
	LinkStack p = top->next; 
	int num = 0;
	while(p)
	{
		num++;
		p = p->next;
	}
	return num;
}
void reverse(LinkStack &L)
{
	LinkStack p,q;
	p = L->next;L->next = NULL;
	while(p)
	{
		q = p->next;
		p->next = L->next;
		L->next = p;
		p = q;
	}
}
Status Push(LinkStack &top, SElemType e)
{

	if (!top)
		return INFEASIBLE;
	else
	{
		LinkStack p = (LinkStack)malloc(sizeof(StackNode));
		p->data.ch = e.ch;
		p->data.HuffCode = (char *)malloc((strlen(e.HuffCode)+1) * sizeof(char));
		strcpy(p->data.HuffCode,e.HuffCode);
		p->next = top->next;
		top->next = p;
		return OK;
	}
}
