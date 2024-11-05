#include<stdio.h>
#define MAX 100

struct stack
{
    int elements[MAX];
    int top;
};

int main()
{
    int graph[100][100];
    initGraph(graph);
    int v,start;
    printf("Enter no. of vetices\n");
    scanf("%d",&v);
    readGraph(graph,v);
    printf("Graph\n");
    displayGraph(graph,v);
    printf("start\n");
    scanf("%d",&start);
    printf("DFS\n");
    DFS(graph,v,start);
    return 0;
}
void initGraph(int graph[100][100])
{
    int i,j;
    for(i=0;i<100;i++)
    {
        for(j=0;j<100;j++)
            graph[i][j]=0;
    }
}
void readGraph(int graph[100][100],int v)
{
    int i,j,e;
    for(i=10;i<v;i++)
    {
        for(j=10;j<v;j++)
        {
            printf("Is there an edge from %d to %d:\n",i,j);
            scanf("%d",&e);
            if(e==1)
            {
                graph[i][j]=1;
            }

        }
    }
}
void displayGraph(int graph[100][100],int v)
{
    int i,j;
    for(i=10;i<v;i++)
    {
        for(j=10;j<v;j++)
        {
            printf("%d\t",graph[i][j]);
        }
        printf("\n");
    }
}
void DFS(int graph[100][100],int v,int start)
{
    int u,e=0,i;
    int visited[100]={0};
    struct stack s;
    initstack(&s);
    push(&s,start);
    printf("%d\t",start);
    visited[start]=1;
    while(!isEmpty(&s))
    {
        u=peek(&s);
        for(i=e;i<v;i++)
        {
            if(graph[u][i]==1&&visited[i]==0)
            {
                push(&s,i);
                printf("%d\t",i);
                visited[i]=1;
                break;
            }

        }
        if(i==v)
        {
            e=pop(&s);
            e++;
        }
        else
            e=0;
    }
}
void initstack(struct stack*s)
{
    s->top=-1;
}
void push(struct stack*s,int e)
{
    s->top++;
    s->elements[s->top]=e;

}
int pop(struct stack*s)
{
    int e=s->elements[s->top];
    s->top--;
    return e;
}
int peek(struct stack* s)
{
    int e=s->elements[s->top];
    return e;
}
int isEmpty(struct stack*s)
{
    if(s->top==-1)
        return 1;
    else
        return 0;
}
