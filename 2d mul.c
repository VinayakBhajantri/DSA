#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define R 10
#define C 10

void random(int l,int h,int r,int c);
void display(int a[R][C],int r,int c);
void read(int a[R][C],int t,int c);
void mult(int a[R][C],int r1,int c1,int b[R][C],int r2,int c2,int res[R][C]);
void multi(int a[R][C],int r1,int c1,int b[R][C],int r2,int c2,int res[R][C]);
void disp(int a[R][C],int r,int c);


int main()
{
    int l1,h1,l2,h2,r1,c1,r2,c2;
    int a[R][C];
    int b[R][C];
    int res[R][C]={0};

    printf("Enter lower,upper limit for 1st matrix:\n ");
    scanf("%d%d",&l1,&h1);
    printf("Enter row and column of 1st matrix:\n");
    scanf("%d%d",&r1,&c1);
    random(l1,h1,r1,c1);
    read(a,r1,c1);
    printf("      The 1st matrix is    \n");

    display(a,r1,c1);
    printf("Enter lower,upper limit for 2nd matrix:\n ");
    scanf("%d%d",&l2,&h2);
    printf("Enter row and column of 2nd matrix:\n");
    scanf("%d%d",&r2,&c2);
    if(c1!=r2)
    {
        printf("it can't be done\n");
        exit(0);
    }

    random(l2,h2,r2,c2);
    read(b,r2,c2);

     printf("      The 2nd matrix is    \n");
    display(b,r2,c2);
    multi(a,r1,c1,b,r2,c2,res);

}
void multi(int a[R][C],int r1,int c1,int b[R][C],int r2,int c2,int res[R][C])
{
    FILE* fp=fopen("out.txt","w");;
    clock_t start,stop;
    start=clock();
    mult(a,r1,c1,b,r2,c2,res);

    int i,j;
    for(i=0;i<r1;i++)
    {
        for(j=0;j<c2;j++)
        {

            fprintf(fp,"%d  ",res[i][j]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"\n");
    stop=clock();
    printf("\n The resul matric is :\n");
   display(res,r1,c2);
    float time_r=(float)(stop-start) / CLOCKS_PER_SEC;
    fprintf(fp,"For the %d rows and %d columns transpose taken the time as %f\n",r1,c2,time_r);

}
void mult(int a[R][C],int r1,int c1,int b[R][C],int r2,int c2,int res[R][C])
{
    int i,j,k;
    for(i=0;i<r1;i++)
    {
        for(j=0;j<c2;j++)
        {
            for(k=0;k<c1;k++)
            {
                res[i][j]=res[i][j]+a[i][k]*b[k][j];
            }
        }
    }
}
void display(int a[R][C],int r,int c)
{
    printf("\n");
    int i,j;
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            printf("%d  ",a[i][j]);
        }
        printf("\n");
    }
}
void random(int l,int h,int r,int c)
{
    FILE*fp=fopen("give.txt","w");
    int i,j,t;
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            t=rand()%(h-l)+l;
            fprintf(fp,"%d ",t);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"\n\n\n\n -----------");
    fclose(fp);
}

void read(int a[R][C],int t,int c)
{
    int i,j,x;
    FILE *fp;
    fp = fopen("give.txt", "r");
    for (i = 0; i < t; i++)
    {
        for(j=0;j<c;j++)
            {
              fscanf(fp, "%d", &x);
              a[i][j] = x;

            }
}
      fclose(fp);
}
