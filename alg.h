#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <string.h>

double mean(double* data, int s, int t){
	double res = 0;
	for(int i = s; i <= t; ++i)res += data[i];
	return res/(double)(t-s+1);
}

double cost(double* data, int s, int t){
	double res = 0;
	double nu = mean(data, s, t);
	for(int i = s; i <= t; ++i)res += (data[i] - nu)*(data[i] - nu);
	return res;
}

int** default_2d_arr(int n_size){
	int** rows = (int **)malloc(sizeof(int*)*n_size);
	for(int i = 0; i < n_size; ++i){
		rows[i] = (int *)malloc(sizeof(int)*n_size);
		for(int j = 0; j < n_size; ++j)rows[i][j] = -1;
	}
	return rows;
}

int* PELT(double* data, int n_size, double penalty){
	double c;
	int temp_size = 0;

	double* F = (double *)malloc(sizeof(double)*(n_size+1)); // Total Cost
	for(int i = 0; i <= n_size; ++i)F[i] = DBL_MAX;
	F[0] = 0;
	
	int** cps = default_2d_arr(n_size + 1); // Change Points


	for(int t = 1; t <= n_size; t++){ // Start Algorithm
		for(int s = 0; s < t; ++s){
			c = cost(data, s, t-1);
			if(F[s] + c + penalty < F[t]){
				F[t] = F[s] + c + penalty;
				if(temp_size > 0){
					memcpy(cps[t], cps[s], temp_size*sizeof(int));
					cps[t][temp_size] = t;
					temp_size ++;
				}
				else{
					cps[t][0] = t;
					temp_size ++;
				}
			}
		}
	}
	free(F);
	return cps[n_size];
}
