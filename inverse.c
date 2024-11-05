#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define R 10
#define C 10

void random(int l,int h,int r,int c);
void display(int a[R][C],int r,int c);
void read(int a[R][C],int t,int c);
void tran(int a[R][C],int r,int c,int b[R][C]);
void disp(int a[R][C],int r,int c);
void io(int a[R][C],int b[R][C],int r,int c);

int main()
{
    int l,h,r,c;

    printf("Enter lower,upper limit:\n ");
    scanf("%d%d",&l,&h);
    printf("Enter row and column:\n");
    scanf("%d%d",&r,&c);
    random(l,h,r,c);

    int a[R][C];
    int b[R][C];
    read(a,r,c);
    display(a,r,c);
    io(a,b,r,c);





}
void io(int a[R][C],int b[R][C],int r,int c)
{
    FILE* fp=fopen("out.txt","w");;
    clock_t start,stop;
    start=clock();
    tran(a,r,c,b);

    int i,j;
    for(i=0;i<c;i++)
    {
        for(j=0;j<r;j++)
        {

            fprintf(fp,"%d  ",b[i][j]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"\n");
    stop=clock();
    display(b,c,r);
    float time_r=(float)(stop-start)/CLOCKS_PER_SEC;
    fprintf(fp,"For the %d rows and %d columns transpose taken the time as %f\n",r,c,time_r);

}

void tran(int a[R][C],int r,int c,int b[R][C])
{
    int i,j;

    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            b[j][i]=a[i][j];

        }

    }

}
void display(int a[R][C],int r,int c)
{
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


