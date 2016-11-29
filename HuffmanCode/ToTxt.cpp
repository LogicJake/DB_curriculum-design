#include <iostream>
#include "count.h"
#include <fstream>
#include <stdlib.h>
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
	fp.open("Codetable.txt",ios::in);
	filein.open("TextToCode.txt",ios::in);
	fileout.open("CodeToText.txt",ios::out);
	LinkStack s;
	SElemType e;
	char ch;
	int i = 0,MAX_SIZE = 0;
	InitCharacterList(s);
	char *c;
	string str;
	getline(fp,str);
	while(!fp.eof())
	{
		c = (char *)malloc(str.size() * sizeof(char));
		strcpy(c, str.c_str());
		char *tokenPtr;
		tokenPtr=strtok(c,"`");
        e.ch = tokenPtr[0];
        tokenPtr=strtok(NULL,"`");
        tokenPtr=strtok(NULL,"`");
        e.HuffCode = (char *)malloc((strlen(tokenPtr)+1) * sizeof(char));
        if(strlen(tokenPtr) > MAX_SIZE)
        	MAX_SIZE = strlen(tokenPtr);
    	strcpy(e.HuffCode,tokenPtr);
     	Push(s,e);
		getline(fp,str);
	}
	char temp[MAX_SIZE+1];
	while(!filein.eof())
	{
		temp[i++] = filein.get();
		temp[i] = '\0';
		if(decode(s,temp,ch))
		{
			memset(temp,0,MAX_SIZE+1);
			if(ch == '|')
				fileout<<endl;
			else
				fileout<<ch;
			i = 0;
		}
	}	
	fp.close();
	filein.close();
	fileout.close();
	cout<<"解码完成，到CodeToText.txt中查看！"<<endl;
}
