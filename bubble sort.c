#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node*next;

};
void random(int l, int h, int n);
void add(struct node**head,int n);
void delet(struct node**head);
void display(struct node*head);
void sort(struct node*head);

int main()
{
     int l, h, n;
    printf("enter range L-H and size\n");
    scanf("%d%d%d", &l, &h, &n);
    random(l, h, n);
    char str[10];
    int t;
    FILE*fp=fopen("input.txt","r");
    FILE*p=fopen("output.txt","w");
    struct node*head=NULL;
   while(!feof(fp))
    {
        fscanf(fp,"%s",str);
        t=atoi(str);
        add(&head,t);
    }
    fclose(fp);
    display(head);
    printf("\n The random numbers of the file \n");
    delet(&head);
    display(head);


    sort(head);
    printf("\n\n Sorted list:\n");
    display(head);
    struct node*cur=head;
    while(cur)
    {
        fprintf(p,"%d ",cur->data);
        cur=cur->next;
    }



}
void sort(struct node*head)
{
    struct node *i,*min;
    struct node *j=NULL;
    int si,temp;
    do
    {
        si=0;
        i=head;
        while(i->next!=j)
        {
            if(i->data>i->next->data)
            {
                temp=i->data;
                i->data=i->next->data;
                i->next->data=temp;
                si=1;
            }
            i=i->next;
        }
        j=i;
    }while(si);
}
void delet(struct node**head)
{
    struct node *cur=*head;
    *head=(*cur).next;
    free(cur);
}
void display(struct node*head)
{
    struct node*cur=head;
    while(cur)
    {
        printf("%d ",cur->data);
        cur=cur->next;
    }
}
void random(int l, int h, int n)
{
    int i, r;
    FILE *fp;
    fp = fopen("input.txt", "w");
    for (i = 0; i < n; i++)
    {
        r = rand() % (h - l) + l;
        fprintf(fp, "%d\t", r);
    }
    fclose(fp);
}

void add(struct node**head,int t)
{
    struct node*p;
    p=(struct node*)malloc(sizeof(struct node));
    if(p==NULL)
    {
        perror("space not available\n");
        return;
    }
    p->data=t;
    p->next=*head;

    *head=p;
}
