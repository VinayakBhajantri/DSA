#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void random(int l, int h, int n);
void merge(int arr[], int l, int m, int r);
void sort(int arr[], int l, int r);

int main()
{
    int l, h, n;
    printf("enter range L-H and size\n");
    scanf("%d%d%d", &l, &h, &n);
    random(l, h, n);
    FILE *fp=fopen("data.txt","r");
    FILE* fp1=fopen("sortmerge.txt","w");
    FILE* fp2=fopen("logmerge.txt","w");
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
    sort(a,0,index);
    stop = clock();

    for(int j=0;j<index;j++)
        fprintf(fp1,"%d\t",a[j]);

    float time_r = (float)(stop - start) / CLOCKS_PER_SEC;
        fprintf(fp2, "selection  %d   %f sec\n", n, time_r);
    return 0;
}
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];


    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }


    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }


    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void sort(int arr[], int l, int r)
{
    if (l < r) {

        int m = l + (r - l) / 2;

        // Sort first and second halves
        sort(arr, l, m);
        sort(arr, m + 1, r);

        merge(arr, l, m, r);
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

