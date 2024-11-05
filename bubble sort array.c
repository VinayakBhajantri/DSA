#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
    int l, h, n;
    printf("enter range L-H and size\n");
    scanf("%d%d%d", &l, &h, &n);
    random(l, h, n);
    FILE *fp=fopen("data.txt","r");
    FILE* fp1=fopen("bubsort.txt","w");
    FILE* fp2=fopen("logbub.txt","w");
    if(fp==NULL)
    {
        printf("Error");
        exit(0);
    }
    char temp[10];
    int t;
    int a[100];
    int index=0;
    while(!feof(fp))
    {
        fscanf(fp,"%s",temp);
        t=atoi(temp);
        a[index++]=t;
    }
    clock_t start,stop;
    start=clock();
    sort(a,index);
    stop = clock();

    for(int j=0;j<index;j++)
        fprintf(fp1,"%d\t",a[j]);

    float time_r = (float)(stop - start) / CLOCKS_PER_SEC;
        fprintf(fp2, "selection  %d   %f sec\n", n, time_r);
    return 0;
}

void sort(int a[],int n)
{
    int min;
    int i,j,temp;
    for(i=0;i<n;i++)
    {
        min=i;
        j=i+1;
        while(j<n)
        {
            if(a[j]<a[min])
                min=j;
            j++;
        }
        temp=a[i];
        a[i]=a[min];
        a[min]=temp;
    }

}
void random(int l, int h, int n)
{
    int i, r;
    FILE *fp;
    fp = fopen("data.txt", "w");
    for (i = 0; i < n; i++)
    {
        r = rand() % (h - l) + l;
        fprintf(fp, "%d\t", r);
    }
    fclose(fp);
}
