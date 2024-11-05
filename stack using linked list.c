#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STACK_SIZE 100


struct node
{
  int data;
  struct node*next;
};
struct node*head=NULL;
void push(FILE *,int n);
void pop(FILE*);
//void display(Stack* stack);
void random(int l, int h, int n);
void log_push(FILE* log_file, int item);
void log_pop(FILE* log_file, int item);
void log_operation(FILE* log_file, const char* operation);

int main()
{
  int l, h, n;
    printf("enter range L-H and size\n");
    scanf("%d%d%d", &l, &h, &n);
    random(l, h, n);
    FILE*fp=fopen("stacks.txt","r");
    int r;
    int i;

    FILE*fp1=fopen("log_push1.txt","w");
    FILE *fp2=fopen("log_pop1.txt","w");

    FILE*fp4=fopen("log_push1 of time.txt","w");
    FILE*fp5=fopen("log_pop1 of time.txt","w");

    clock_t start,stop;

           start = clock();
       for(i=0;i<n;i++)
         {
             fscanf(fp,"%d",&r);
               push(fp1,r);
         }
         stop=clock();
         float time_l = (float)(stop - start) / CLOCKS_PER_SEC;
               fprintf(fp1,"No. of push operations   %d\n",n);
               fprintf(fp4,"Time required for push operations %f sec\n",time_l);
               int s;
               scanf("%d",&s);
               start=clock();
               for(i=0;i<s;i++)
               {
                   pop(fp2);
               }
               stop=clock();
              float time_g=(float)(stop-start)/CLOCKS_PER_SEC;
               fprintf(fp2,"No. of pop operations   %d\n",s);
               fprintf(fp5,"Time required for pop operations %f sec\n",time_g);




remove(fp);
FILE*fp8=fopen("stacks.txt","w");
fclose(fp1);
fclose(fp2);

}
void pop(FILE*fp2)
{

    struct node*temp;
    if(head == NULL)
        printf("Stack is Empty\n");
    else
    {
        printf("Poped element = %d\n", head->data);
        int r=head->data;
        fprintf(fp2,"Pop  %d\n",r);


        temp = head;


        head = head->next;


        free(temp);
    }
}
void push(FILE *fp,int n)
{

    struct node*p=malloc(sizeof(struct node));
    p->data=n;
    p->next=head;
    head=p;
    fprintf(fp,"Push    %d\n",head->data);
}
void random(int l, int h, int n)
{
    int i, r;
    FILE *fp;
    fp = fopen("stacks.txt", "w");
    for (i = 0; i < n; i++)
    {
        r = rand() % (h - l) + l;
        fprintf(fp, "%d\t", r);
    }
    fclose(fp);
}



