#include<bits/stdc++.h>
#include<unistd.h>
#define hk 1000000
using namespace std;
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
int main()
{
    int n=4,w=8,m=2;
    cout<<"No of frames that Sender have "<<n<<"\n";
    cout<<"No of frames that Sender have "<<m<<"\n";
    cout<<"Window Size "<<w<<"\n";
    int count1=0;
    int arr1[n+1];
    int count2=0;
    int arr2[m+1];

    for(int i=0;i<=n;i++)
          arr1[i]=0;
    for(int i=0;i<=m;i++)
          arr2[i]=0; 

    int rem1=n;
    int rem2=m;

    while(count1<n||count2<m)
    {
     if(count1<n)
     {
	      cout<<"SENDER:\n\n";
	      int p=rand()%min(rem1,w)+1;
	      cout<<"Sender is sending frames:\n";
	      cout<<"No of frames send by sender: "<<p<<"\n";
	      delay(hk);
	      cout<<"Frames Are:\n";
	      int q=p,j=1;
	      vector<int>v;
	      while(q>0)
	      {
		 if(arr1[j]==0)
		 {
		        cout<<"Frame id: "<<j<<"\n";
		        delay(hk);
		        v.push_back(j);
		        q--;
		 }
		 j++;
	      }
	       for(int k=1;k<=p;k++)
	       {
		   int h=rand()%2+1;
		   if(h==1)
		   {
		     delay(hk);
		     cout<<"Frame No "<<v[k-1]<<" Successfully Transmitted\n";
		     arr1[v[k-1]]=1;
		     count1++;
		     rem1--;
		   }
		   else
		   {
		     delay(hk);
		     cout<<"Frame No "<<v[k-1]<<" Error in Transmission\n";
		     arr1[v[k-1]]=0;
		   }
	       }
       cout<<"\n\n\n";
       delay(hk);
     }
     if(count2<m)
       {
              cout<<"\nRECEIVER:\n\n";
	      int p=rand()%min(rem2,w)+1;
	      cout<<"Receiver is sending frames:\n";
	      cout<<"No of frames send by Receiver: "<<p<<"\n";
	      delay(hk);
	      cout<<"Frames Are:\n";
	      int q=p,j=1;
	      vector<int>v;
	      while(q>0)
	      {
		 if(arr2[j]==0)
		 {
		        cout<<"Frame id: "<<j<<"\n";
		        delay(hk);
		        v.push_back(j);
		        q--;
		 }
		 j++;
	      }
	       for(int k=1;k<=p;k++)
	       {
		   int h=rand()%2+1;
		   if(h==1)
		   {
		     delay(hk);
		     cout<<"Frame No "<<v[k-1]<<" Successfully Transmitted\n";
		     arr2[v[k-1]]=1;
		     count2++;
		     rem2--;
		   }
		   else
		   {
		     delay(hk);
		     cout<<"Frame No "<<v[k-1]<<" Error in Transmission\n";
		     arr2[v[k-1]]=0;
		   }
	       }
	       
	       delay(hk);
       }
       delay(3*hk);
       cout<<"--------------------------------\n";
    }
    return 0;
}