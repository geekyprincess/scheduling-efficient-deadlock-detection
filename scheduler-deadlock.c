/*
This is a project on finding a better scheduling for the process so as to minimize deadlock. 


<<<<<<<<<<<<<<<<<<<<<<<<<<<      It has been coded by geekyprincess (aka Ashima),   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<<<<<<<<<<      Other project members were(Manisha, Ruchi, Raghav)>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

*/


#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
//global variables
int process,resource;
int avail[10],max[15][10],allot[15][10],need[15][10],completed[15],ser[15],arrv[15],p[15];

main()
{

   int i,j,instanc,k=0,count1=0,count2=0;
   printf("\n\t Enter No. of Process(max 15):-\n");
   printf("\t\t");
   scanf("%d",&process);
//Entering No. of Processes
   for(i=0;i<process;i++)
   {
       p[i]=i;
   }

   printf("\n\tEnter No. of Resources(max 10):-\n");
   printf("\t\t");
   scanf("%d",&resource);
//No. of Resources
   for(i=0;i<process;i++)
   completed[i]=0;
//Setting Flag for uncompleted Process
   printf("\n\tEnter No. of Available Instances\n");
   for(i=0;i<resource;i++)
   {
     printf("\t\t");
     scanf("%d",&instanc);
     avail[i]=instanc;                        // Storing Available instances
   }

   printf("\n\tEnter Maximum No. of instances of resources that a Process need:\n");
   for(i=0;i<process;i++)
   {
        printf("\n\t For P[%d]\n",i);
        for(j=0;j<resource;j++)
        {
            printf("\t");
            scanf("%d",&instanc);
            fflush(stdin);
            max[i][j]=instanc;
        }
   }

 //Entering burst time for all processes
   for(i=0;i<process;i++)
   {
        printf("Enter the burst time of %d process:\t",i+1);
        scanf("%d",&ser[i]);
        arrv[i] =0;
   }

   printf("\n\t Enter no. of instances already allocated to process of a resource:\n");
   for(i=0;i<process;i++)
   {
        printf("\n\t For P[%d]\t\n",i);
        for(j=0;j<resource;j++)
        {
            printf("\t\t");
            scanf("%d",&instanc);
            allot[i][j]=instanc;
            need[i][j]=max[i][j]-allot[i][j];       //calculating Need of each process
        }
   }

    int t;
    for(t=0;t<3;t++)
    {
        int var1, var2;

        var1= 1 + rand() / (RAND_MAX / (process - 1 + 1) + 1);
        var2 = 1 + rand() / (RAND_MAX / (process - 1 + 1) + 1);

        swapRow(var1, var2,max);
        swapRow(var1,var2,allot);
        swapRow(var1,var2,need);
        swapCol(var1,var2,completed);
        swapCol(var1,var2,p);
        swapCol(var1,var2,ser);
        bankers(t);
        //setting complete array to 0
        for(i=0;i<process;i++)
            completed[i]=0;
    }
}

bankers(int t)
{
    int count1 = 0, count2 = 0,i , j,k, n=0;
    int safe[15];
    printf("\n");
    printf("\nSafe Sequence is:- \t");
    while(count1!=process)
    {
    count2=count1;
    for(i=0;i<process;i++)
    {
       for(j=0;j<resource;j++)
       {
            if(need[i][j]<=avail[j])
            {
                 k++;
            }
        }
        if(k==resource && completed[i]==0 )
        {
           safe[n] = i;
           n++;
           printf("P[%d]\t",p[i]);
           completed[i]=1;
           for(j=0;j<resource;j++)
           {
               avail[j]=avail[j]+allot[i][j];
           }
           count1++;
         }
         k=0;
    }
         if(count1==count2)
         {
         printf("\t\t Stop ..After this.....Deadlock \n");
            break;
         }
    }

    printf("\n");
     for(i=0;i<3;i++)
    {
        for(j=0;j<process;j++)
            printf("%d\t",ans[i][j]);
        printf("\n");
    }
    if(count1!=count2)
        fcfs(safe);
}
//using First Come First Serve Algorithm
fcfs(int *safe[])
{
    int i,j,sum=0;
    int arrv[15],start[15];
    int finish[15],wait[15],turn[15];
    float avgturn=0.0,avgwait=0.0;
    start[0]=0;

   for(i=0;i<process;i++)
    {
        sum=0;
        for(j=0;j<i;j++)
        sum=sum+ser[j];
        start[i]=sum;
    }
    for(i=0;i<process;i++)
    {
        finish[i]=ser[i]+start[i];
        wait[i]=start[i];
        turn[i]=ser[i]+wait[i];
    }
    for(i=0;i<process;i++)
    {
        avgwait+=wait[i];
        avgturn+=turn[i];
    }
    avgwait/=process;
    avgturn/=process;
    printf("\nAverage waiting time=%f",avgwait);
    printf("\nAverage turn around time=%f",avgturn);
}
//function to swap two rows in a 2d array
swapRow(int a,int b, int array1[15][10])
{
    int i,c;
     for (i = 0; i < process; ++i)
    {
        //  first row has index is
        c = array1[a - 1][i];
        array1[a - 1][i] = array1[b - 1][i];
        array1[b - 1][i] = c;
    }
}

//function to swap two column in a array
swapCol(int p,int q, int array2[15])
{
int i,r;
        // first column index is 0
        r = array2[p - 1];
        array2[p - 1] = array2[q - 1];
        array2[q - 1] = r;
}
