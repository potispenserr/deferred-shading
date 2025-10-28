#pragma once
#include "Vector4D.h"
#include "math.h"
#include <iostream>
///
///\copyright{
///This file is part of Lab 1.
///
///Lab 1 is free software : you can redistribute itand /or modify
///it under the terms of the GNU General Public License as published by
///the Free Software Foundation, either version 3 of the License, or
///(at your option) any later version.
///
///Lab 1 is distributed in the hope that it will be useful,
///but WITHOUT ANY WARRANTY; without even the implied warranty of
///MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
///GNU General Public License for more details.
///
///You should have received a copy of the GNU General Public License
///along with Lab 1.If not, see < https://www.gnu.org/licenses/>.}

#define PI           3.14159265358979323846 

class Matrix4D
{

public:
	Vector4D mxarr[4];

	// constructors
	Matrix4D()
	{
		mxarr[0][0] = 1.0f;
		mxarr[0][1] = 0.0f;
		mxarr[0][2] = 0.0f;
		mxarr[0][3] = 0.0f;

		mxarr[1][0] = 0.0f;
		mxarr[1][1] = 1.0f;
		mxarr[1][2] = 0.0f;
		mxarr[1][3] = 0.0f;

		mxarr[2][0] = 0.0f;
		mxarr[2][1] = 0.0f;
		mxarr[2][2] = 1.0f;
		mxarr[2][3] = 0.0f;

		mxarr[3][0] = 0.0f;
		mxarr[3][1] = 0.0f;
		mxarr[3][2] = 0.0f;
		mxarr[3][3] = 1.0f;

	}

	Matrix4D(float f00, float f01, float f02, float f03, float f10, float f11, float f12, float f13, float f20, float f21, float f22, float f23, float f30, float f31, float f32, float f33)
	{
		mxarr[0][0] = f00;
		mxarr[0][1] = f01;
		mxarr[0][2] = f02;
		mxarr[0][3] = f03;

		mxarr[1][0] = f10;
		mxarr[1][1] = f11;
		mxarr[1][2] = f12;
		mxarr[1][3] = f13;

		mxarr[2][0] = f20;
		mxarr[2][1] = f21;
		mxarr[2][2] = f22;
		mxarr[2][3] = f23;

		mxarr[3][0] = f30;
		mxarr[3][1] = f31;
		mxarr[3][2] = f32;
		mxarr[3][3] = f33;


	}




	Matrix4D(Matrix4D& m)
	{


		mxarr[0][0] = m.mxarr[0][0];
		mxarr[0][1] = m.mxarr[0][1];
		mxarr[0][2] = m.mxarr[0][2];
		mxarr[0][3] = m.mxarr[0][3];

		mxarr[1][0] = m.mxarr[1][0];
		mxarr[1][1] = m.mxarr[1][1];
		mxarr[1][2] = m.mxarr[1][2];
		mxarr[1][3] = m.mxarr[1][3];

		mxarr[2][0] = m.mxarr[2][0];
		mxarr[2][1] = m.mxarr[2][1];
		mxarr[2][2] = m.mxarr[2][2];
		mxarr[2][3] = m.mxarr[2][3];

		mxarr[3][0] = m.mxarr[3][0];
		mxarr[3][1] = m.mxarr[3][1];
		mxarr[3][2] = m.mxarr[3][2];
		mxarr[3][3] = m.mxarr[3][3];


	}

	///
	///getters 
	///
	float get(int i, int j) {
		if (i >= 4 || j >= 4) {
			throw std::out_of_range("Index out of range");
		}
		return mxarr[i][j];
	}

	float x() {
		return mxarr[0][3];
	}
	float y() {
		return mxarr[1][3];
	}
	float z() {
		return mxarr[2][3];
	}

	///
	///setters
	///
	void set(int i, int j, float val) {
		if (i >= 4 || j >= 4) {
			throw std::out_of_range("Index out of range");
		}
		mxarr[i][j] = val;
	}


