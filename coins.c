

#include <stdio.h>


int coins(int *A, int S, int n){

int coins[S+1];
int j;
int i;
int min = 1000000;
int choice[S+1];
coins[0] = 0;
int minChoice;

for(i = 1; i <= S; i++){
    min = 1000000;
    printf("\n%d\n", i);
    for(j = 1; j < n; j++){
        if(A[j] <= i && coins[i-A[j]] < min){
            min = coins[i -A[j]];
            minChoice = j;
        }
    }
    coins[i] = 1 + min;
    choice[i] = minChoice;
}
if(coins[S] == 1000000){
    printf("no solution.");
}else{
    while( S > 0){
        printf("%d, ", A[choice[S]]);
        S -= A[choice[S]];
    }
}


}






int main(){

    int A[5] = {50, 25, 10, 1};
    int n = 4;

    int S = 30;

    coins(A, S, n);

}