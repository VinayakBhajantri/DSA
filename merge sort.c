#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct node
{
  int data;
  struct node*next;
};
void add(struct node**head,int n);
void sort(struct node* head,int n);
void display(struct node*head);
struct node* SortedMerge(struct node* a, struct node* b);
void random(int l,int h,int n);
void delet(struct node**head);
void FrontBackSplit(struct node* source,struct node** frontRef, struct node** backRef);
void mergesort(struct node** head);
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
    mergesort(&head);
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
        fprintf(fp, "merge  %d   %f sec\n", n, time_r);

}
void display(struct node*head)
{
    struct node*cur=head;
    while(cur)
    {
        printf("%d\t",cur->data);
        cur=cur->next;
    }
}
void delet(struct node**head)
{
    struct node*cur=*head;
    *head=cur->next;
    free(cur);
}
void add(struct node**head,int n)
{
    struct node*p;
    p=(struct node*)malloc(sizeof(struct node));
    if(p==NULL)
    {
        printf("insuff\n");
        exit(0);
    }
    p->data=n;
    p->next=*head;

    *head=p;
}
void mergesort(struct node** head)
{
    struct node* cur = *head;
    struct node* a;
    struct node* b;


    if ((cur == NULL) || (cur->next == NULL)) {
        return;
    }


    FrontBackSplit(cur, &a, &b);


    mergesort(&a);
    mergesort(&b);


    *head = SortedMerge(a, b);

}
struct node* SortedMerge(struct node* a, struct node* b)
{
    struct node* result = NULL;


    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);


    if (a->data <= b->data) {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}
void FrontBackSplit(struct node* source,struct node** frontRef, struct node** backRef)
{
    struct node* fast;
    struct node* slow;
    slow = source;
    fast = source->next;


    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }


    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}
void random(int l,int h,int n)
{
    int i,r;
    FILE*fp=fopen("input.txt","w");
    for(i=0;i<n;i++)
    {
        r=rand()%(h-l)+l;
        fprintf(fp,"%d  ",r);
    }
    fclose(fp);
}