	void reset()
	{
		mxarr[0][0] = 1.0f;
		mxarr[0][1] = 0.0f;
		mxarr[0][2] = 0.0f;
		mxarr[0][3] = 0.0f;

		mxarr[1][0] = 0.0f;
		mxarr[1][1] = 1.0f;
		mxarr[1][2] = 0.0f;
		mxarr[1][3] = 0.0f;

		mxarr[2][0] = 0.0f;
		mxarr[2][1] = 0.0f;
		mxarr[2][2] = 1.0f;
		mxarr[2][3] = 0.0f;

		mxarr[3][0] = 0.0f;
		mxarr[3][1] = 0.0f;
		mxarr[3][2] = 0.0f;
		mxarr[3][3] = 1.0f;
	}

	///
	///Printing function
	///
	void print() {
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
			{
				std::cout << " " << mxarr[i][j];
				if (j == 3)
					std::cout << "\n" << "\n";
			}
		std::cout << "--------" << "\n";
	}






	///
	///matrix multiplication overload
	///
	Matrix4D operator*(Matrix4D& m)
	{
		Matrix4D newmx;
		newmx.mxarr[0][0] = mxarr[0][0] * m.mxarr[0][0] + mxarr[0][1] * m.mxarr[1][0] + mxarr[0][2] * m.mxarr[2][0] + mxarr[0][3] * m.mxarr[3][0];
		newmx.mxarr[0][1] = mxarr[0][0] * m.mxarr[0][1] + mxarr[0][1] * m.mxarr[1][1] + mxarr[0][2] * m.mxarr[2][1] + mxarr[0][3] * m.mxarr[3][1];
		newmx.mxarr[0][2] = mxarr[0][0] * m.mxarr[0][2] + mxarr[0][1] * m.mxarr[1][2] + mxarr[0][2] * m.mxarr[2][2] + mxarr[0][3] * m.mxarr[3][2];
		newmx.mxarr[0][3] = mxarr[0][0] * m.mxarr[0][3] + mxarr[0][1] * m.mxarr[1][3] + mxarr[0][2] * m.mxarr[2][3] + mxarr[0][3] * m.mxarr[3][3];
		newmx.mxarr[1][0] = mxarr[1][0] * m.mxarr[0][0] + mxarr[1][1] * m.mxarr[1][0] + mxarr[1][2] * m.mxarr[2][0] + mxarr[1][3] * m.mxarr[3][0];
		newmx.mxarr[1][1] = mxarr[1][0] * m.mxarr[0][1] + mxarr[1][1] * m.mxarr[1][1] + mxarr[1][2] * m.mxarr[2][1] + mxarr[1][3] * m.mxarr[3][1];
		newmx.mxarr[1][2] = mxarr[1][0] * m.mxarr[0][2] + mxarr[1][1] * m.mxarr[1][2] + mxarr[1][2] * m.mxarr[2][2] + mxarr[1][3] * m.mxarr[3][2];
		newmx.mxarr[1][3] = mxarr[1][0] * m.mxarr[0][3] + mxarr[1][1] * m.mxarr[1][3] + mxarr[1][2] * m.mxarr[2][3] + mxarr[1][3] * m.mxarr[3][3];
		newmx.mxarr[2][0] = mxarr[2][0] * m.mxarr[0][0] + mxarr[2][1] * m.mxarr[1][0] + mxarr[2][2] * m.mxarr[2][0] + mxarr[2][3] * m.mxarr[3][0];
		newmx.mxarr[2][1] = mxarr[2][0] * m.mxarr[0][1] + mxarr[2][1] * m.mxarr[1][1] + mxarr[2][2] * m.mxarr[2][1] + mxarr[2][3] * m.mxarr[3][1];
		newmx.mxarr[2][2] = mxarr[2][0] * m.mxarr[0][2] + mxarr[2][1] * m.mxarr[1][2] + mxarr[2][2] * m.mxarr[2][2] + mxarr[2][3] * m.mxarr[3][2];
		newmx.mxarr[2][3] = mxarr[2][0] * m.mxarr[0][3] + mxarr[2][1] * m.mxarr[1][3] + mxarr[2][2] * m.mxarr[2][3] + mxarr[2][3] * m.mxarr[3][3];
		newmx.mxarr[3][0] = mxarr[3][0] * m.mxarr[0][0] + mxarr[3][1] * m.mxarr[1][0] + mxarr[3][2] * m.mxarr[2][0] + mxarr[3][3] * m.mxarr[3][0];
		newmx.mxarr[3][1] = mxarr[3][0] * m.mxarr[0][1] + mxarr[3][1] * m.mxarr[1][1] + mxarr[3][2] * m.mxarr[2][1] + mxarr[3][3] * m.mxarr[3][1];
		newmx.mxarr[3][2] = mxarr[3][0] * m.mxarr[0][2] + mxarr[3][1] * m.mxarr[1][2] + mxarr[3][2] * m.mxarr[2][2] + mxarr[3][3] * m.mxarr[3][2];
		newmx.mxarr[3][3] = mxarr[3][0] * m.mxarr[0][3] + mxarr[3][1] * m.mxarr[1][3] + mxarr[3][2] * m.mxarr[2][3] + mxarr[3][3] * m.mxarr[3][3];
		return newmx;
	}

