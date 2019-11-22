//
//  Matrix.cpp
//  Prac3_Matrix
//
//  Created by Jong-Chul Yoon on 28/04/2019.
//  Copyright © 2019 Jong-Chul Yoon. All rights reserved.
//

#include "Matrix_4.hpp"

Matrix3::Matrix3()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			m_Entry[i][j] = 0.0;
}

Matrix3::Matrix3(const double Entry[3][3])
{
	memcpy(m_Entry, Entry, 9 * sizeof(double));
}

double Matrix3::Get_value(int iRow, int iCol)
{
	return m_Entry[iRow][iCol];
}

void Matrix3::Set_value(int iRow, int iCOl, double value)
{
	m_Entry[iRow][iCOl] = value;
}

Matrix3::Matrix3(const Matrix3& rkMatrix)
{
	memcpy(m_Entry, rkMatrix.m_Entry, 9 * sizeof(double));
}

Matrix3::Matrix3(double fEntry00, double fEntry01, double fEntry02, double fEntry10, double fEntry11, double fEntry12, double fEntry20, double fEntry21, double fEntry22)
{
	m_Entry[0][0] = fEntry00;
	m_Entry[0][1] = fEntry01;
	m_Entry[0][2] = fEntry02;
	m_Entry[1][0] = fEntry10;
	m_Entry[1][1] = fEntry11;
	m_Entry[1][2] = fEntry12;
	m_Entry[2][0] = fEntry20;
	m_Entry[2][1] = fEntry21;
	m_Entry[2][2] = fEntry22;
}

Matrix3 Matrix3::Transpose()
{
	Matrix3 temp;

	for (int iRow = 0; iRow < 3; iRow++)
	{
		for (int iCol = 0; iCol < 3; iCol++)
			temp.Set_value(iRow, iCol, Get_value(iCol, iRow));
	}

	return temp;
}

double Matrix3::Cal_determinant()
{
	double fCofactor00 = m_Entry[1][1] * m_Entry[2][2] - m_Entry[1][2] * m_Entry[2][1];
	double fCofactor10 = m_Entry[1][2] * m_Entry[2][0] - m_Entry[1][0] * m_Entry[2][2];
	double fCofactor20 = m_Entry[1][0] * m_Entry[2][1] - m_Entry[1][1] * m_Entry[2][0];

	double  fDet =
		m_Entry[0][0] * fCofactor00 +
		m_Entry[0][1] * fCofactor10 +
		m_Entry[0][2] * fCofactor20;

	return fDet;

}

bool Matrix3::Inverse(Matrix3* rkMatrix)
{
	if (!Cal_determinant()) return false;

	rkMatrix->Set_value(0, 0, m_Entry[1][1] * m_Entry[2][2] - m_Entry[1][2] * m_Entry[2][1]);
	rkMatrix->Set_value(0, 1, m_Entry[0][2] * m_Entry[2][1] - m_Entry[0][1] * m_Entry[2][2]);
	rkMatrix->Set_value(0, 2, m_Entry[0][1] * m_Entry[1][2] - m_Entry[0][2] * m_Entry[1][1]);
	rkMatrix->Set_value(1, 0, m_Entry[1][2] * m_Entry[2][0] - m_Entry[1][0] * m_Entry[2][2]);
	rkMatrix->Set_value(1, 1, m_Entry[0][0] * m_Entry[2][2] - m_Entry[0][2] * m_Entry[2][0]);
	rkMatrix->Set_value(1, 2, m_Entry[0][2] * m_Entry[1][0] - m_Entry[0][0] * m_Entry[1][2]);
	rkMatrix->Set_value(2, 0, m_Entry[1][0] * m_Entry[2][1] - m_Entry[1][1] * m_Entry[2][0]);
	rkMatrix->Set_value(2, 1, m_Entry[0][1] * m_Entry[2][0] - m_Entry[0][0] * m_Entry[2][1]);
	rkMatrix->Set_value(2, 2, m_Entry[0][0] * m_Entry[1][1] - m_Entry[0][1] * m_Entry[1][0]);

	double fDet =
		m_Entry[0][0] * rkMatrix->Get_value(0, 0) +
		m_Entry[0][1] * rkMatrix->Get_value(1, 0) +
		m_Entry[0][2] * rkMatrix->Get_value(2, 0);

	double fInvDet = 1.0f / fDet;

	for (int iRow = 0; iRow < 3; iRow++)
	{
		for (int iCol = 0; iCol < 3; iCol++)
			rkMatrix->Set_value(iRow, iCol, rkMatrix->Get_value(iRow, iCol)*fInvDet);
	}

	return true;
}

void Matrix3::Print_matrix()
{
	cout << " " << m_Entry[0][0] << ", " << m_Entry[0][1] << ", " << m_Entry[0][2] << endl;
	cout << " " << m_Entry[1][0] << ", " << m_Entry[1][1] << ", " << m_Entry[1][2] << endl;
	cout << " " << m_Entry[2][0] << ", " << m_Entry[2][1] << ", " << m_Entry[2][2] << endl;
}


/// 4th h.w

bool Matrix3::operator== (Matrix3& rkMatrix)            // is_same (두 행렬이 같으면 true 아닐시 false)
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (m_Entry[r][c] != rkMatrix.m_Entry[r][c])
			{
				return false;
			}
		}
	}
	return true;
}
bool Matrix3::operator!= (Matrix3& rkMatrix)           // is_not_same (두 행렬이 다르면 false, 아닐 시 true)
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (m_Entry[r][c] == rkMatrix.m_Entry[r][c])
			{
				return false;
			}
		}
	}
	return true;
}
Matrix3 Matrix3::operator* (Matrix3& rkMatrix)  // Multiply
{
	Matrix3 result;
	int r = 0, c = 0, k = 0;

	for (r = 0; r < 3; r++)
	{
		for (c = 0; c < 3; c++)
		{
			for (k = 0; k < 3; k++)
			{
				result.m_Entry[r][c] += (m_Entry[r][k] * rkMatrix.m_Entry[k][c]);
			}
		}
	}

	return result;

}
Matrix3 Matrix3::operator* (double Scalar) // matrix * scalar
{
	Matrix3 result;
	int r = 0, c = 0;
	for (r = 0; r < 3; r++)
	{
		for (c = 0; c < 3; c++)
		{
			result.m_Entry[r][c] = m_Entry[r][c] * Scalar;
		}
	}
	return result;
}

Matrix3 operator* (double Scalar, Matrix3& rkMatrix) // scalar * matrix
{
	Matrix3 result;

	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			result.Set_value(r, c, (Scalar * rkMatrix.Get_value(r, c)));
		}
	}


	return result;

}

Vector3 Matrix3::operator* (Vector3& rkVector)
{
	Vector3 result;

	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			result.m_value[r] += m_Entry[r][c] * rkVector.m_value[c];
		}
	}

	return result;

}
