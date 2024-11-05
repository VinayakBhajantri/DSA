#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node*next;
};
struct stack
{
    struct node*top;
};
int peek(struct stack*s);
int pop(struct stack*s);
void deleteGraph(struct node*graph[],int v);
void push(struct stack*s,int e);
int isEmpty(struct stack*s);
void initstack(struct stack *s);
void displayGraph(struct node*graph[],int v);
void readGraph(struct node*graph[],int v);
void addEdge(struct node*graph[],int src,int dest);
void initGraph(struct node*graph[]);
void DFS(struct node*graph[],int v,int start);
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
    printf("start vertex\n");
    scanf("%d",&start);
    printf("Graph\n");
    DFS(graph,v,start);
    deleteGraph(graph,v);
    return 0;

}
void initGraph(struct node*graph[])
{
    int i;
    for(i=0;i<100;i++)
        graph[i]=NULL;
}
void DFS(struct node*graph[],int v,int start)
{
    int visited[100]={0};
    struct stack s;
    initstack(&s);
    push(&s,start);
    printf("%d\t",start);
    visited[start]=1;
    struct node*p,*q=NULL;
    int flag=0,u,x;
    while(!isEmpty(&s))
    {
        u=peek(&s);
        p=graph[u];
        if(flag==1)
            p=q;

            while(p!=NULL)
            {
                if(visited[p->data]==0)
                {
                push(&s,p->data);
                printf("%d\t",p->data);
                visited[p->data]=1;
                break;
                }
                p=p->next;
            }
            if(p==NULL)
            {

                x=pop(&s);
                q=graph[x];
                q=q->next;
                if(flag==0)
                flag=1;

            }
            else
                {
                    q=NULL;
                    flag=0;
                }
        }

}
int peek(struct stack*s)
{
    struct node*cur=s->top;
    return cur->data;
};
int isEmpty(struct stack*s)
{
    if(s->top==NULL)
        return 1;
    else
        return 0;
}
int pop(struct stack*s)
{
    struct node*cur=s->top;
    s->top=cur->next;
    free(cur);
    return cur->data;
};
void push(struct stack*s,int e)
{
    struct node*p=(struct node*)malloc(sizeof(struct node));
    p->data=e;
    p->next=s->top;
    s->top=p;
}
void initstack(struct stack *s)
{
    s->top=NULL;
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
        struct node*q=graph[src];
        while(q->next!=NULL)
            q=q->next;
        q->next=p;
    }

}
void deleteGraph(struct node*graph[],int v)
{
    int i;
    struct node*p;
    for(i=0;i<v;i++)
    {
        p=graph[i];
        while(p!=NULL)
        {
            graph[i]=p->next;
            free(p);
            p=graph[i];
        }
    }
}
