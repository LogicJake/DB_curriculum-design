#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <time.h>
using namespace std;
int main()
{
	fstream fp;
	fp.open("8.txt",ios::out);
int i,a;
srand( (unsigned)time( NULL ) );
for( i = 0; i < 20000;i++ )
{
	a = rand()%1000;
	while(a == 0)
		a = rand()%1000;
	fp<<a<<" ";
} 
}
