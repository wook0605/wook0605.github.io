//
//  main.cpp
//  Prac3_Matrix
//
//  Created by Jong-Chul Yoon on 28/04/2019.
//  Copyright © 2019 Jong-Chul Yoon. All rights reserved.
//

#include "Matrix_4.hpp"

int main()
{
	double Id[3][3] = { 1.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0 };

	Matrix3 Identity(Id);
	Matrix3 M1(1, 2, 3, 0, 1, 4, 5, 6, 0);

	Matrix3 M2;

	if (!M1.Inverse(&M2)) cout << "sigular matrix" << endl;

	Matrix3 result = M1 * M2;

	if (result == Identity)
	{
		cout << "Good Job!!" << endl;
		result = result * 3;
		result = (1 / 3.0)*result;
		result.Print_matrix();
	}

	if (result != Identity)
	{
		cout << "I think you mad a mistake" << endl;
	}

	///// Use the Matrix class to solve the simultaneous equations as follows:
	cout << " 3x+2y-1z=10 " << endl;
	cout << " 2x+3y+3z=2  " << endl;
	cout << " 5x-2y-2z=-1 " << endl;

	Vector3 value;

		Matrix3 M3 = { 3,2,-1,2,3,3,5,-2,-2 };
		Matrix3 M4;
		Vector3 V1 = { 10, 2, -1 };
		M3.Inverse(&M4);

		for (int r = 0; r < 3; r++)
		{
			for (int c = 0; c < 3; c++)
			{
				value.m_value[r] += M4.Get_value(r,c) * V1.m_value[c];
			}
			
		}

	cout << "solving....." << endl;
	cout << "x=" << value.m_value[0] << endl;
	cout << "y=" << value.m_value[1] << endl;
	cout << "z=" << value.m_value[2] << endl;

	return 0;
}