	///
	///matrix vector multiplication overload
	///
	Vector4D operator*(Vector4D& vector)
	{
		float x = mxarr[0][0] * vector.x() + mxarr[0][1] * vector.y() + mxarr[0][2] * vector.z() + mxarr[0][3] * vector.w();
		float y = mxarr[1][0] * vector.x() + mxarr[1][1] * vector.y() + mxarr[1][2] * vector.z() + mxarr[1][3] * vector.w();
		float z = mxarr[2][0] * vector.x() + mxarr[2][1] * vector.y() + mxarr[2][2] * vector.z() + mxarr[2][3] * vector.w();
		float w = mxarr[3][0] * vector.x() + mxarr[3][1] * vector.y() + mxarr[3][2] * vector.z() + mxarr[3][3] * vector.w();
		Vector4D newVector(x, y, z, w);
		return newVector;
	}
	///
	///Array overload
	///
	Vector4D& operator [] (int i) {
		//return *(Vector4D*)(&mxarr[i]);
		//return vecarray[i];
		return mxarr[i];
	}



	///
	///assignment overload
	///
	void operator=(Matrix4D m)
	{
		mxarr[0][0] = m.mxarr[0][0];
		mxarr[0][1] = m.mxarr[0][1];
		mxarr[0][2] = m.mxarr[0][2];
		mxarr[0][3] = m.mxarr[0][3];

		mxarr[1][0] = m.mxarr[1][0];
		mxarr[1][1] = m.mxarr[1][1];
		mxarr[1][2] = m.mxarr[1][2];
		mxarr[1][3] = m.mxarr[1][3];

		mxarr[2][0] = m.mxarr[2][0];
		mxarr[2][1] = m.mxarr[2][1];
		mxarr[2][2] = m.mxarr[2][2];
		mxarr[2][3] = m.mxarr[2][3];


		mxarr[3][0] = m.mxarr[3][0];
		mxarr[3][1] = m.mxarr[3][1];
		mxarr[3][2] = m.mxarr[3][2];
		mxarr[3][3] = m.mxarr[3][3];
	}

