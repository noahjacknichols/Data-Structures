#include <stdio.h>


int max(int a, int b){
    return(a > b) ? a:b;
}

int sum(int *A, int n){
    int i;
    int j;
    int sum[n];
    int choice[n];
    for(i = 0; i < n; i++){
        choice[i] = 0;
    }
    sum[0] = A[0];
    sum[1] = max(sum[0], A[1]);
    for(i = 2; i < n; i++){
        choice[i] = (sum[i-2] + A[i] > sum[i-1]) ? A[i]:0;
        if(choice[i] == A[i]){
            for(j = i-1; j > 0; j-=2){
                choice[j] = 0;
                choice[j-1] = A[j-1]; 
            }
        }
        
        sum[i] = max(sum[i-2] + A[i], sum[i-1]);

    }
    for(i = 0; i < n; i++){
        printf("%d,", choice[i]);
    }
    printf("the sum is: %d", sum[n-1]);
}

 


int main(){

    int A[7] = {4, 0, 0, 11};
    int n = 4;
    sum(A, n);

  
}
