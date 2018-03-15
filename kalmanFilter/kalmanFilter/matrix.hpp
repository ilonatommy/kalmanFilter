#pragma once
/*
* matrix.hpp
*
*  Created on: 11 Mar 2018
*      Author: ilona
*/

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

void matrixAdd2x1(double** in1, double** in2, double** out);
void matrixAdd2x2(double** in1, double** in2, double** out);
void matrixSub2x2(double** in1, double** in2, double** out);
void matrixTrans2x2(double** in, double** out);
void matrix2x2Mult2x1(double** in1, double** in2, double** out);
void matrix2x1Mult1x1(double** in1, double** in2, double** out);
void matrix2x2Mult2x2(double** in1, double** in2, double** out);
void matrix1x2Mult2x1(double** in1, double** in2, double** out);
void matrix1x2Mult2x2(double** in1, double** in2, double** out);
void matrix2x1Mult2x1(double** in1, double** in2, double** out);
void matrix2x1Mult1x2(double** in1, double** in2, double** out);

#endif /* MATRIX_HPP_ */
