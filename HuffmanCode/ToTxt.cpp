#include <iostream>
#include "count.h"
#include <fstream>
#include <stdio.h>
using namespace std;
Status decode(LinkStack s, char *temp, char &ch)
{
	LinkStack p = s->next; 
	while(p)
	{
		if(strcmp(p->data.HuffCode,temp) == 0)
		{
			ch = p->data.ch;
			return 1;
		}
		p = p->next;
	}
	return 0;
}
int main()
{
	fstream fp;
	fstream filein,fileout;
	fp.open("Codetable.dat",ios::in|ios::binary);
	filein.open("TextToCode.txt",ios::in);
	fileout.open("CodeToText.txt",ios::out);
	LinkStack s;
	SElemType e;
	char temp[MAX_SIZE];
	memset(temp,MAX_SIZE,0);
	char ch;
	int i = 0;
	InitCharacterList(s);
	fp.read((char *)&e,sizeof(e));
	while(!fp.eof())
	{
		Push(s,e);
		fp.read((char *)&e,sizeof(e));
	//	cout<<e.ch<<":"<<e.count<<" "<<e.HuffCode<<endl;
	}
//	CharacterListTraverse(s);
	while(!filein.eof())
	{
		temp[i++] = filein.get();
		temp[i] = '\0';
		if(decode(s,temp,ch))
		{
			memset(temp,MAX_SIZE,0);
			fileout<<ch;
			i = 0;
		}
	}	
	fp.close();
	filein.close();
	fileout.close();
}
