#include<stdio.h>
#include<stdlib.h>
  int top;
    int items[100];


void random(int l,int h,int n);
void pop(FILE* fp);
void push(FILE* fp,int n);

int main()
{

    top=-1;
    int l=1,h=60,n=8,p=0,po=0,r;
    random(l,h,n);
    FILE* fp=fopen("input.txt","r");
    FILE* fp1=fopen("push.txt","w");
    FILE* fp2=fopen("pop.txt","w");

    int ch;
    while(1)
    {
        scanf("%d",&ch);
        switch(ch)

             {
                 case 1:fscanf(fp,"%d",&r);

                    push(fp1,r);

                    p++;

                    break;
             case 2:pop(fp2);
                    po++;
                    break;
             case 3:fprintf(fp1,"Pushed elements :%d \n",p);
    fprintf(fp2,"Poped elements :%d\n",po);
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    case 4:exit(0);
             }
    }

}
void pop(FILE* fp)
{

    int r=items[top];

    top--;
    fprintf(fp,"Pop %d\n",r);
}
void push(FILE* fp,int n)
{

    top++;


    items[top]=n;

    fprintf(fp,"Push %d\n",n);
}
void random(int l,int h,int n)
{
    FILE* fp=fopen("input.txt","w");
    for(int i=0;i<n;i++)
    {
        int r=rand()%(h-l)+l;
        fprintf(fp,"%d    ",r);
    }
    fclose(fp);
}
