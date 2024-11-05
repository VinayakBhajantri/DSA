#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct node
{
    int data;
    struct node*next;

};
void random(int l, int h, int n);
void add(struct node**head,int n);
void read(struct node*head);
void display(struct node*head);
void sort(struct node*head,int n);
void ssort(struct node*head);
void delet(struct node**head);

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


    sort(head,n);


}
void sort(struct node*head,int n)
{

    clock_t start,stop;
    start=clock();
    ssort(head);
    printf("\n\n Sorted list:\n");
    display(head);
    stop = clock();
    struct node*cur=head;
    FILE*fp=fopen("output.txt","w");
    while(cur)
    {
        fprintf(fp,"%d ",cur->data);
        cur=cur->next;
    }
    fprintf(fp,"\n");
        float time_r = (float)(stop - start) / CLOCKS_PER_SEC;
        fprintf(fp, "selection  %d   %f sec\n", n, time_r);

}
void ssort(struct node*head)
{
    struct node*i,*j,*min;
    int temp;
    for(i=head;i!=NULL;i=i->next)
    {
        min=i;
        for(j=i->next;j!=NULL;j=j->next)
        {
            if(min->data>j->data)
            {
                min=j;
            }
        }
        temp=i->data;
        i->data=min->data;
        min->data=temp;
    }
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
