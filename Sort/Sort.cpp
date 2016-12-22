#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <string.h>
using namespace std;
string source = "E:\\Program Files\\DB\\curriculum design\\Sort\\Data\\";
string obj = "E:\\Program Files\\DB\\curriculum design\\Sort\\";		//存放排序结果的文件夹 
void InsertSort(int a[], int n, int no)
{
	int i,j,temp = -1,num = 0;
	int key[20001];
	fstream fp;
	char fileout[70];
	string tempout;
	char buf[10];
 	sprintf(buf,"%d",no);
 	string b = "_sort.txt"; 
	tempout = buf+b;
	tempout = obj+"直接插入排序\\"+tempout;
	for(j = 0; j < tempout.length(); j++)
		fileout[j] = tempout[j];
	fileout[j] = '\0';
	fp.open(fileout,ios::out);
	if(fp.fail())
	{
		cout<<"打开"<<fileout<<"失败!";
		return ;
	}
	key[0] = -1;
	for(j = 1; j <= 20000; j++)
		key[j] = a[j-1];
//	for(j = 0; j <= 20001; j++)
//	{		cout<<key[j]<<" ";
//		getchar();
//	}

	for(i = 2; i <= 20000; i++)
	{
		num++;
		if(key[i] < key[i-1])
		{ 
			key[0] = key[i];
			for(j = i-1; key[j] > key[0]; --j)
			{
				num ++;
				key[j+1] = key[j];
			}
			key[j+1] = key[0];
		}
	} 
	cout<<"\t文件"<<no<<"\t\t"<<setw(20)<< setfill(' ')<<left<<"直接插入排序"<<num;
    for(j = 1; j <= 20000; j++)
    	fp<<key[j]<<" ";
   	fp.close();
}
void BInsertSort(int a[], int n, int no)
{
	int i,j,num = 0,low,high,m;
	int key[20001];
	fstream fp;
	char fileout[70];
	string tempout;
	char buf[10];
 	sprintf(buf,"%d",no);
 	string b = "_sort.txt"; 
	tempout = buf+b;
	tempout = obj+"折半插入排序\\"+tempout;
	for(j = 0; j < tempout.length(); j++)
		fileout[j] = tempout[j];
	fileout[j] = '\0';
	fp.open(fileout,ios::out);
	if(fp.fail())
	{
		cout<<"打开"<<fileout<<"失败!";
		return ;
	}
	key[0] = -1;
	for(j = 1; j <= 20000; j++)
		key[j] = a[j-1];
	for(i = 2; i <= 20000;i++)
	{
		key[0] = key[i];
		low = 1;
		high = i-1;
		while(low <= high)		//对半查找 
		{
			num++;
			m = (low+high)/2;
			if(key[0] < key[m])
				high = m-1;
			else 
				low = m+1;
		}
		for(j = i-1; j >= high+1; j--)			//移位 
		{
			key[j+1] = key[j]; 
		}
		key[high+1] = key[0];
	 } 
	cout<<"\t文件"<<no<<"\t\t"<<setw(20)<< setfill(' ')<<left<<"折半插入排序"<<num;
    for(j = 1; j <= 20000; j++)
    	fp<<key[j]<<" ";
   	fp.close();	
}
void bubble_sort(int a[], int n, int no)
{
	int flag,i,j,temp,num = 0;
	fstream fp;
	char fileout[60];
	string tempout;
	char buf[10];
 	sprintf(buf,"%d",no);
 	string b="_sort.txt";
	tempout = buf+b;
	tempout = obj+"起泡排序\\"+tempout;
	for(j = 0; j < tempout.length(); j++)
		fileout[j] = tempout[j];
	fileout[j] = '\0';
	fp.open(fileout,ios::out);
	if(fp.fail())
	{
		cout<<"打开"<<fileout<<"失败!";
		return ;
	}
    for (j = 0; j < n - 1; j++)
    {
    	flag = 0;
        for (i = 0; i < n - 1 - j; i++)
        {
        	num++;
            if(a[i] > a[i + 1])
            {
            	flag = 1;
                temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
            }
        }
        if(flag == 0)
        	break;
    }
   	cout<<"\t文件"<<no<<"\t\t"<<setw(20)<< setfill(' ')<<left<<"起泡排序"<<num;
    for(j = 0; j < 20000; j++)
		fp<<a[j]<<" ";
   	fp.close();
}
int num = 0;
void QuickSort(int a[], int left, int right)
{
	if(left >= right)/*如果左边索引大于或者等于右边的索引就代表已经整理完成一个组了*/
    {
        return ;
    }
    int i = left;
    int j = right;
    int key = a[left];
    while(i < j)
    {
    	num++;
        while(i < j && key <= a[j])
        {
        	num++;
            j--;
        }
        a[i] = a[j];
        while(i < j && key >= a[i])
        {
        	num++;
            i++;
        }
        a[j] = a[i];
    }
    a[i] = key;
    QuickSort(a, left, i - 1);
    QuickSort(a, i + 1, right);
}
void QSort(int a[], int no)
{
	int i,j;
	fstream fp;
	char fileout[70];
	string tempout;
	char buf[10];
 	sprintf(buf,"%d",no);
 	string b = "_sort.txt"; 
	tempout = buf+b;
	tempout = obj+"快速排序\\"+tempout;
	for(j = 0; j < tempout.length(); j++)
		fileout[j] = tempout[j];
	fileout[j] = '\0';
	fp.open(fileout,ios::out);
	if(fp.fail())
	{
		cout<<"打开"<<fileout<<"失败!";
		return ;
	}
	QuickSort(a,0,19999);
	cout<<"\t文件"<<no<<"\t\t"<<setw(20)<< setfill(' ')<<left<<"快速排序"<<num;
    for(j = 0; j < 20000; j++)
		fp<<a[j]<<" ";
   	fp.close();
}
void SelectSort(int a[],int n, int no)
{
	int i,j,temp,num = 0;
	fstream fp;
	char fileout[60];
	string tempout;
	char buf[10];
 	sprintf(buf,"%d",no);
 	string b="_sort.txt";
	tempout = buf+b;
	tempout = obj+"选择排序\\"+tempout;
	for(j = 0; j < tempout.length(); j++)
		fileout[j] = tempout[j];
	fileout[j] = '\0';
	fp.open(fileout,ios::out);
	if(fp.fail())
	{
		cout<<"打开"<<fileout<<"失败!";
		return ;
	}
	for(i = 0; i < n; i++){
    	int min = a[i]; 
        int temp;
        int index = i;
        for(j = i; j < n; j++)
		{
			num++;
            if(a[j] < min){ 
           		min = a[j]; 
            	index = j;
            }       
        }       
        temp = a[i]; 
        a[i] = min;
        a[index]= temp;
    }  
	cout<<"\t文件"<<no<<"\t\t"<<setw(20)<< setfill(' ')<<left<<"选择排序"<<num;
    for(j = 0; j < 20000; j++)
		fp<<a[j]<<" ";
   	fp.close();
}
//堆排序
int num1 = 0;
void HeapAdjust(int array[],int i,int nLength)
{
    int nChild;
    int nTemp;
    for(; 2*i+1 < nLength; i = nChild)
    {
        nChild = 2*i+1;
        num1++;
        if(nChild < nLength-1 && array[nChild+1] > array[nChild])
			++nChild;
		num1++;
        if(array[i]<array[nChild])
        {
            nTemp=array[i];
            array[i]=array[nChild];
            array[nChild]=nTemp; 
        }
        else break;
    }
}
void HeapSort(int array[], int length, int no)
{
	int i,j,temp;
	fstream fp;
	char fileout[70];
	string tempout;
	char buf[10];
 	sprintf(buf,"%d",no);
 	string b = "_sort.txt"; 
	tempout = buf+b;
	tempout = obj+"堆排序\\"+tempout;
	for(j = 0; j < tempout.length(); j++)
		fileout[j] = tempout[j];
	fileout[j] = '\0';
	fp.open(fileout,ios::out);
	if(fp.fail())
	{
		cout<<"打开"<<fileout<<"失败!";
		return ;
	}
    for(i = length/2-1; i >= 0; --i)
    	HeapAdjust(array,i,length);
    for(i = length-1; i > 0; --i)
    {
		temp = array[i];
		array[i] = array[0];
		array[0] = temp; 
        HeapAdjust(array,0,i);
    }
    cout<<"\t文件"<<no<<"\t\t"<<setw(20)<< setfill(' ')<<left<<"堆排序"<<num1;
    for(j = 0; j < 20000; j++)
		fp<<array[j]<<" ";
   	fp.close();
} 
//基数排序
int num2 = 0;
int maxbit(int data[], int n)   
{  
    int d = 1; //保存最大的位数  
    int p = 10;  
    for(int i = 0; i < n; ++i)  
    {  
        while(data[i] >= p)  
        {  
            p *= 10;  
            ++d;  
        }  
    }  
    return d;  
}  
void radixsort(int data[], int n, int no) //基数排序  
{  
	int i,j,k;
	fstream fp;
	char fileout[70];
	string tempout;
	char buf[10];
 	sprintf(buf,"%d",no);
 	string b = "_sort.txt"; 
	tempout = buf+b;
	tempout = obj+"基数排序\\"+tempout;
	for(j = 0; j < tempout.length(); j++)
		fileout[j] = tempout[j];
	fileout[j] = '\0';
	fp.open(fileout,ios::out);
	if(fp.fail())
	{
		cout<<"打开"<<fileout<<"失败!";
		return ;
	}
    int d = maxbit(data, n);  
    int tmp[n];  
    int count[10]; //计数器  
    int radix = 1;  
    for(i = 1; i <= d; i++) //进行d次排序  
    {  
        for(j = 0; j < 10; j++)  
            count[j] = 0; //每次分配前清空计数器  
        for(j = 0; j < n; j++)  
        {  
            k = (data[j] / radix) % 10; //统计每个桶中的记录数  
            count[k]++;  
        }  
        for(j = 1; j < 10; j++)  
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶  
        for(j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中  
        {  
            k = (data[j] / radix) % 10;  
            tmp[count[k] - 1] = data[j];  
            count[k]--;  
        }  
        for(j = 0; j < n; j++) //将临时数组的内容复制到data中  
            data[j] = tmp[j];  
        radix = radix * 10;  
    }  
    
    cout<<"\t文件"<<no<<"\t\t"<<setw(20)<< setfill(' ')<<left<<"基数排序"<<num2;
    for(j = 0; j < 20000; j++)
		fp<<data[j]<<" ";
   	fp.close();
}
int main()
{
	fstream fp;
	int i,j;
	string tempin;
	char filein[50];
	int a[20000];
	int Arraytemp[20000];
	clock_t start,finish;
	cout<<"\t文件\t\t"<<setw(20)<< setfill(' ')<<left<<"排序方法"<<setw(20)<< setfill(' ')<<left<<"比较次数"<<"比较时间(s)"<<endl;
	for (i = 1; i <= 8; ++i)
	{
		char buf[10];
 		sprintf(buf,"%d",i);
		string b=".txt";
		tempin = buf+b;
		tempin = source+tempin;
   		for(j = 0; j < tempin.length(); j++)
   			filein[j] = tempin[j];
		filein[j] = '\0';
		fp.open(filein,ios::in);
		if(fp.fail())
		{
			cout<<"打开"<<filein<<"失败!";
			exit(0); 
		}
		for(j = 0; j < 20000; j++)
			fp>>a[j];
					
		for(j = 0; j < 20000; j++)
			Arraytemp[j] = a[j];
		start = clock();
		InsertSort(Arraytemp,20000,i);
		finish = clock();
		cout<<"\t\t"<<left<<1.0*(finish-start)/CLOCKS_PER_SEC<< endl;
		
		for(j = 0; j < 20000; j++)
			Arraytemp[j] = a[j];
		start = clock();
		BInsertSort(Arraytemp,20000,i);
		finish = clock();
		cout<<"\t\t"<<left<<1.0*(finish-start)/CLOCKS_PER_SEC<< endl;

		for(j = 0; j < 20000; j++)
			Arraytemp[j] = a[j];	
		start = clock();
		bubble_sort(Arraytemp,20000,i);
		finish = clock();
		cout <<"\t\t"<< 1.0*(finish-start)/CLOCKS_PER_SEC<< endl;
	
		for(j = 0; j < 20000; j++)
			Arraytemp[j] = a[j];	
		start = clock();
		QSort(Arraytemp, i);
		finish = clock();
		cout <<"\t\t"<< 1.0*(finish-start)/CLOCKS_PER_SEC<< endl;
		num = 0;
		
		for(j = 0; j < 20000; j++)
			Arraytemp[j] = a[j];	
		start = clock();
		SelectSort(Arraytemp,20000,i);
		finish = clock();
		cout <<"\t\t"<< 1.0*(finish-start)/CLOCKS_PER_SEC<< endl;
		
		for(j = 0; j < 20000; j++)
			Arraytemp[j] = a[j];	
		start = clock();
		HeapSort(Arraytemp,20000,i);
		finish = clock();
		cout <<"\t\t"<< 1.0*(finish-start)/CLOCKS_PER_SEC<< endl;
		num1 = 0;

		for(j = 0; j < 20000; j++)
			Arraytemp[j] = a[j];	
		start = clock();
		radixsort(Arraytemp,20000,i);
		finish = clock();
		cout <<"\t\t"<< 1.0*(finish-start)/CLOCKS_PER_SEC<< endl;
		num2 = 0;	
		fp.close();
		memset(a,0,20000*sizeof(int));
		tempin.clear();
		system("pause");
	}
}
