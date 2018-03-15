/*
* marix.cpp
*
*  Created on: 11 Mar 2018
*      Author: ilona
*/
#include "matrix.hpp"
#include "stdafx.h"


void matrixAdd2x1(double** in1, double** in2, double** out)
{
	for (int i = 0; i < 2; i++)
	{
		out[i][0] = in1[i][0] + in2[i][0];
	}	
} 

void matrixAdd2x2(double** in1, double** in2, double** out)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			out[i][j] = in1[i][j] + in2[i][j];
		}
	}
}

void matrixSub2x2(double** in1, double** in2, double** out)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			out[i][j] = in1[i][j] - in2[i][j];
		}
	}
}

void matrixTrans2x2(double** in, double** out)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
			out[i][j] = in[j][i];
	}
}

void matrix2x2Mult2x1(double** in1, double** in2, double** out)
{
	for (int i = 0; i < 2; i++)
	{
		out[i][0] = 0;
		for (int k = 0; k < 2; k++)
		{
			out[i][0] += in1[i][k] * in2[k][0];
		}		
	}	
}

void matrix2x1Mult1x1(double** in1, double** in2, double** out)
{
	for (int i = 0; i < 2; i++)
	{
		out[i][0] = in1[i][0] * in2[0][0];		
	}	
}

void matrix2x2Mult2x2(double** in1, double** in2, double** out)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			out[i][j] = 0;
			for (int k = 0; k < 2; k++)
			{
				out[i][j] += in1[i][k] * in2[k][j];
			}
		}
	}
}

void matrix1x2Mult2x1(double** in1, double** in2, double** out)
{
	for (int k = 0; k < 2; k++)
	{
		out[0][0] = in1[0][k] * in2[k][0];
	}
}

void matrix1x2Mult2x2(double** in1, double** in2, double** out)
{
	for (int j = 0; j < 2; j++)
	{
		out[0][j] = 0;
		for (int k = 0; k < 2; k++)
		{
			out[0][j] += in1[0][k] * in2[k][j];
		}
	}
}

void matrix2x1Mult2x1(double** in1, double** in2, double** out)
{
	for (int i = 0; i < 2; i++)
	{
		out[i][0] = 0;
		for (int k = 0; k < 2; k++)
		{
			out[i][0] += in1[i][0] * in2[k][0];
		}
	}
}

void matrix2x1Mult1x2(double** in1, double** in2, double** out)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			out[i][j] = in1[i][0] * in2[0][j];
			
		}
	}
}