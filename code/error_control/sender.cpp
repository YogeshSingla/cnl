
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
    int n=4;
    cout<<"We are sending "<<n<<"frames from sender to receiver\n";
    for(int i=1;i<=n;i++)
    {
        int ack=0;
      while(ack==0)
      {
        cout<<"sender is sending frame no "<<i<<"\n";
        delay(100);
          int p=rand()%3+1;
          if(p==1)
          {
            cout<<"Error in Sending:\n";
            cout<<"(Receiver did not get expected "<<i<<" frame)\n\n";
            delay(100);
            int q=rand()%2+1;
            if(q==1)
            {
                cout<<"Negative ack Received by sender\n";
                cout<<"NACK=1\n\n";
                delay(100);
            }
            else
             {
                cout<<"Timeout in getting Acknowledge signal\n\n";
                delay(100);
             }
              cout<<"-------------------------------\n";
          }
          else if(p==2)
          {
              cout<<"Frame did not reach at receiver\n";
              cout<<"(timeout for frame)"<<i<<"\n";
              cout<<"-------------------------------\n";
              delay(100);
          }
          else
          {
              cout<<"Frame "<<i<<" Successfully reached at receiver\n";
              delay(100);
               int q=rand()%2+1;
               if(q==1)
                {
                  ack=1;
                  cout<<"Acknowledgment value:"<<ack<<"\n";
                  cout<<"Success\n\n";
                  delay(100);
                }
                else
                 {
                    cout<<"Timeout in getting Acknowledge signal\n";
                    delay(100);
                 }
                  cout<<"-------------------------------\n";
          }
         delay(1500);
      }
    }
    return 0;
}