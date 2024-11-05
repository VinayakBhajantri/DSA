#include<stdio.h>
#include<limits.h>
#include<stdlib.h>


struct Edge
{
    int source;
    int destination;
    struct Egde *next;
};


struct Edge *HEAD=NULL;
void Insert_Edge(int, int);

int main()
{
    int vertices;

    vertices = 5;
    int graph[vertices][vertices];


    for(int i=0;i<vertices;i++)
    {
        for(int j=0;j<vertices;j++)
        {
            graph[i][j]=INT_MAX;
        }
    }


    graph[0][1]=200;
    graph[0][2]=-20;
    graph[0][3]=100;
    graph[1][4]=70;
    graph[2][3]=50;
    graph[3][4]=10;
    graph[4][2]=40;


    printf("GRAPH AFTER FILLING THE NODE IS :::\n");
    for(int i=0;i<vertices;i++)
    {
        for(int j=0;j<vertices;j++)
        {
            if(graph[i][j] == INT_MAX)
            {
                printf("%-10c", '-');
            }
            else
            {
                printf("%-10d", graph[i][j]);
            }
        }
        printf("\n");
    }

    printf("**********************************************************************\n");

    for(int i=0;i<vertices;i++)
    {
        for(int j=0;j<vertices;j++)
        {
            if(graph[i][j] != INT_MAX)
            {
                Insert_Edge(i,j);
            }
        }
    }
    int source;
    printf("Enter the source node::  ");


    scanf("%d",&source); // Choose the source as 0 for our first test case.
    int shortest_path[vertices];
    for(int i=0;i<vertices;i++)
    {
        shortest_path[i]=INT_MAX;
    }
    shortest_path[source]=0; //As Source cost to itself is 0

    // This Loop Runs |VERTICES-1| Times
    for(int i=1;i<vertices;i++)
    {
        struct Edge *temp=HEAD;
        while(temp!=NULL)
        {

            if(shortest_path[temp->source] != INT_MAX)
            {
                if(shortest_path[temp->source] + graph[temp->source][temp->destination]
                < shortest_path[temp->destination])
                {
                    shortest_path[temp->destination]=shortest_path[temp->source]
                    + graph[temp->source][temp->destination];
                }
            }
            temp= temp->next;
        }
    }
    printf("MINUMUM COSTS FOUND AFTER APPLYING THE BELLMAN FORD ALGORITHM FOR SOURCE NODE [%c] COMES OUT TO BE::: \n",source+97);
    printf("*****************************************************************\n");
    for(int i=0;i<vertices;i++)
    {
        if(shortest_path[i]==INT_MAX)
        {
            printf("Node [%c] to [%c] is unreachable \n",source+97,i+97);
            continue;
        }
        else
        {
            printf("Node [%c] TO [%c] MINIMUM COST IS:: %d\n",source+97,i+97,shortest_path[i]);
        }
    }
    return 0;
}
void Insert_Edge(int src, int des)
{
    struct Edge *ptr = (struct Edge*)malloc(sizeof(struct Edge));
    struct Edge *temp=HEAD;
    ptr->source=src;
    ptr->destination=des;
    if(HEAD==NULL)
    {
        HEAD=ptr;
        HEAD->next=NULL;
    }
    else
    {
        while(temp->next!=NULL)
        {
            temp=(struct Edge*)temp->next;
        }
        temp->next=ptr;
        ptr->next=NULL;
    }
    return ;
}
