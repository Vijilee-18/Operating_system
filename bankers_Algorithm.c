#include<stdio.h>
int main()
{
    int noProcess , noResource;
    printf("Enter The Number of Process :");
    scanf("%d",&noProcess);
    printf("Enter The Number of Resource :");
    scanf("%d",&noResource);
    int alloc[noProcess][noResource] ,  max[noProcess][noResource] , need[noProcess][noResource] , avail[noResource];

    //Allocation Matrix 
    printf("Enter The Allocation Matrix : \n");
    for(int i=0;i<noProcess;i++)
    {
        for(int j=0 ;j<noResource;j++)
        {
            scanf("%d",&alloc[i][j]);
        }
    }
    //Max Matrix 
    printf("Enter The Max Matrix : \n");
    for(int i=0;i<noProcess;i++)
    {
        for(int j=0 ;j<noResource;j++)
        {
            scanf("%d",&max[i][j]);
        }
    }
    //Available Resource
    printf("\nEnter the Available Matrix : ");
    for(int i=0;i<noResource;i++){
        scanf("%d",&avail[i]);
    }
    
    //Need Matrix
    for(int i=0;i<noProcess;i++){
        for(int j=0;j<noResource;j++){
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }

    int finish[noProcess] ,safeSequence[noProcess];
    for(int i=0;i<noProcess;i++)
    {
        finish[i]=0;
    }
    int count=0;
    while(count<noProcess)
    {
        int found=0;
        for(int i=0;i<noProcess;i++)
        {
            if(finish[i]==0)
            {
                int j;
                for(j=0;j<noResource;j++){
                    if(need[i][j]>avail[j]){
                        break;
                    }
                }
                if(j==noResource){
                    for(int k=0;k<noResource;k++)
                    {
                        avail[k] +=alloc[i][k];
                    }
                    safeSequence[count++]=i;
                    finish[i]=1;
                    found=1;
                }
            }
        }
        if(found==0)
        {
            printf("System is Not in Safe State ");
            return 0;
        }
    }
    printf("System is in Safe State\n");
    printf("Safe Sequence :");
    for(int i=0;i<noProcess;i++)
    {
        printf("P%d",safeSequence[i]);
    }
    return 0;
}