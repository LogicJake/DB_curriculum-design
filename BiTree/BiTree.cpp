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
	bool tag;		//0为左子数 1为右子树 
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
int BiTreeDepth(BiTree &T)			//求树的高度 
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
void PreOrderTraverse(BiTree T)		//前序遍历
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
void InOrderTraverse(BiTree T)		//中序遍历
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
void PostOrderTraverse(BiTree T)	//后序遍历
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
void LevelOrderTraverse(BiTree T)		//层次遍历 
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
    	if(num1 == 0)		//一层输出完毕换行 
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
void PreOrderTraverse_recursion(BiTree T)		//递归前序遍历
{
	if(T!=NULL)
    {
        printf("%c ",T->data);
        PreOrderTraverse_recursion(T->lchild);
        PreOrderTraverse_recursion(T->rchild);
    }
}
void InOrderTraverse_recursion(BiTree T)      //递归中序遍历
{
    if(T!=NULL)
    {
        InOrderTraverse_recursion(T->lchild);
        printf("%c ",T->data);
        InOrderTraverse_recursion(T->rchild);
    }
}
void PostOrderTraverse_recursion(BiTree T)    //递归后序遍历
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
void LevelOrderTraverse_recursion(BiTree T)		//层次遍历递归
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
int LeafNode(BiTree T)							//求叶子结点个数
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
Status IsCompleteBinaryTree(BiTree T)		//层次遍历 
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
	cout<<"前序遍历：    ";
	PreOrderTraverse(T);
	cout<<"\n前序遍历递归：";
	PreOrderTraverse_recursion(T);
	cout<<"\n中序遍历：    ";
	InOrderTraverse(T);
	cout<<"\n中序遍历递归：";
	InOrderTraverse_recursion(T);
	cout<<"\n后序遍历：    ";
	PostOrderTraverse(T);
	cout<<"\n后序遍历递归：";
	PostOrderTraverse_recursion(T);
	cout<<"\n层次遍历：    \n";
	LevelOrderTraverse(T);
	cout<<"\n\n层次遍历递归:\n";
	LevelOrderTraverse_recursion(T);
	cout<<"\n叶子结点个数："<<LeafNode(T);
	cout<<"\n是否为完全二叉树：";
	if(IsCompleteBinaryTree(T))
		cout<<"是";
	else
		cout<<"否"; 
	exchange(T);
	cout<<"\n\n交换左右子树\n";
	LevelOrderTraverse_recursion(T);
	return 0;
}
