#include <stdio.h>
#include <stdlib.h>

int fib(int n);

int main (int argc, char *argv[]){
	int n, ans;

	printf("\n Enter a numer to get it's fibonacci: ");
	scanf("%d", &n);

	ans = fib(n);

	printf("\nThe fibonacci of %d is %d. \n", n, ans);

	return 0;
}

int fib(int n){
	int i;
	int nums[n+1];

	// if (n==0) return 0;
	// if (n==1) return 1;
	nums[0] = 0;
	nums[1] = 1;
	for (i=2; i<=n; i++){
		nums[i] = nums[i-1] + nums[i-2];
	}

	return nums[n];
}
