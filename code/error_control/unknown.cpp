#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
int main()
{
    int n=10,w=8;
    cout<<"We are sending "<<n<<"frames from sender to receiver\n";
    cout<<"Window Size "<<w<<"\n";
    int count=0;
    int arr[n+1];
    for(int i=0;i<=n;i++)
          arr[i]=0;
    int rem=n;
    while(count<n)
    {
      int p=rand()%min(rem,w)+1;
      cout<<"Sender is sending frames:\n";
      cout<<"No of frames send by sender: "<<p<<"\n";
      delay(100);
      cout<<"Frames Are:\n";
      int q=p,j=1;
      vector<int>v;
      while(q>0)
      {
         if(arr[j]==0)
         {
            cout<<"Frame id: "<<j<<"\n";
                delay(200);
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
             delay(300);
             cout<<"Frame No "<<v[k-1]<<" Successfully Transmitted\n";
             arr[v[k-1]]=1;
             count++;
             rem--;
           }
           else
           {
             delay(300);
             cout<<"Frame No "<<v[k-1]<<" Error in Transmission\n";
             arr[v[k-1]]=0;
           }
       }
       cout<<"--------------------------------\n";
       delay(1000);
    }
    return 0;
}
///////////////////////////////////////////////////
