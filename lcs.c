
#include <stdio.h>


int max(int a, int b){
    return a>b ? a:b;
}

int LCSLength(char *x, char *y, int m, int n){
    if(m == 0 || n ==0){
        return 0;
    }

    if(x[m-1] == y[n-1]){
        return 1 + LCSLength(x, y, m-1, n-1);
    }

    return max(LCSLength(x, y, m, n-1), LCSLength(x, y, m-1, n));


}


int main(){

    char str1[10] = "Hello";
    char str2[10] = "Hell";
    int m = 5;
    int n = 4;
    int lcs = LCSLength(str1,str2,m,n);
    printf("The LCS is: %d\n", lcs);
    return 0;

}
