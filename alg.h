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
	// Cost Variable Assignment
	double c;

	// Total Cost
	double* F = (double *)malloc(sizeof(double)*(n_size+1));
	for(int i = 0; i <= n_size; ++i)F[i] = DBL_MAX;
	F[0] = -penalty;
	
	// Change Points
	int** cps = default_2d_arr(n_size + 1);

	// Start Algorithm
	for(int t = 1; t <= n_size; t++){
		for(int s = 0; s < t; ++s){
			c = cost(data, s, t-1);
			if(F[s] + c + penalty < F[t]){
				F[t] = F[s] + c + penalty;
				for(int i = 0; i < s+1; i++)cps[t][i] = cps[s][i];
				cps[t][s] = t;
			}
		}
	}
	int* res = cps[n_size];
	
	// Free the memory
	free(F);
	for(int i = 0; i < n_size-1; ++i)free(cps[i]);
	free(cps);

	return res;
}
