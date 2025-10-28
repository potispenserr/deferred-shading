#pragma once
#include <math.h>
#define POW2(x) ((x)*(x))


class Vector4D
{
private:
	float vecarray[4];

public:
	///
	///constructors
	///
	Vector4D() {
		vecarray[0] = 0.0f;
		vecarray[1] = 0.0f;
		vecarray[2] = 0.0f;
		vecarray[3] = 1.0f;
	}

	Vector4D(float x, float y) {
		vecarray[0] = x;
		vecarray[1] = y;
		vecarray[2] = 0.0f;
		vecarray[3] = 1.0f;
	}

	Vector4D(float x, float y, float z) {
		vecarray[0] = x;
		vecarray[1] = y;
		vecarray[2] = z;
		vecarray[3] = 1.0f;
	}
	Vector4D(float x, float y, float z, float w) {
		vecarray[0] = x;
		vecarray[1] = y;
		vecarray[2] = z;
		vecarray[3] = w;
	}

	Vector4D(const Vector4D& v) {
		vecarray[0] = v.vecarray[0];
		vecarray[1] = v.vecarray[1];
		vecarray[2] = v.vecarray[2];
		vecarray[3] = v.vecarray[3];
	}


	///
	///getters
	///
	float&  x() { return vecarray[0]; }
	float&  y() { return vecarray[1]; }
	float&  z() { return vecarray[2]; }
	float&  w() { return vecarray[3]; }

	///
	///setters
	///
	void set(int i, float x)
	{
		vecarray[i] = x;

	}

	void setxy(float x, float y) {
		vecarray[0] = x;
		vecarray[1] = y;

	}

	void setxyz(float x, float y, float z) {
		vecarray[0] = x;
		vecarray[1] = y;
		vecarray[2] = z;

	}

	void setxyzw(float x, float y, float z, float w) {
		vecarray[0] = x;
		vecarray[1] = y;
		vecarray[2] = z;
		vecarray[3] = w;
	}
	///
	///Overloads the + operator for vector addition
	///
	Vector4D operator+(const Vector4D& v) {
		Vector4D newvec;
		newvec.vecarray[0] = vecarray[0] + v.vecarray[0];
		newvec.vecarray[1] = vecarray[1] + v.vecarray[1];
		newvec.vecarray[2] = vecarray[2] + v.vecarray[2];
		newvec.vecarray[3] = vecarray[3] + v.vecarray[3];
		return newvec;
	}
	///
	///Overloads the - operator for vector subtraction
	///
	Vector4D operator-(const Vector4D& v) {
		Vector4D newvec;
		newvec.vecarray[0] = vecarray[0] - v.vecarray[0];
		newvec.vecarray[1] = vecarray[1] - v.vecarray[1];
		newvec.vecarray[2] = vecarray[2] - v.vecarray[2];
		return newvec;
	}

	///
	///Overloads the * operator for multiplication with scalar
	///
	Vector4D operator*(const float& scalar) {
		Vector4D newvec;
		newvec.vecarray[0] = scalar * vecarray[0];
		newvec.vecarray[1] = scalar * vecarray[1];
		newvec.vecarray[2] = scalar * vecarray[2];
		newvec.vecarray[3] = scalar * vecarray[3];
		return newvec;
	}

	///
	///Overloads the = operator for vector copying
	///
	Vector4D operator=(const Vector4D& v) {
		this->vecarray[0] = v.vecarray[0];
		this->vecarray[1] = v.vecarray[1];
		this->vecarray[2] = v.vecarray[2];
		return *this;
	}

	///
	///Overloads the == operator for vector comparison
	///
	bool operator==(const Vector4D& v) {
		if (this->vecarray[0] == v.vecarray[0] && this->vecarray[1] == v.vecarray[1]){
			if (this->vecarray[2] == v.vecarray[2]) {
				return true;
			}
		}
		return false;
	}
	///
	///Overloads the < operator for vector comparison as well
	///
	bool operator<(const Vector4D& v) const {
		if (this->vecarray[0] < v.vecarray[0] && this->vecarray[1] < v.vecarray[1] && this->vecarray[2] < v.vecarray[2]) {
				return true;
		}
		return false;
	}

	bool operator!=(const Vector4D& v) const {
		if (this->vecarray[0] != v.vecarray[0] && this->vecarray[1] != v.vecarray[1] && this->vecarray[2] != v.vecarray[2]) {
			return true;
		}
		return false;
	}



	/*float operator [] (int i) const {
		//return *(Vector4D*)(&mxarr[i]);
		return vecarray[i];
	}*/

	float& operator [] (int i) {
		return vecarray[i];
	}

	///
	/// Calculates length of given vector
	///
	float length(Vector4D v) {
		float sum = POW2(v.vecarray[0]) + POW2(v.vecarray[1]) + POW2(v.vecarray[2]) + POW2(v.vecarray[3]);
		float length = sqrt(sum);
		return length;
	}

	///
	/// Returns the dot product of 2 vectors
	///
	static float dot(Vector4D& a, Vector4D& b) {
		float result = (a.vecarray[0] * b.vecarray[0]) + (a.vecarray[1] * b.vecarray[1]) + (a.vecarray[2] * b.vecarray[2]);

		return(result);
	}

	///
	/// Returns a vector from cross multiplication
	///
	static Vector4D cross(const Vector4D& a, const Vector4D& b) {
		Vector4D cross;
		cross.vecarray[0] =  (a.vecarray[1] * b.vecarray[2]) - (a.vecarray[2] * b.vecarray[1]);
		cross.vecarray[1] =  (a.vecarray[2] * b.vecarray[0]) - (a.vecarray[0] * b.vecarray[2]);
		cross.vecarray[2] =  (a.vecarray[0] * b.vecarray[1]) - (a.vecarray[1] * b.vecarray[0]);
		return cross;
	}

	///
	/// Returns the normalized vector
	///
	Vector4D norm() {
		Vector4D normvec;
		float length = POW2(vecarray[0]) + POW2(vecarray[1]) + POW2(vecarray[2]);
		float norm = sqrt(length);
		if (length > 0) {
			normvec.x() = (this->x() / norm);
			normvec.y() = (this->y() / norm);
			normvec.z() = (this->z() / norm);
			return normvec;
		}
		else {
			return *this;
		}
		
	}

	
};
