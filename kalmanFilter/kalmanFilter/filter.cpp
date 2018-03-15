#include "filter.hpp"
#include "matrix.hpp"
#include "stdafx.h"
#include <iostream>
#include <math.h>
#define M_PI			3.14159265358979323846
#define LOOP_DELAY		100
#define INITIAL_DELAY	100

//sensor functions which are used but not written yet
double getGyroZ() {};
double getAccX() {};
double getAccY() {};
void setDelay(int time) {};


double** allocateMatrix(int rows, int cols, double** matrix)
{
	matrix = (double**)malloc(sizeof(double*) * rows);
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = (double*)malloc(sizeof(*matrix) *cols);
	}
	return matrix;
}

void measurementsFilter(void * params)
{
	//declaration and allocation:
	(void)params;

	double dt;

	//matrixes: A 2x2, B 2x1, C 1x2
	double** A = allocateMatrix(2, 2, A);
	double** B = allocateMatrix(2, 1, B);
	double** C = allocateMatrix(1, 2, C); 

	//pPrev, pNext, V 2x2, W 1x1, xPrex 2x1
	double stdDev_v, stdDev_w;
	double** V = allocateMatrix(2, 2, V);
	double** W = allocateMatrix(1, 1, W);
	double** pPrev = allocateMatrix(2, 2, pPrev),
	double** pNext = allocateMatrix(2, 2, pNext);
	double** xPrev = allocateMatrix(2, 1, xPrev);

	//variables for meassurements actualisation
	double** xNext = allocateMatrix(2, 1, xNext);
	double** eps = allocateMatrix(1, 1, eps);
	double** S = allocateMatrix(1, 1, S);
	double** K = allocateMatrix(2, 1, K);
	double** u = allocateMatrix(1, 1, u);
	double** y = allocateMatrix(1, 1, y);
	double accX, accY;

	//variables storing results of aritmetical operations on matrixes
	//Ax, Bu, PCT, Keps, KS, 2x1, AP, AT, APAT 2x2, CP 1x2
	double** Ax = allocateMatrix(2, 1, Ax);
	double** Bu = allocateMatrix(2, 1, Bu);
	double** AP = allocateMatrix(2, 2, AP);
	double** AT = allocateMatrix(2, 2, AT);
	double** APAT = allocateMatrix(2, 2, APAT);
	double** Cx = allocateMatrix(1, 1, Cx);;
	double** CP = allocateMatrix(1, 2, CP);
	double** CPCT = allocateMatrix(1, 1, CPCT);
	double** PCT = allocateMatrix(2, 1, PCT);
	double** S1 = allocateMatrix(1, 1, S1); //inverted S
	double** Keps = allocateMatrix(2, 1, Keps);
	double** KS = allocateMatrix(2, 1, KS);
	double** KSKT = allocateMatrix(2, 2, KSKT);

	//initialisation
	dt = 0.1;

	A[0][0] = 1;
	A[0][1] = -dt;
	A[1][0] = 0;
	A[1][1] = 1;

	B[0][0] = dt;
	B[1][0] = 0;

	C[0][0] = 1;
	C[0][1] = 0;

	stdDev_v = 1;
	stdDev_w = 2;

	V[0][0] = pow(stdDev_v, 2)*dt;
	V[0][1] = 0;
	V[1][0] = 0;
	V[1][1] = V[0][0];

	W[0][0] = pow(stdDev_w,2);

	//initial filter values - identity matrix
	pNext[0][0] = 1;
	pNext[0][1] = 0;
	pNext[1][0] = 0;
	pNext[1][1] = 1;

	//initial delay of the filter (the same as the microcontroler) here
	setDelay(INITIAL_DELAY);

	//accX accY <- get current acceleration here
	accX = getAccX() * 4 / 65535;
	accY = getAccY() * 4 / 65535;
	
	xNext[0][0] = atan(accX / accY) * 180 / M_PI;
	xNext[1][0] = 0;

	//Calculations made every 100ms
	while (1)
	{		
		// x(t+1|t) = Ax(t|t) + Bu(t) 
		u[0][0] = getGyroZ() * 250 / 32768; //rescale data
		matrix2x2Mult2x1(A, xNext, Ax);
		matrix2x1Mult1x1(B, u, Bu);
		matrixAdd2x1(Ax, Bu, xPrev);

		// P(t+1|t) = AP(t|t)A^T + V 
		matrix2x2Mult2x2(A, pNext, AP);
		matrixTrans2x2(A, AT);
		matrix2x2Mult2x2(AP, AT, APAT);
		matrixAdd2x2(APAT, V, pPrev);

		// eps(t) = y(t) - Cx(t|t-1)
		accX = 0;//accX <- get current acceleration here
		accY = 0;//accY <- get current acceleration here
		y[0][0] = atan(accX / accY) * 180 / M_PI;
		matrix1x2Mult2x1(C, xPrev, Cx);
		eps[0][0] = y[0][0] - Cx[0][0];

		// S(t) = CP(t|t-1)C^T + W 
		matrix1x2Mult2x2(C, pPrev, CP);
		matrix1x2Mult2x1(C, CP, CPCT);
		S[0][0] = CPCT[0][0] + W[0][0];

		// K(t) = P(t|t-1)C^TS(t)^-1 
		matrix2x2Mult2x1(pPrev, C, PCT);
		S1[0][0] = 1 / S[0][0];
		matrix2x1Mult1x1(PCT, S1, K);

		// x(t|t) = x(t|t-1) + K(t)eps(t) 
		matrix2x1Mult1x1(K, eps, Keps);
		matrixAdd2x1(xPrev, Keps, xNext);

		// P(t|t) = P(t|t-1) - K(t)S(t)K(t)^T 
		matrix2x1Mult1x1(K, S, KS);
		matrix2x1Mult1x2(KS, K, KSKT);
		matrixSub2x2(pPrev, KSKT, pNext);

		//delay function here (to get new measurements, e.g. 100ms)
		setDelay(LOOP_DELAY);
	}
}

void routeEstimator()
{

}
