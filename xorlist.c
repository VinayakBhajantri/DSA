#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>
struct node
{
    int data;
    struct node*next;
};
void di(struct node*head);
void add(struct node**head,int e);
struct node*XOR(struct node*p,struct node*q);
int main()
{
    struct node*head=NULL;
    int i,e,n;
    printf("Enter numbe  ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("add ");
        scanf("%d",&e);
        add(&head,e);
    }
    di(head);
}
void add(struct node**head,int e)
{
    struct node*p=(struct node*)malloc(sizeof(struct node));
    if(p==NULL)
    {
        perror("");
        return;
    }
    p->data=e;
    p->next=NULL;
    if(*head==NULL)
    {
        *head=p;
        return;

    }
    p->next=XOR(NULL,*head);
    (*head)->next=XOR(p,(*head)->next);
    *head=p;
}
struct node*XOR(struct node*p,struct node*q)
{
    struct node*r;
    r=(struct node*)((uintptr_t)p^(uintptr_t)q);
    return r;
}
void di(struct node*head)
{
    struct node*cur=head;
    struct node*prev=NULL;
    struct node*q;
    while(cur)
    {
        printf("%d\t",cur->data);
        q=XOR(cur->next,prev);
        prev=cur;
        cur=q;


    }
}
