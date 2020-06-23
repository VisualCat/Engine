#ifndef __MATRIX2_H__
#define __MATRIX2_H__ 1

#include "vector_2.h"

class Matrix2x2 {
public:

	Matrix2x2();
	Matrix2x2(float a[4]);
	Matrix2x2(float value);
	Matrix2x2(const Vector2& a, const Vector2& b); 
	Matrix2x2(const Matrix2x2& copy);
	~Matrix2x2();
	Matrix2x2 Identity() const;
	Matrix2x2 Multiply(const Matrix2x2& other) const;
	float Determinant() const;
	Matrix2x2 Adjoint() const;
	Vector2 GetLine(int line) const;
	Vector2 GetColum(int line) const;

	Matrix2x2 Inverse() const;
	Matrix2x2 Transpose() const;

	inline Matrix2x2 operator+(const Matrix2x2& other) const;
	inline void operator+=(const Matrix2x2& other);
	inline Matrix2x2 operator+(float value) const;
	inline void operator+=(float value);
	inline Matrix2x2 operator-(const Matrix2x2& other) const;
	inline void operator-=(const Matrix2x2& other);
	inline Matrix2x2 operator-(float value) const;
	inline void operator-=(float value);

	inline Matrix2x2 operator*(float value) const;
	inline void operator*=(float value);
	inline Matrix2x2 operator/(float value) const;
	inline void operator/=(float value);

	bool operator==(const Matrix2x2& other) const;
	bool operator!=(const Matrix2x2& other) const;
	inline void operator=(const Matrix2x2& other);

	float m[4];
};


inline Matrix2x2::Matrix2x2() {
	for (int i = 0; i < 4; i++)
	{
		this->m[i] = 0.0f;
	}
}

inline Matrix2x2::Matrix2x2(float a[4]) {
	for (int i = 0; i < 4; i++)
	{
		this->m[i] = a[i];
	}
}

inline Matrix2x2::Matrix2x2(float a) {
	for (int i = 0; i < 4; i++)
	{
		this->m[i] = a;
	}
}

inline Matrix2x2::Matrix2x2(const Vector2& a, const Vector2& b) {
	
	this->m[0] = a.x;
	this->m[1] = a.y;
	this->m[2] = b.x;
	this->m[3] = b.y;
	
}

inline Matrix2x2::Matrix2x2(const Matrix2x2& copy) {
	this->m = copy.m;
}

inline Matrix2x2::~Matrix2x2() {

}

inline Matrix2x2 Matrix2x2::operator+(const Matrix2x2& other) const {
	Matrix2x2 result;
	for (int i = 0; i < 4; i++)
	{
		result.m[i] = this->m[i] + other.m[i];
	}
	return result;
}

inline void Matrix2x2::operator+=(const Matrix2x2& other) {
	for (int i = 0; i < 4; i++)
	{
		this->m[i] += other.m[i];
	}
}

inline Matrix2x2 Matrix2x2::operator+(float value) const {
	Matrix2x2 result;
	for (int i = 0; i < 4; i++)
	{
		result.m[i] = this->m[i] + value;
	}
	return result;
}

inline void Matrix2x2::operator+=(float value) {
	for (int i = 0; i < 4; i++)
	{
		this->m[i] += value;
	}
}

inline Matrix2x2 Matrix2x2::operator-(const Matrix2x2& other) const {
	Matrix2x2 result;
	for (int i = 0; i < 4; i++)
	{
		result.m[i] = this->m[i] - other.m[i];
	}
	return result;
}

inline void Matrix2x2::operator-=(const Matrix2x2& other) {
	for (int i = 0; i < 4; i++)
	{
		this->m[i] -= other.m[i];
	}
}

inline Matrix2x2 Matrix2x2::operator-(float value) const {
	Matrix2x2 result;
	for (int i = 0; i < 4; i++)
	{
		result.m[i] = this->m[i] - value;
	}
	return result;
}

inline void Matrix2x2::operator-=(float value) {
	for (int i = 0; i < 4; i++)
	{
		this->m[i] -= value;
	}
}


inline Matrix2x2 Matrix2x2::operator*(float value) const {
	Matrix2x2 result;
	for (int i = 0; i < 4; i++)
	{
		result.m[i] = this->m[i] * value;
	}
	return result;
}

inline void Matrix2x2::operator*=(float value) {
	for (int i = 0; i < 4; i++)
	{
		this->m[i] *= value;
	}
}

inline Matrix2x2 Matrix2x2::operator/(float value) const {
	Matrix2x2 result;
	for (int i = 0; i < 4; i++)
	{
		result.m[i] = this->m[i] / value;
	}
	return result;
}

inline void Matrix2x2::operator/=(float value) {
	for (int i = 0; i < 4; i++)
	{
		this->m[i] /= value;
	}
}


inline bool Matrix2x2::operator==(const Matrix2x2& other) const 
	for (int i = 0; i < 4; i++)
	{
		if (this->m[i] != other.m[i])
		{
			return false;
		}
	}
	return true;
}

inline bool Matrix2x2::operator!=(const Matrix2x2& other) const {
	for (int i = 0; i < 4; i++)
	{
		if (this->m[i] != other.m[i])
		{
			return true;
		}
	}
	return true;
}

inline void Matrix2x2::operator=(const Matrix2x2& other) {
	for (int i = 0; i < 4; i++)
	{
		this->m[i] = other.m[i];
	}
}

inline Matrix2x2 Matrix2x2::Identity() const {
	Matrix2x2 id;
	id.m[0] = 1.0f;
	id.m[1] = 0.0f;
	id.m[2] = 0.0f;
	id.m[3] = 1.0f;
	return id;
}

inline float Matrix2x2::Determinant() const {
	return (this->m[0]*this->m[3]) - (this->m[1] * this->m[2]);
}

inline Matrix2x2 Matrix2x2::Inverse() const {
	return Matrix2x2();
}

inline Matrix2x2 Matrix2x2::Multiply(const Matrix2x2& other) const {
	return Matrix2x2();
}

inline Matrix2x2 Matrix2x2::Adjoint() const {
	Matrix2x2 adMat;

	adMat.m[0] = this.m[3];
	adMat.m[1] = this.m[1];
	adMat.m[2] = this.m[2];
	adMat.m[3] = this.m[0];

	adMat.m[0] *= -1;
	adMat.m[3] *= -1;

	return adMat;
}

inline Matrix2x2 Matrix2x2::Transpose() const {
	Matrix2x2 transMat;
	transMat.m[0] = this.m[0];
	transMat.m[1] = this.m[2];
	transMat.m[2] = this.m[1];
	transMat.m[3] = this.m[3];
	return transMat;
}

inline Vector2 Matrix2x2::GetLine(int line) const {
	return Vector2();
}

inline Vector2 Matrix2x2::GetColum(int line) const {	
	return Vector2();
}


#endif
