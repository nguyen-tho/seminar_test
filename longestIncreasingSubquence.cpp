/* Dynamic Programming C/C++ implementation of LIS problem */
#include <stdio.h>
#include <stdlib.h>
#define MAX 100000
void getInput(int arr[], int&n){
	scanf("%d", &n);
	for(int i =0; i<n;i++){
		scanf("%d", &arr[i]);
	}

}
/* lis() returns the length of the longest increasing
subsequence in arr[] of size n */
void lis(int arr[], int n)
{
	int *lis, *p, i, j, max = 0;
	lis = (int*)malloc(sizeof(int) * n);
    //p = (int*)malloc(sizeof(int) * n);
	/* Initialize LIS values for all indexes */
	for (i = 0; i < n; i++)
		lis[i] = 1;

	/* Compute optimized LIS values in bottom up manner */
	for (i = 1; i < n; i++)
		for (j = 0; j < i; j++)
			if (arr[i] > arr[j] && lis[i] < lis[j] + 1){
                lis[i] = lis[j] + 1;
                //p[i] = j;
            }
				
                

	/* Pick maximum of all LIS values */
	for (i = 0; i < n; i++)
		if (max < lis[i]){
            max = lis[i];
            //p[i] = i;
        }
			

	/* Free memory to avoid memory leak */
	/*
    for(int id =0; id < sizeof(lis); id++ ){
        printf("%d ", lis[id]);
    }
    printf("\n");
    for(int id =0; id < sizeof(lis); id++ ){
        printf("%d ",arr[p[id]]);
    }
    printf("\n");
	*/
	free(lis);

	printf("Length of subquence: %d", max) ;
}

/* Driver program to test above function */
int main()
{
	//int arr[] = { 10, 22, 9, 33, 21, 50, 41, 60 };
	//int n = sizeof(arr) / sizeof(arr[0]);
	int n;
	int arr[MAX];
	getInput(arr,n);
	lis(arr,n);
	return 0;
}
