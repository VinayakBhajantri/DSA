
#include<stdio.h>
void read(int a[],int n);
int fact(int n);
int main()
{
    int a[100];
    int n,i;
    printf("Enter no. of an array\n");
    scanf("%d",&n);
    read(a,n);
    for(i=0;i<n;i++)
        {
            int f=fact(a[i]);
    printf("Fact of %d   :  %d\t",a[i],f);
    printf("\n");
        }
}
void read(int a[],int n)
{
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
}
int fact(int n)
{
    if(n==0)
        return 1;
    int f=fact(n-1);
    return n*f;
}


