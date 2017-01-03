#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stack>
#include <queue> 
using namespace std;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef char ElemType;
typedef int Status;
typedef struct BiTNode
{
	ElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;
typedef struct
{	
	BiTree ptr; 
	bool tag;		//0Ϊ������ 1Ϊ������ 
}stacknode;
string s;
int i = 0;
Status CreateBiTree(BiTree &T)
{
	char ch;
	ch = s[i];
	i++;
	if(ch != '\0')
	{
		if(ch == ' ')
			T = NULL;
		else
		{
			if(!(T = (BiTNode *)malloc(sizeof(BiTNode))))
				exit(OVERFLOW);
			T->data = ch;
			CreateBiTree(T->lchild);
			CreateBiTree(T->rchild);
		}
	}
	return OK;
}
int BiTreeDepth(BiTree &T)			//�����ĸ߶� 
{
	if(T == NULL)
		return 0;
	else
	{
		int lDepth,rDepth;
		lDepth = BiTreeDepth(T->lchild);
		rDepth = BiTreeDepth(T->rchild);
		if(lDepth > rDepth)
			return lDepth + 1;
		else
			return rDepth + 1;
	 } 
}
void PreOrderTraverse(BiTree T)		//ǰ�����
{
	stack<BiTree> s;
	BiTree p;
	p = T;
	while(p != NULL||!s.empty())
	{
		while(p != NULL)
		{
			printf("%c ", p->data);
			s.push(p);
			p = p->lchild;
		}
		if(!s.empty())
		{
			p = s.top();
			s.pop();
			p = p->rchild;
		}
	}
}
void InOrderTraverse(BiTree T)		//�������
{
	stack<BiTree> s;
	BiTree p;
	p = T;
	while(p != NULL||!s.empty())
	{
		while(p != NULL)
		{
			s.push(p);
			p = p->lchild;
		}
		if(!s.empty())
		{
			p = s.top();
			s.pop();
			printf("%c ", p->data);
			p = p->rchild;
		}
	}
}
void PostOrderTraverse(BiTree T)	//�������
{
	stacknode x;
	stack<stacknode> s;
	BiTree p;
	p = T;
	do
	{
		while(p != NULL)
		{
			x.ptr = p;
			x.tag = 0;
			s.push(x);
			p = p->lchild;
		}
		while(!s.empty() && s.top().tag == 1)
		{
			x.ptr = s.top().ptr;
			x.tag = s.top().tag;
			s.pop();
			p = x.ptr;
			printf("%c ",p->data);
		}
		if(!s.empty())
		{
			s.top().tag = 1;
			p = s.top().ptr->rchild;
		}
	}while(!s.empty());
}
void LevelOrderTraverse(BiTree T)		//��α��� 
{
	BiTree p;
	int num1,num2; 
    p = T;
    if (!T) {
        return;
    }
    queue<BiTree> Q; 
    Q.push(p);
    num1 = 1;
    num2 = 0;
    while (!Q.empty()) {
    	if(num1 == 0)		//һ�������ϻ��� 
    	{
    		cout<<endl;
    		num1 = num2;
    		num2 = 0;
		}
        p = Q.front();
        Q.pop();
        num1--; 
        printf("%c ",p->data);
        if (p->lchild){
			num2++;
        	Q.push(p->lchild);
        }
        if (p->rchild){
			num2++;
        	Q.push(p->rchild);
        }
    }
}
void PreOrderTraverse_recursion(BiTree T)		//�ݹ�ǰ�����
{
	if(T!=NULL)
    {
        printf("%c ",T->data);
        PreOrderTraverse_recursion(T->lchild);
        PreOrderTraverse_recursion(T->rchild);
    }
}
void InOrderTraverse_recursion(BiTree T)      //�ݹ��������
{
    if(T!=NULL)
    {
        InOrderTraverse_recursion(T->lchild);
        printf("%c ",T->data);
        InOrderTraverse_recursion(T->rchild);
    }
}
void PostOrderTraverse_recursion(BiTree T)    //�ݹ�������
{
    if(T!=NULL)
    {
        PostOrderTraverse_recursion(T->lchild);
        PostOrderTraverse_recursion(T->rchild);
        printf("%c ",T->data); 
    }    
} 
void PrintNodeAtLevel(BiTree T,int level)	
{
    if (NULL == T || level < 1 )
        return;
    if (1 == level)
    {
        cout << T->data <<" ";
        return;
    }
    PrintNodeAtLevel(T->lchild,level-1);
    PrintNodeAtLevel(T->rchild,level-1);
}
void LevelOrderTraverse_recursion(BiTree T)		//��α����ݹ�
{
    if (NULL == T)
        return;
    int depth = BiTreeDepth(T);
    int i;
    for (i = 1; i <= depth; i++)
    {
        PrintNodeAtLevel(T, i);
        cout<<endl;
    }
}
int LeafNode(BiTree T)							//��Ҷ�ӽ�����
{
	if(T == NULL)
		return 0;
	if(T->lchild == NULL && T->rchild == NULL) 
		return 1;
	return LeafNode(T->lchild) + LeafNode(T->rchild);
}
void exchange(BiTree T)
{
	BiTree temp = NULL;
 	if(T->lchild == NULL && T->rchild == NULL)
        return;
 	else{
       temp = T->lchild;
       T->lchild = T->rchild;
       T->rchild = temp;
 	}
 	if(T->lchild)
      	exchange(T->lchild);
 	if(T->rchild)
      	exchange(T->rchild);
}
Status IsCompleteBinaryTree(BiTree T)		//��α��� 
{
	bool flag = FALSE;
	BiTree p;
    p = T;
    if (!T) {
        return FALSE;
    }
    queue<BiTree> Q; 
    Q.push(p);
    while (!Q.empty()) {
    	if(flag == TRUE)
    	{
    		if(p->lchild != NULL || p->rchild != NULL)
    			return FALSE;
		}
        p = Q.front();
        Q.pop();
        if(p->lchild == NULL && p->rchild != NULL)
        	return FALSE;
        if((p->lchild != NULL && p->rchild == NULL) || (p->lchild == NULL && p->rchild == NULL))
        	flag = TRUE;
		if (p->lchild)
        	Q.push(p->lchild);
        if (p->rchild)
        	Q.push(p->rchild);
    }
    return TRUE;
}
int main()
{
	BiTree T;
	fstream fp;
	fp.open("Init.txt",ios::in);
	getline(fp,s);
	CreateBiTree(T);
	fp.close();
	cout<<"ǰ�������    ";
	PreOrderTraverse(T);
	cout<<"\nǰ������ݹ飺";
	PreOrderTraverse_recursion(T);
	cout<<"\n���������    ";
	InOrderTraverse(T);
	cout<<"\n��������ݹ飺";
	InOrderTraverse_recursion(T);
	cout<<"\n���������    ";
	PostOrderTraverse(T);
	cout<<"\n��������ݹ飺";
	PostOrderTraverse_recursion(T);
	cout<<"\n��α�����    \n";
	LevelOrderTraverse(T);
	cout<<"\n\n��α����ݹ�:\n";
	LevelOrderTraverse_recursion(T);
	cout<<"\nҶ�ӽ�������"<<LeafNode(T);
	cout<<"\n�Ƿ�Ϊ��ȫ��������";
	if(IsCompleteBinaryTree(T))
		cout<<"��";
	else
		cout<<"��"; 
	exchange(T);
	cout<<"\n\n������������\n";
	LevelOrderTraverse_recursion(T);
	return 0;
}
