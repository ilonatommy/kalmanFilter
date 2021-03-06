// kalmanFilter.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdlib.h>
#include "matrix.hpp"
#include <iostream>

void show(int dim1, int dim2, double** matrix)
{
	for (int i = 0; i < dim1; i++) {
		for (int j = 0; j < dim2; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void fill(int dim1, int dim2, double** matrix)
{
	for (int i = 0; i < dim1; i++) {
		for (int j = 0; j < dim2; j++)
		{
			matrix[i][j] = j + i + 1;
		}
	}
}

void matrixLibTest(int firstDimRow, int firstDimCol, int secDimRow, int secDimCol)
{
	double** matrix1 = (double**)malloc(sizeof(double*) * firstDimRow);
	for (int i = 0; i<firstDimRow; i++)
	{
		matrix1[i] = (double*)malloc(sizeof(*matrix1) *firstDimCol);
	}

	double** matrix2 = (double**)malloc(sizeof(double*)*secDimRow);
	for (int i = 0; i<secDimRow; i++)
	{
		matrix2[i] = (double*)malloc(sizeof(*matrix2) *secDimCol);
	}
	fill(firstDimRow, firstDimCol, matrix1);
	fill(secDimRow, secDimCol, matrix2);

	show(firstDimRow, firstDimCol, matrix1);
	show(secDimRow, secDimCol, matrix2);


	double** result = (double**)malloc(sizeof(double*) * dimensionRow);
	for (int i = 0; i < dimensionRow; i++)
	{
		result[i] = (double*)malloc(sizeof(*result) * secDimCol);
	}
	matrix2x1Mult1x2(matrix1, matrix2, result);
	show(dimensionRow, secDimCol, result);
}

int main()
{	
	
    return 0;
}



