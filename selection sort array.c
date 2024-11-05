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
    FILE* fp1=fopen("selsort.txt","w");
    FILE* fp2=fopen("logsel.txt","w");
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


void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(int arr[], int n)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;

        // Swap the found minimum element with the first element
           if(min_idx != i)
            swap(&arr[min_idx], &arr[i]);
    }
}
