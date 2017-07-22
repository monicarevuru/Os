#include <stdio.h>
#include <stdlib.h>

int Allocation[20][20],Need[20][20],Max[20][20],Available[20],work[20],Finish[20],request[20];
int n,r;

int safetyAlgorithm();
void res_request();
int main()
{
	int i,j;
	printf("Enter the number of processes: ");
	scanf("%d",&n);
	printf("Enter the number of resources: ");
	scanf("%d",&r);
	printf("Enter the available number of resources: ");
	for(i=0;i<r;i++)
	{
		scanf("%d",&Available[i]);
	}
	printf("Enter the allocation matrix: ");
	for(i=0;i<n;i++)
	{
		for(j=0;j<r;j++)
		{
			scanf("%d",&Allocation[i][j]);
		}
	}
	printf("Enter the maximum matrix: ");
	for(i=0;i<n;i++)
	{
		for(j=0;j<r;j++)
		{
			scanf("%d",&Max[i][j]);
		}
	}
	printf("The need matrix will be :\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<r;j++)
		{
			Need[i][j] = Max[i][j] - Allocation[i][j];
			printf("%d\t",Need[i][j]);
		}
		printf("\n");
	}
	//safetyAlgorithm();
	//res_request();

	int a;
	printf("\n 1. Safety Algorithm\n 2. Resouce Request\n Enter your choice\n");
	scanf("%d",&a);
	switch(a)
	{
		case 1 : safetyAlgorithm();
			 break;
		case 2 : res_request();
			 break;
			default: printf("Invalid choice\n");
	}
	
}


/*-------------------------------------------------------------------------------------------*/
					/*---safety algorithm---*/
/*-------------------------------------------------------------------------------------------*/

	
int safetyAlgorithm()
{
	int i,j,k,l,p=0;
	for(i=0;i<r;i++)
	{
		work[i] = Available[i];
		Finish[i]=0;
	}
	for(int m=0;m<n;m++)
	{
		for(i=0;i<n;i++)
		{
			l=0;			
			for(j=0;j<r;j++)
			{
				if((Finish[i]==0)&&(Need[i][j]<=work[j]))
				{
					l++;
					if(l==r)
					{
						for(k=0;k<r;k++)
						{
			               			work[k]+=Allocation[i][k];
			          			Finish[i]=1;							
						}
						p++;
						printf("P%d ",i);
					}
				}
			}		
		}
		if(p==n)
			break;
	}
	if(p == n)
	{
		printf(" is Safe sequence\nSystem is in Safe state\n");
		return 1;
	}
	else
	{
		printf("\nSystem is not in safe state\n");
		return 0;
	}

}
/*-------------------------------------------------------------------------------------------*/
				      /*---Resource Request algorithm---*/
/*-------------------------------------------------------------------------------------------*/
void res_request()
{
	char ch;
	do
	{
		int process,k=0,i,j;
		printf("Enter the process no. of requested \n");
		scanf("%d",&process);
		printf("Enter request : ");
		for(i=0;i<r;i++)
		{
			scanf("%d",&request[i]);
		}
		printf("Request array: \n");
		for(i=0;i<r;i++)
		{
			printf("%d ",request[i]);
		}
		printf("\n");
		for(j=0;j<r;j++)
		{
			if( request[j] <= Need[process][j] )
			{
				if( request[j] <= Available[j] )
				{
					k++;
					if(k == r)
					{
						for(int i=0;i<r;i++)
						{
							Available[i] = Available[i] - request[i];
						}
						for(int i=0;i<r;i++)
						{
							Allocation[process][i] = Allocation[process][i] + request[i];
							Need[process][i] = Need[process][i] - request[i];
						}
						int res = safetyAlgorithm();
						if(res == 1)
						{
							printf("Resource is allocated\n");
							printf("Allocation Matrix\n");
							for(int a=0;a<n;a++)
							{
								for(int b=0;b<r;b++)
								{
									printf("%d\t",Allocation[a][b]);
								}
								printf("\n");
							}
							printf("Available Matrix: \n");
							for(int a=0;a<r;a++)
							{
								printf("%d\t",Available[a]);
							}
							printf("\n");
						}
						else
						{
							printf("Resources are not allocated,old state is restored\n");
							printf("process %d must wait\n",process);
							for(int i=0;i<r;i++)
							{
								Available[i] = Available[i] + request[i];
							}
							for(int i=0;i<r;i++)
							{
								Allocation[process][i] = Allocation[process][i] - request[i];
								Need[process][i] = Need[process][i] + request[i];
							}
						}
   	
					}

				}
				else
					printf("process %d must wait, resources are not available\n",process);
					
			}
			else
			{
				printf("exceeded its maximum claim\n");
				exit(1);
			}	
	
		}
		printf("do you want to continue y or n: \n");
		scanf(" %c",&ch);

	}while(ch == 'y' || ch == 'Y');	
			
}



   
