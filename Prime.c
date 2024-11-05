#include <stdio.h>

int main()
{
    int n;
    printf("Enter number\n");
    scanf("%d",&n);
    int i;
    int isPrime= 1;

    if(n < 2){
        isPrime = 0;                           // if n<2 not prime
    }
    else{

        for(i=2; i < n; i++)                   //to check prime numbers greater than or equal to 2
        {
            if(n % i == 0)
            {
                isPrime = 0;
                break;
            }
        }
    }

    if(isPrime)
        printf("%d is Prime", n);
    else
        printf("%d is not Prime", n);

    return 0;
}