	///Creates temp matrix to store transpose 
	///Assigns the transpose to referenced matrix 
	///
	void transpose(Matrix4D& m)
	{
		Matrix4D transp;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				transp.mxarr[i][j] = m.mxarr[j][i];
			}
		}
		m = transp;
	}

	///Inverts matrix, calculates determinant and assigns the inverse by reference
	///Throws an exception if determinant is 0
	void invert(Matrix4D& m) {
		Matrix4D inv;
		inv.mxarr[0][0] = m.mxarr[1][1] * m.mxarr[2][2] * m.mxarr[3][3] -
			m.mxarr[1][1] * m.mxarr[2][3] * m.mxarr[3][2] -
			m.mxarr[2][1] * m.mxarr[1][2] * m.mxarr[3][3] +
			m.mxarr[2][1] * m.mxarr[1][3] * m.mxarr[3][2] +
			m.mxarr[3][1] * m.mxarr[1][2] * m.mxarr[2][3] -
			m.mxarr[3][1] * m.mxarr[1][3] * m.mxarr[2][2];

		inv.mxarr[1][0] = -m.mxarr[1][0] * m.mxarr[2][2] * m.mxarr[3][3] +
			m.mxarr[1][0] * m.mxarr[2][3] * m.mxarr[3][2] +
			m.mxarr[2][0] * m.mxarr[1][2] * m.mxarr[3][3] -
			m.mxarr[2][0] * m.mxarr[1][3] * m.mxarr[3][2] -
			m.mxarr[3][3] * m.mxarr[1][2] * m.mxarr[2][3] +
			m.mxarr[3][0] * m.mxarr[1][3] * m.mxarr[2][2];

		inv.mxarr[2][0] = m.mxarr[1][0] * m.mxarr[2][1] * m.mxarr[3][3] -
			m.mxarr[1][0] * m.mxarr[2][3] * m.mxarr[3][1] -
			m.mxarr[2][0] * m.mxarr[1][1] * m.mxarr[3][3] +
			m.mxarr[2][0] * m.mxarr[1][3] * m.mxarr[3][1] +
			m.mxarr[3][0] * m.mxarr[1][1] * m.mxarr[2][3] -
			m.mxarr[3][0] * m.mxarr[1][3] * m.mxarr[2][1];

		inv.mxarr[3][0] = -m.mxarr[1][0] * m.mxarr[2][1] * m.mxarr[3][2] +
			m.mxarr[1][0] * m.mxarr[2][2] * m.mxarr[3][1] +
			m.mxarr[2][0] * m.mxarr[1][1] * m.mxarr[3][2] -
			m.mxarr[2][0] * m.mxarr[1][2] * m.mxarr[3][1] -
			m.mxarr[3][0] * m.mxarr[1][1] * m.mxarr[2][2] +
			m.mxarr[3][0] * m.mxarr[1][2] * m.mxarr[2][1];

		inv.mxarr[0][1] = -m.mxarr[0][1] * m.mxarr[2][2] * m.mxarr[3][3] +
			m.mxarr[0][1] * m.mxarr[2][3] * m.mxarr[3][2] +
			m.mxarr[2][1] * m.mxarr[0][2] * m.mxarr[3][3] -
			m.mxarr[2][1] * m.mxarr[0][3] * m.mxarr[3][2] -
			m.mxarr[3][1] * m.mxarr[0][2] * m.mxarr[2][3] +
			m.mxarr[3][1] * m.mxarr[0][3] * m.mxarr[2][2];

		inv.mxarr[1][1] = m.mxarr[0][0] * m.mxarr[2][2] * m.mxarr[3][3] -
			m.mxarr[0][0] * m.mxarr[2][3] * m.mxarr[3][2] -
			m.mxarr[2][0] * m.mxarr[0][2] * m.mxarr[3][3] +
			m.mxarr[2][0] * m.mxarr[0][3] * m.mxarr[3][2] +
			m.mxarr[3][0] * m.mxarr[0][2] * m.mxarr[2][3] -
			m.mxarr[3][0] * m.mxarr[0][3] * m.mxarr[2][2];

		inv.mxarr[2][1] = -m.mxarr[0][0] * m.mxarr[2][1] * m.mxarr[3][3] +
			m.mxarr[0][0] * m.mxarr[2][3] * m.mxarr[3][1] +
			m.mxarr[2][0] * m.mxarr[0][1] * m.mxarr[3][3] -
			m.mxarr[2][0] * m.mxarr[0][3] * m.mxarr[3][1] -
			m.mxarr[3][0] * m.mxarr[0][1] * m.mxarr[2][3] +
			m.mxarr[3][0] * m.mxarr[0][3] * m.mxarr[2][1];

		inv.mxarr[3][1] = m.mxarr[0][0] * m.mxarr[2][1] * m.mxarr[3][2] -
			m.mxarr[0][0] * m.mxarr[2][2] * m.mxarr[3][1] -
			m.mxarr[2][0] * m.mxarr[0][1] * m.mxarr[3][2] +
			m.mxarr[2][0] * m.mxarr[0][2] * m.mxarr[3][1] +
			m.mxarr[3][0] * m.mxarr[0][1] * m.mxarr[2][2] -
			m.mxarr[3][0] * m.mxarr[0][2] * m.mxarr[2][1];

		inv.mxarr[0][2] = m.mxarr[0][1] * m.mxarr[1][2] * m.mxarr[3][3] -
			m.mxarr[0][1] * m.mxarr[1][3] * m.mxarr[3][2] -
			m.mxarr[1][1] * m.mxarr[0][2] * m.mxarr[3][3] +
			m.mxarr[1][1] * m.mxarr[0][3] * m.mxarr[3][2] +
			m.mxarr[3][1] * m.mxarr[0][2] * m.mxarr[1][3] -
			m.mxarr[3][1] * m.mxarr[0][3] * m.mxarr[1][2];

		inv.mxarr[1][2] = -m.mxarr[0][0] * m.mxarr[1][2] * m.mxarr[3][3] +
			m.mxarr[0][0] * m.mxarr[1][3] * m.mxarr[3][2] +
			m.mxarr[1][0] * m.mxarr[0][2] * m.mxarr[3][3] -
			m.mxarr[1][0] * m.mxarr[0][3] * m.mxarr[3][2] -
			m.mxarr[3][0] * m.mxarr[0][2] * m.mxarr[1][3] +
			m.mxarr[3][0] * m.mxarr[0][3] * m.mxarr[1][2];

		inv.mxarr[2][2] = m.mxarr[0][0] * m.mxarr[1][1] * m.mxarr[3][3] -
			m.mxarr[0][0] * m.mxarr[1][3] * m.mxarr[3][1] -
			m.mxarr[1][0] * m.mxarr[0][1] * m.mxarr[3][3] +
			m.mxarr[1][0] * m.mxarr[0][3] * m.mxarr[3][1] +
			m.mxarr[3][0] * m.mxarr[0][1] * m.mxarr[1][3] -
			m.mxarr[3][0] * m.mxarr[0][3] * m.mxarr[1][1];

		inv.mxarr[3][2] = -m.mxarr[0][0] * m.mxarr[1][1] * m.mxarr[3][2] +
			m.mxarr[0][0] * m.mxarr[1][2] * m.mxarr[3][1] +
			m.mxarr[1][0] * m.mxarr[0][1] * m.mxarr[3][2] -
			m.mxarr[1][0] * m.mxarr[0][2] * m.mxarr[3][1] -
			m.mxarr[3][0] * m.mxarr[0][1] * m.mxarr[1][2] +
			m.mxarr[3][0] * m.mxarr[0][2] * m.mxarr[1][1];

		inv.mxarr[0][3] = -m.mxarr[0][1] * m.mxarr[1][2] * m.mxarr[2][3] +
			m.mxarr[0][1] * m.mxarr[1][3] * m.mxarr[2][2] +
			m.mxarr[1][1] * m.mxarr[0][2] * m.mxarr[2][3] -
			m.mxarr[1][1] * m.mxarr[0][3] * m.mxarr[2][2] -
			m.mxarr[2][1] * m.mxarr[0][2] * m.mxarr[1][3] +
			m.mxarr[2][1] * m.mxarr[0][3] * m.mxarr[1][2];

		inv.mxarr[1][3] = m.mxarr[0][0] * m.mxarr[1][2] * m.mxarr[2][3] -
			m.mxarr[0][0] * m.mxarr[1][3] * m.mxarr[2][2] -
			m.mxarr[1][0] * m.mxarr[0][2] * m.mxarr[2][3] +
			m.mxarr[1][0] * m.mxarr[0][3] * m.mxarr[2][2] +
			m.mxarr[2][0] * m.mxarr[0][2] * m.mxarr[1][3] -
			m.mxarr[2][0] * m.mxarr[0][3] * m.mxarr[1][2];

		inv.mxarr[2][3] = -m.mxarr[0][0] * m.mxarr[1][1] * m.mxarr[2][3] +
			m.mxarr[0][0] * m.mxarr[1][3] * m.mxarr[2][1] +
			m.mxarr[1][0] * m.mxarr[0][1] * m.mxarr[2][3] -
			m.mxarr[1][0] * m.mxarr[0][3] * m.mxarr[2][1] -
			m.mxarr[2][0] * m.mxarr[0][1] * m.mxarr[1][3] +
			m.mxarr[2][0] * m.mxarr[0][3] * m.mxarr[1][1];

		inv.mxarr[3][3] = m.mxarr[0][0] * m.mxarr[1][1] * m.mxarr[2][2] -
			m.mxarr[0][0] * m.mxarr[1][2] * m.mxarr[2][1] -
			m.mxarr[1][0] * m.mxarr[0][1] * m.mxarr[2][2] +
			m.mxarr[1][0] * m.mxarr[0][2] * m.mxarr[2][1] +
			m.mxarr[2][0] * m.mxarr[0][1] * m.mxarr[1][2] -
			m.mxarr[2][0] * m.mxarr[0][2] * m.mxarr[1][1];

		float det = m.mxarr[0][0] * inv.mxarr[0][0] + m.mxarr[0][1] * inv.mxarr[1][0] + m.mxarr[0][2] * inv.mxarr[2][0] + m.mxarr[0][3] * inv.mxarr[3][0];

		if (det == 0) {
			throw("Determinant is 0");
		}
		else {
			det = 1.0f / det;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; i < 4; i++) {
					inv.mxarr[i][j] * det;
				}
			}
			m = inv;
		}
	}

	Matrix4D perspective(float fov, float aspect, float near, float far) {


		Matrix4D persp;
		persp[0][0] = 1 / (aspect * tan(fov / 2));
		persp[1][1] = 1 / (tan(fov / 2));
		persp[2][2] = -(far + near) / (far - near);
		persp[2][3] = -1;
		persp[3][2] = -(2 * far * near) / (far - near);
		persp[3][3] = 0.0f;
		return persp;
	}

	Matrix4D lookat(Vector4D camPos, Vector4D camTarget, Vector4D up) {

		Vector4D directionToCam = (camTarget - camPos).norm();
		Vector4D camRight = (Vector4D::cross(directionToCam, up)).norm();
		Vector4D camUp = (Vector4D::cross(camRight, directionToCam)).norm();

		Matrix4D lookat;
		lookat[0][0] = camRight.x();
		lookat[1][0] = camRight.y();
		lookat[2][0] = camRight.z();

		lookat[0][1] = camUp.x();
		lookat[1][1] = camUp.y();
		lookat[2][1] = camUp.z();

		lookat[0][2] = -directionToCam.x();
		lookat[1][2] = -directionToCam.y();
		lookat[2][2] = -directionToCam.z();



		lookat[3][0] = -(Vector4D::dot(camRight, camPos));
		lookat[3][1] = -(Vector4D::dot(camUp, camPos));
		lookat[3][2] = (Vector4D::dot(directionToCam, camPos));

		return lookat;

	}

	///
	/// Translate
	///
	static Matrix4D translation(Vector4D v) {
		return Matrix4D(1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
					    v.x(), v.y(), v.z(), 1.0f);

	}

	/// 
	/// Scale
	/// 
	static Matrix4D scale(Vector4D v) {
		return Matrix4D(v.x(), 0.0f, 0.0f, 0.0f,
						0.0f, v.y(), 0.0f, 0.0f,
						0.0f, 0.0f, v.z(), 0.0f,
						0.0f, 0.0f, 0.0f,  1.0f);
	}

	///
	///Rotation around x-axis
	///
	static Matrix4D rotx(float d) {
		float cs = cos(d);
		float sn = sin(d);
		Matrix4D rot(1, 0, 0, 0, 
			         0, cs, -sn, 0,
			         0, sn, cs, 0,
			         0, 0, 0, 1);
		return rot;
	}

	///
	///Rotation around y-axis 
	///
	static Matrix4D roty(float d) {
		float cs = cos(d);
		float sn = sin(d);
		Matrix4D rot(cs, 0, -sn, 0,
					 0, 1,  0,  0,
					 sn, 0, cs, 0,
					 0,  0,  0,  1);
		return rot;
	}

	///
	///Rotation around z-axis 
	///
	static Matrix4D rotz(float d) {
		float cs = cos(d);
		float sn = sin(d);
		Matrix4D rot(
			cs, -sn, 0, 0,
			sn, cs, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
		return rot;
	}
	///
	///Rotation around Vector
	///
	static Matrix4D rodriguesrotate(Vector4D vec, float d) {
		float cs = cos(d);
		float onedown = 1 - cos(d); 
		float sn = sin(d);

		float x = vec.x();
		float y = vec.y();
		float z = vec.z();

		Matrix4D rod(
			cos(d) + x * x * onedown, x * y * onedown - z * sn, y * sn + x * z * onedown,
			0, z * sn + x * y * onedown, cos(d) + y * y * onedown, -x * sn + y * z * onedown, 0,
			-y * sn + x * z * onedown, x * sn + y * z * onedown, cos(d) + z * z * onedown, 0,
			0, 0, 0, 1
		);
		return rod;
	}


};