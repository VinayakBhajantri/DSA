#include <stdio.h>
int bi(int a[], int l, int r, int x);
void read(int a[],int n);
void d(int a[],int n);
int main()
{

    int a[100];
    int n,t;
    scanf("%d",&n);
    read(a,n);
    printf("Array elements\n");
    d(a,n);
    printf("Enter to be search\n");
    scanf("%d",&t);
   int v= bi(a,0,n-1,t);
   if(v==-1)
   {
       printf("The element %d is not present in an array\n ",t);
   }
   else
   {
       printf("The element %d is  present in the index %d\n ",t,v);
   }

}
int bi(int a[], int l, int r, int x)
{
if (r >= l)
{
int mid = l + (r - l)/2;

if (a[mid] == x) return mid;

if (a[mid] > x) return bi(a, l, mid-1, x);

return bi(a, mid+1, r, x);
}

return -1;
}
void read(int a[],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
          scanf("%d",&a[i]);

    }
}
void d(int a[],int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        printf("%d   ",a[i]);

    }
    printf("\n");
}

