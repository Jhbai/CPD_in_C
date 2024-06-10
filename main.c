#include <stdio.h>
#include <stdlib.h>
#include "alg.h"
double cost(double* data, int s, int t);
int** default_2d_arr(int n_size);
int* PELT(double* data, int n_size, double penalty);

int main(int argc, char** argv){
	double data[] = {1.0, 2.0, 3.0, 4.0};
	double res = cost(data, 0, 2);
	printf("test ans: %lf\n", res);

	int** matrix = default_2d_arr(5);
	matrix[0][0] = 10;
	printf("test matrix[0][0]: %d\n", matrix[0][0]);

	double ts_data[] = {1.0, 1.0, 1.0, 1.0, 4.0, 4.0, 4.0};
	int* ans = PELT(ts_data, 6, 2);
	for(int i = 0; i < 6; ++i)printf("%d, ", ans[i]);
	printf("\n");
	return 0;
}
