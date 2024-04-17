#include <stdio.h>

int fibo(int a);
int memo[100] = {0};

int main(){
    int n;
    scanf("%d", &n);
    int f;
    f = fibo(n);
    printf("%d", f);
    return 0;
}
int fibo(int a){
    if(a<2){
        return a;
    }
        if(memo[a] != 0) { // 메모이제이션된 값이 있으면 바로 반환
        return memo[a];
    }
    memo[a] = fibo(a-2) + fibo(a-1);
    return memo[a];
}