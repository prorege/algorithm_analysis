// #include <stdio.h>

// InsertionSort(A, n){//A라는 배열과 정수 n(원소의 개수) 전달
//     for (i = 2 to n){ //i를 2~n까지 반복
//         key = A[i]; key에 현재 인덱스의 원소 저장
//         j=i-1;      j는 바로 직전 인덱스
//         while(j>0) and (A[j] > key){ 현재 인덱스가 1이 되기 전까지, 동시에 j의 값이 i의 값보다 크다면
//             A[j+1] = A[j]; //i의 값은 j로 내려온다. 왜냐하면 key에 i의 값이 저장되어 있기 때문에 괜찮음.
//             j=j-1; //그리고 j는 또 내려간다. 
//         }
//         A[j+1] = key; //다 끝나면 A[j]가 key보다 더 작다는 말
//     }
// }


/*
A = {2,6,4,3,5} 이렇게 배열이 있다고 하자

n은 5고 i는 2부터 시작한다. 
i=2인 상황
key에는 4가 들어간다. 
j=1이다. 
A[j] = 6이고 이것은 4보다 크기 때문에 while문을 만족,
2번째 인덱스는 이제 4가 아닌 6이 들어간다. 
그리고 j는 0으로 바뀐다. 
지금 상황은 A={2,6,6,3,5}이고 key=4이다. 
다시 while문을 보자.
j=0이기 때문에 while문 조건을 만족하지 못해 탈출한다. 
A[j+1] = A[1] 에는 key값인 4가 들어간다. 
A={2,4,6,3,5}가 된다. 

i=3인 상황도 해보자.
먼저 key에는 3이 저장된다. 
j=2인 상황
A[2]인 6이 key인 3보다 크다. while시작
A[3] = A[2]이기에 A는 2,4,6,6,5이다. 
j=1로 내려감.
다시 while문
A[1]은 4, key값은 3 while시작
A[2] = A[1]. A = {2,4,4,6,5}
j = 0
while탈출
A[1] = 3
A = {2,3,4,6,5}
*/ 