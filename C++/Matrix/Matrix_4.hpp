//
//  Matrix.hpp
//  Prac3_Matrix
//
//  Created by Jong-Chul Yoon on 28/04/2019.
//  Copyright © 2019 Jong-Chul Yoon. All rights reserved.
//

#ifndef Matrix_4_hpp
#define Matrix_4_hpp

#include <iostream>
using namespace std;

class Vector3
{
public:
	double m_value[3] = { 0, };
};


class Matrix3
{
public:
	//construction
	Matrix3();
	Matrix3(const double Entry[3][3]);
	Matrix3(const Matrix3& rkMatrix);
	Matrix3(double fEntry00, double fEntry01, double fEntry02,
		double fEntry10, double fEntry11, double fEntry12,
		double fEntry20, double fEntry21, double fEntry22);

	// assignment and comparison
	Matrix3& operator= (const Matrix3& rkMatrix)
	{
		memcpy(m_Entry, rkMatrix.m_Entry, 9 * sizeof(double));
		return *this;
	}

	//operator overloading
	bool operator== (Matrix3& rkMatrix);            // is_same
	bool operator!= (Matrix3& rkMatrix);            // is_not_same
	Matrix3 operator* (Matrix3& rkMatrix);  // Multiply
	Matrix3 operator* (double Scalar); // matrix * scalar

	// matrix * vector [3x3 * 3x1 = 3x1]
	Vector3 operator* (Vector3& rkVector);

	// member access
	double Get_value(int iRow, int iCol);
	void Set_value(int iRow, int iCOl, double value);

	//bool is_same(Matrix3 rkMatrix);
	//bool is_not_same(Matrix3 rkMatrix);

	// operation
	//Matrix3 Multiply(Matrix3 rkMatrix);
	Matrix3 Transpose();

	//inverse operation
	double Cal_determinant(); // ref(https://www.wikihow.com/Find-the-Determinant-of-a-3X3-Matrix)
	bool Inverse(Matrix3* rkMatrix); // ref(https://www.wikihow.com/Find-the-Inverse-of-a-3x3-Matrix)

	void Print_matrix();

private:
	double m_Entry[3][3];
};
// scalar * matrix
Matrix3 operator* (double Scalar, Matrix3& rkMatrix);

#endif /* Matrix_hpp */#pragma once
