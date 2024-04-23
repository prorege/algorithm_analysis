#include <stdio.h>
#include <limits.h>

unsigned long long fibo(int n);
unsigned long long memo[100];
int main(){
    int n;
    scanf("%d", &n);
    unsigned long long a;
    a = fibo(n);
    printf("%lld", a);
    
    return 0;
}

unsigned long long fibo(int n){
    if(n<2) return n;
    if(memo[n] != 0) return memo[n];
    memo[n] = fibo(n-2) + fibo(n-2);
    return memo[n];
}