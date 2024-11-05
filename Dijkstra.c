#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int indexi[100]={0};
int available[100]={0};
struct vertex
{
    int v;
    int wt;
};
struct node
{
    struct vertex data;
    struct node*next;
};
struct Graph
{
    struct node*head;
    struct node*last;
};
struct Heap
{
    struct vertex a[100];
    int size;
};
void Heapify(struct Heap*h,int i);
void initGraph(struct Graph G[])
{
    int i;
    for(i=0;i<100;i++)
    {
        G[i].head=NULL;
        G[i].last=NULL;
    }
}
void addEdge(struct Graph G[],int src,int dest,int wt)
{
    struct node*p=(struct node*)malloc(sizeof(struct node));
    p->next=NULL;
    p->data.v=dest;
    p->data.wt=wt;

    if(G[src].head==NULL)
    {
       G[src].head=p;
       G[src].last=p;
    }
    else
    {
        (G[src].last)->next=p;
        G[src].last=p;
    }
}

void initHeap(struct Heap*h)
{
    h->size=0;
}

void swap(struct vertex* a,struct vertex* b)
{
   struct vertex temp;
   temp=*a;
   *a=*b;
   *b=temp;
}

void swapInt(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

void decreaseKey(struct Heap*h,int i,int k)
{
    h->a[i].wt=k;

    while(i!=0&& (h->a[i]).wt < (h->a[(i-1)/2]).wt)

    //while(i!=0&&(h->a[i].wt)<(h->a[[i-1]/2]].wt))
    {
        swap(&h->a[i],&(h->a[(i-1)/2]));
        swapInt(&indexi[i],&(indexi[(i-1)/2]));
        i=(i-1)/2;
    }
}

int isEmpty(struct Heap*h)
{
    return h->size;
}

struct vertex extractMin(struct Heap*h)
{
   struct vertex u;
   u=h->a[0];
   h->a[0]=h->a[h->size-1];
   h->size--;
   available[u.v]=0;
   int x=h->a[0].v;
   indexi[x]=0;
   Heapify(h,0);
   return u;
}

int left(int i)
{
    return (2*i)+1 ;
}

int right(int i)
{
    return (2*i)+2;
}



void Dijkstra(struct Graph G[],int v,int src)
{
    struct Heap h;
    initHeap(&h);
    struct vertex u,e;
    int distance[100]={0};
    int i,j,x,wt,d;
    for(i=0;i<v;i++)
    {
        h.a[i].v=i;
        h.a[i].wt=INT_MAX;
        indexi[i]=i;
        available[i]=1;
    }
    h.size=v;
    decreaseKey(&h,indexi[src],0);

    while(isEmpty(&h)!=0)
    {
        u=extractMin(&h);
        x=u.v;
        d=u.wt;
        distance[x]=d;
        printf("        %d       %d\n",x,d);
        struct node*q=G[x].head;
        while(q!=NULL)
        {
            e=q->data;
            if(available[e.v]&&e.wt+d<(h.a[indexi[e.v]]).wt)
                decreaseKey(&h,indexi[e.v],e.wt+d);

            q=q->next;
        }
    }

    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < v; i++)
        printf("%d \t\t\t\t %d\n", i, distance[i]);

}


void Heapify(struct Heap*h,int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if(l<h->size&&h->a[l].wt<h->a[i].wt)
        smallest = l;
    if(r<h->size&&h->a[r].wt<h->a[smallest].wt)
        smallest = r;
    if (smallest != i)
    {
        swap(&h->a[i],&h->a[smallest]);
        Heapify(h,smallest);}
}
int main()
{
    struct Graph G[100];
    initGraph(G);
    int i,j,e,d,dest,v,start,wt;
    printf("Enter no. of vertices\n");
    scanf("%d",&v);
    for(i=0;i<v;i++)
    {
        printf("Enter no. of edges from %d:",i);
        scanf("%d",&e);
        for(j=0;j<e;j++)
        {
            printf("Enter dest vertex no. from %d:",i);
            scanf("%d",&dest);
            printf("Enter wt of dest vertex\n");
            scanf("%d",&wt);
            addEdge(G,i,dest,wt);
        }
    }
    printf("Enter src vertex\n");
    scanf("%d",&start);
    Dijkstra(G,v,start);
    return 0;
}
