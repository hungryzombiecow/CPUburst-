#include<stdio.h>

#include<iostream>

using namespace std;
int n;
void taketheprocess(struct process p[],int n);
void print(struct process p[],int n);
bool check(struct process p[],int total,int currently);
void aftertime(struct process p[],int totaltime,int i,int previous,int currently,struct process q[],struct process t[]);
void aftertime2(struct process p[],int n,int currently,int previous,int totaltime,struct process q[],struct process t[]);
void clone(struct process p[],struct process q[],int n);
void sortonpriority(struct process p[],int n);
struct process
{
 int processno;
 int bursttime;
 int priority;
  int end=0;
int start;
int turnaroundtime;
int waitingtime;


};
    int minindex;
  int minimumburst;
  int totaltime=0;
  int previous=0;
void taketheprocess(struct process p[],int n)
{
    for(int i=0;i<n;i++)						//O(n)
    {
    p[i].processno=i;
    cout<<"Enter the burst time for Process no "<<i<<"\n";
    cin>>p[i].bursttime;
    }
}
void calculatewt(struct process q[],struct process t[],int n)
{
    for(int i=0;i<n;i++)						//O(n)
    {
     q[i].waitingtime=q[i].turnaroundtime-t[i].bursttime;
     q[i].bursttime=t[i].bursttime;
    }
}
void assignthepriority(struct process p[],struct process q[],int n)
{
    for(int i=0;i<n;i++)
    {        for(int j=i+1;j<n;j++)				//O(n^2)
        {
            if(p[i].bursttime>p[j].bursttime)
            {
                swap(p[i].bursttime,p[j].bursttime);
                swap(p[i].processno,p[j].processno);
            }
        }
    }
    int tempn=n;
    for(int i=0;i<n;i++)						//O(n)
    {
     p[i].priority=tempn--;
    }
 for(int i=0;i<n;i++)							//O(n)
 {
  q[p[i].processno].priority=p[i].priority;
 }
 for(int i=0;i<n;i++)							//O(n^2)
    {        for(int j=i+1;j<n;j++)
        {
            if(q[i].bursttime==q[j].bursttime && q[i].processno<q[j].processno && q[i].priority<q[j].priority)
            {
                swap(q[i].priority,q[j].priority);
            }
        }
    }
}
void clone(struct process p[],struct process q[],int n)
{


    for(int i=0;i<n;i++)					//O(n)
    {
        q[i]=p[i];
    }
}
void decrement(struct process p[],int currently,int previous,int totalp)
{
     p[currently].start=p[previous].end;
     p[currently].end=totalp;
    p[currently].bursttime=(p[currently].bursttime)-( p[currently].end -  p[currently].start);
    }

void execute(struct process p[],int currently,struct process q[],struct process t[])
{
    int i,alltime;
    int tempburst;
    {


        for(i=0;i<p[currently].bursttime;)
        {
         ++totaltime;
         i++;
         ++alltime;
         if(totaltime<=n-1 && i>=p[currently].bursttime)
         {
             decrement(p,currently,previous,totaltime);
         }
         if(totaltime<=n-1 && check(p,totaltime,currently))
         {
          decrement(p,currently,previous,totaltime);
          previous=currently;
          i=0;
          currently=totaltime;
          continue;
         }
         if(totaltime<=n-1 &&  !(check(p,totaltime,currently)) && p[currently].bursttime==0)
         {

             if(check(p,previous,totaltime))
             {
                 int t=currently;
             currently=previous;
             previous=t;
             i=0;
             continue;
             }
             else
             {
                 previous=currently;
              currently=totaltime;

              if(currently>n)
         {
          break;
         }
              continue;
             }
         }

         if(totaltime>n-1)
         {
          break;
         }

        }


    }
    aftertime(p,totaltime,i,previous,currently,q,t);

}
void calculatetime(struct process p[],int n)
{
 for(int i=0;i<n;i++)
 {
    p[i].turnaroundtime=p[i].end-p[i].processno;


}

}
void sortonpriority(struct process p[],int n)
{
 for(int i=0;i<n;i++)
 {
     for(int j=i+1;j<n;j++)
     {
         if(p[i].priority<p[j].priority)
         {
          swap(p[i],p[j]);

         }
     }
 }

}
void aftertime(struct process p[],int totaltime,int i,int previous,int currently,struct process q[],struct process t[])

{
    {

     for(;i<p[currently].bursttime;i++)
     {

      ++totaltime;

    }
    decrement(p,currently,previous,totaltime);
    previous=currently;


    }
    clone(p,q,n);
    sortonpriority(p,n);
    aftertime2(p,n,currently,previous,totaltime,q,t);
}




void aftertime2(struct process p[],int n,int currently,int previous,int totaltime,struct process q[],struct process t[])
{
 for(int i=0;i<n;i++)
 {
     currently=p[i].processno;
     if(q[currently].bursttime!=0)
     {
     for(int j=0;j<q[currently].bursttime;j++)
     {
         ++totaltime;

     }
     decrement(q,currently,previous,totaltime);
     previous=currently;
    }
 }
calculatetime(q,n);
calculatewt(q,t,n);
 print(q,n);
}
bool check(struct process p[],int total,int currently)
{
    if(p[total].bursttime!=0 && p[total].priority>p[currently].priority)
    {
    return true;
            }
    else
        return false;
}
void print(struct process p[],int n)
{
    float avw, avt;
     cout<<"|| Process no || Burst time ||  Priority || Process  Start time ||Process End Time||Turn Aroundtime||Waiting Time\n\n";
 for(int i=0;i<n;i++)
 {
     cout<<"\n";
    cout<<"\t"<<p[i].processno+1<<"\t";
     cout<<"\t"<<p[i].bursttime<<"\t";
     cout<<"\t"<<p[i].priority<<"\t";
    cout<<"\t"<<p[i].start<<"\t";
    cout<<"\t"<<p[i].end<<"\t";
    cout<<"\t"<<p[i].turnaroundtime<<"\t";
    cout<<"\t"<<p[i].waitingtime<<"\t";
    avw +=p[i].waitingtime;
    avt +=p[i].turnaroundtime;
}
    cout<<"\n\nAverage wating time: "<<avw/n<<endl;
    cout<<"Average turn around time: "<<avt/n;
}
main()
{
    cout<<"Enter total no of process\n";
    cin>>n;
    struct process p[n+1],q[n+1],t[n+1];
    taketheprocess(p,n);
    clone(p,q,n);
    assignthepriority(q,p,n);
    clone(p,t,n);
    execute(p,0,q,t);
    cout<<"\n";
}
