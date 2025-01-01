#include<stdio.h>
#include<math.h>
int calculate_value(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        // If exp is odd, multiply the base with the result
        if (exp % 2 == 1)
            result = (result * base) % mod;
        // Square the base and reduce exp by half
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}
int main()
{
    int B,n,M,result;
    printf("Enter the value of B:\n");
    scanf("%d",&B);
    printf("enter the value of power:\n");
    scanf("%d",&n);
    printf("enter the modulo value:\n");
    scanf("%d",&M);
    result = calculate_value(B, n, M);
    printf("Result is %d",result);
    return 0;
}