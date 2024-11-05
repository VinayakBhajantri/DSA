#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node*next;
};
struct queue
{
    struct node *f,*r;
};
void BFS(struct node*graph[],int v,int start);
void EnQueue(struct queue*q,int e);
int isQEmpty(struct queue*q);
int DeQueue(struct queue *q);
void initQueue(struct queue*q);
void displayGraph(struct node*graph[],int v);
void readGraph(struct node*graph[],int v);
void addEdge(struct node*graph[],int src,int dest);
void initGraph(struct node*graph[]);
int main()
{
    struct node*graph[100];
    initGraph(graph);
    int v,start;
    printf("Enter no. of vertices\n");
    scanf("%d",&v);
    readGraph(graph,v);
    printf("Graph\n");
    displayGraph(graph,v);
    printf("Enter start vertex\n");
    scanf("%d",&start);
    printf("BFS traversal\n");
    BFS(graph,v,start);
    return 0;
}
void BFS(struct node*graph[],int v,int start)
{
    struct queue q;
    initQueue(&q);
    int visited[10]={0};
    int u;
    struct node*p;
    EnQueue(&q,start);
    visited[start]=1;

    while(!isQEmpty(&q))
    {
        u=DeQueue(&q);
        printf("%d\t",u);
        p=graph[u];
        while(p!=NULL)
        {
        if(visited[p->data]==0)
        {
            EnQueue(&q,p->data);
            visited[p->data]=1;
        }
        p=p->next;
    }
    }
}
void EnQueue(struct queue*q,int e)
{
    struct node*p;
    p=(struct node*)malloc(sizeof(struct node));

    p->data=e;
    p->next=NULL;
    if((q->f == NULL)&&(q->r == NULL))
       {
          q->f= q->r =p;
       }
    else
    {
        (q->r) -> next=p;
        q->r=p;
    }
}
int isQEmpty(struct queue*q)
{
    if(q->f==NULL)
        return 1;
    else
        return 0;
}
int DeQueue(struct queue *q)
{
    struct node*p=q->f;
    q->f=(q->f)->next;
    int e=p->data;
    free(p);
    if(q->f==NULL)
        q->r=NULL;
    return e;
}
void initQueue(struct queue*q)
{
    q->f=q->r=NULL;
}
void displayGraph(struct node*graph[],int v)
{
    int i;
    struct node*p;
    for(i=0;i<v;i++)
    {
        p=graph[i];
        while(p!=NULL)
        {
            printf("Edge from %d to %d\n",i,p->data);
            p=p->next;
        }
    }
}
void readGraph(struct node*graph[],int v)
{
    int i,j,e;
    for(i=0;i<v;i++)
    {
        for(j=0;j<v;j++)
        {
            printf("Is there an edge from %d to %d:\n",i,j);
            scanf("%d",&e);
            if(e==1)
                addEdge(graph,i,j);

        }
    }
}
void addEdge(struct node*graph[],int src,int dest)
{
    struct node*p=(struct node*)malloc(sizeof(struct node));
    p->data=dest;
    p->next=NULL;
    if(graph[src]==NULL)
        graph[src]=p;
    else
       {
           struct node* q=graph[src];
           while((q->next)!=NULL)
            q=q->next;
           q->next=p;
       }

}
void initGraph(struct node*graph[])
{
    int i;
    for(i=0;i<100;i++)
        graph[i]=NULL;
}
