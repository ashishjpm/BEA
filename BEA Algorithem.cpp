#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
using namespace std;
int qa[10][10],qs[10][10],fm[10],aa[10][10][10],aam[10][10],ca[10][10],q,a,s,ord[10],index=3;
//----------------------------------------------------Modual 3 Bond function ----------------------------------------------------------------------------- 
int bonda(int x,int y)//bond calculation between i-k
{
	int b=0;
	for(int k=1;k<=a;k++)
		b=b+(ca[k][x])*(aam[k][y]);
	return b;
}
int bondb(int x,int y)//bond calculation between k-j
{
	 int b=0;
     for(int k=1;k<=a;k++)
	 b=b+(aam[k][x])*(ca[k][y]);
     return b;
}

int bondc(int x,int y)//bond calculation between i-j
{
	int b=0;
	for(int k=1;k<=a;k++)
		b=b+(ca[k][x])*(ca[k][y]);
	return b;
}
//------------------------------------------------Moudual 2 Contribution function---------------------------------------------------------------------------
int cont(int i,int k,int j) //calculate contribution 
{
	
cout<<"\n\n\nCont of: "<<i<<"-"<<k<<"-"<<j;

 int s,q,w,e;
 cout<<"\n------------------------";
 q=bonda(i,k);
 w=bondb(k,j);
 e=bondc(i,j); 
  cout<<"\nBond"<<i<<"-"<<k<<" ="<<q;
  cout<<"\nBond"<<k<<"-"<<j<<" ="<<w;
  cout<<"\nBond"<<i<<"-"<<j<<" ="<<e;
	s=2*(q+w-e);
	 	return s;
}
//-------------------------------------------------Modual 1 Main function-----------------------------------------------------------------------------------
int main()
{
	int i,j,k,l;
//-----------------------------------------------Getting user input-----------------------------------------------------------------------------------------
	cout<<"\n Enter the no of queries:";
	cin>>q;
	cout<<"Enter the no of attributes:";
	cin>>a;
	cout<<"Enter the no of sites:";
	cin>>s;
	cout<<"Enter values for Attribute Usage matrix:\n\n";
	for(i=0;i<a;i++)
	for(j=0;j<q;j++)
	{
		cout<<"a"<<i+1<<".q"<<j+1<<"   :";
		cin>>qa[i][j];
	}
	cout<<"Enter values for Query Site matrix:\n\n";
	for(i=0;i<q;i++)
	for(j=0;j<s;j++)
	{
		cout<<"q"<<i+1<<".s"<<j+1<<"  :";
		cin>>qs[i][j];
	}
	for(i=0;i<q;i++)
	{
		fm[i]=0;
		for(j=0;j<s;j++)
		{
			fm[i]=fm[i]+qs[i][j];
		}
	}
	//print qa
	cout<<"\n____________________________________________________________\n";
	cout<<"QA atrix\n\n";
	for(i=0;i<a;i++)
	{
		cout<<"\n";
		for(j=0;j<q;j++)
		{
			cout<<qa[j][i]<<"\t";
		}
	}
	//print qs
	cout<<"\n____________________________________________________________\n";
	cout<<"QS matrix\n\n";
	for(i=0;i<q;i++)
	{
		cout<<"\n";
		for(j=0;j<s;j++)
		{
			cout<<qs[i][j]<<"\t";
		}
	}
	//process finding aa matrix
	for(i=0;i<a;i++)
	for(j=0;j<a;j++)
	for(k=0;k<2;k++)
	{
		aa[i][j][k]=0;
	}
	for(i=0;i<a;i++)
	for(j=0;j<a;j++)
	for(k=0;k<q;k++)
	{
		if((qa[i][k]==1)&&(qa[j][k]==1))
		{
			aa[i][j][0]=fm[k]+aa[i][j][0];
			aa[i][j][1]=k;
		}
	}
	int flag=0;
	for(i=0;i<a;i++)
	for(j=0;j<a;j++)
	{
		flag=1;
		for(k=j;k<a;k++)
		{
			if((aa[j][i][0]==aa[k][i][0])&&(aa[j][i][1]==aa[k][i][1]))
			{
				flag=0;
			}
		}
		if(flag==1)
		{
			aa[i][i][0]=aa[i][i][0]+aa[j][i][0];
		}
	}
	//print aa
	cout<<"\n____________________________________________________________\n";
	cout<<"AA matrix\n\n";
	for(i=0;i<a;i++)
	{
		cout<<"\n";
		for(j=0;j<a;j++)
		{
			cout<<aa[i][j][0]<<"\t";
		}
	}
	cout<<"\n\n\n";
	//creating aam
	for(i=0;i<10;i++)
	for(j=0;j<10;j++)
	{
	aam[i][j]=0;
	ca[i][j]=0;
	}
	
	for(i=1;i<=a;i++)
	for(j=1;j<=a;j++)
	aam[i][j]=aa[i-1][j-1][0];
	
	
	//aa to ca matrix
	
	for(int i=1;i<=a;i++)
	for(int j=1;j<=2;j++)
	{
	  ca[i][j]=aam[i][j];
	}
	//-----------------------------------------------------------MODUAL 2----------------------------------------------------------
	int temp_max=0,max=0,loc;
	int order[10],temp_order[10],loc_arry[10];
	int final[10][10];
	for(i=0;i<10;i++)
	loc_arry[i]=0;
	//---
	loc_arry[1]=1;
	loc_arry[2]=2;
	for(i=0;i<10;i++)
	{
	 order[i]=0;
	 temp_order[i]=0;
	}
	//----------------
	while(index<=a)
     { 
       temp_max=0;
	    max=0;
	  for(i=1;i<index;i++)
	  { 
	  	temp_order[0]=i-1;
	  	temp_order[1]=index;
	  	temp_order[2]=i;
	  	temp_max=cont(i-1,index,i);
	  
	  	if(temp_max>max)
	  	{
	  	max=temp_max;
	  	order[0]=temp_order[0];
	  	order[1]=temp_order[1];
	  	order[2]=temp_order[2];
	   }
	  	
	  }
	  //baundry condtion
	  int bo=cont(index-1,index,index+1);
	 if(bo>=max)
	 {
	 	cout<<"\n\n-----------------------------------------";
	    cout<<"\nMaximum value = "<<bo;
	    cout<<"  of  order :  "<<index-1<<"-"<<index<<"-"<<index+1;
	    loc=index;//Gotot laganaa hai
	    loc_arry[index]=index;
	    goto x;
	 }
	 else
	 {
	  cout<<"\n\n-----------------------------------------";
	  cout<<"\nMaximum value = "<<max;
	  cout<<"  of  order :  "<<order[0]<<"-"<<order[1]<<"-"<<order[2];
	 }
	 loc=loc_arry[order[2]];//copying the location of 3rd in max order
	 loc_arry[index]=loc;
	 
	 for(i=1;i<index;i++)
	 if(loc_arry[i]>=loc)
     loc_arry[i]=loc_arry[i]+1;//updating location
     //fill ca
     for(j=index;j>loc;j--)
     {
     for(i=1;i<=a;i++)
     ca[i][j]=aam[i][j-1];
     }
     
x: for(i=1;i<=a;i++)
					 {
					 ca[i][loc]=aam[i][loc];
					}
	cout<<"\n \nAttribute Order is :";
	for(i=1;i<=index;i++)
	cout<<" "<<loc_arry[i]<<" ";
	
		//increament index
		index=index+1;
	}
	cout<<"\n \n_______________CA MATRIX___________________________\n\n";
	for(i=1;i<=a;i++)
	{
	cout<<"\n";
	for(j=1;j<=a;j++)
	{
	
	final[i][j]=aam[loc_arry[i]][loc_arry[j]];
	cout<<final[i][j]<<"\t";
   }
}
//print 
cout<<"\n\n____________________________________________________";
system("pause");
}
     
     
     
     
	 	 
