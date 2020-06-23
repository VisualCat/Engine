#ifndef __MATRIX3_H__
#define __MATRIX3_H__ 1

#include "vector_2.h"
#include "vector_3.h"

class Matrix3x3 {
public:

	Matrix3x3();
	Matrix3x3(float *values_array);
	Matrix3x3(float value);
	Matrix3x3(float a, float b, float c,
			float d, float e, float f,
			float g, float h, float i);
	Matrix3x3(Vector3 a, Vector3 b, Vector3 c);

	Matrix3x3(const Matrix3x3& copy);
	~Matrix3x3();

	static Matrix3x3 Identity();

	Matrix3x3 Multiply(const Matrix3x3& other) const;

	float Determinant() const;

	Matrix3x3 Adjoint() const;
	bool GetInverse(Matrix3x3& out) const;
	bool Inverse();

	Matrix3x3 Transpose() const;

	static Matrix3x3 Translate(const Vector2& position);
	static Matrix3x3 Translate(float x, float y);

	Vector3 GetColum(int colum) const;
	Vector3 GetLine(int line) const;

	inline Matrix3x3 operator+(const Matrix3x3& other) const;
	inline Matrix3x3& operator+=(const Matrix3x3& other);
	inline Matrix3x3 operator+(float value) const;
	inline Matrix3x3& operator+=(float value);
	inline Matrix3x3 operator-(const Matrix3x3& other) const;
	inline Matrix3x3& operator-=(const Matrix3x3& other);
	inline Matrix3x3 operator-(float value) const;
	inline Matrix3x3& operator-=(float value);
	inline Matrix3x3 operator*(float value) const;
	inline Matrix3x3& operator*=(float value);
	inline Matrix3x3 operator/(float value) const;
	inline Matrix3x3& operator/=(float value);
	bool operator==(const Matrix3x3& other) const;
	bool operator!=(const Matrix3x3& other) const;
	inline void operator=(const Matrix3x3& other);

	float m[9];
};


inline Matrix3x3::Matrix3x3() {
	for (int i = 0; i < 9; i++)
	{
		this->m[i] = 0.0f;
	}
}

inline Matrix3x3::Matrix3x3(float value) {
	for (int i = 0; i < 9; i++)
	{
		this->m[i] = value;
	}
}

inline Matrix3x3::Matrix3x3(float a, float b, float c, 
							float d, float e, float f, 
							float g, float h, float i ) {
	this->m[0] = a;
	this->m[1] = b;
	this->m[2] = c;

	this->m[3] = d;
	this->m[4] = e;
	this->m[5] = f;

	this->m[6] = g;
	this->m[7] = h;
	this->m[8] = i;
}

inline Matrix3x3::Matrix3x3(float *values_array) {
	for (int i = 0; i < 9; i++)
	{
		this->m[i] = values_array[i];
	}
}

inline Matrix3x3::Matrix3x3(Vector3 a, Vector3 b, Vector3 c) {

	this->m[0] = a.x;
	this->m[1] = a.y;
	this->m[2] = a.z;

	this->m[3] = b.x;
	this->m[4] = b.y;
	this->m[5] = b.z; 

	this->m[6] = c.x;
	this->m[7] = c.y;
	this->m[8] = c.z;

}

inline Matrix3x3::Matrix3x3(const Matrix3x3& copy) {
	for (int i = 0; i < 9; i++)
	{
		this->m[i] = copy.m[i];
	}
}

inline Matrix3x3::~Matrix3x3() {
}

inline Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other) const {
}

inline Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& other) {
}

inline Matrix3x3 Matrix3x3::operator+(float value) const {
	return Matrix3x3();
}

inline Matrix3x3& Matrix3x3::operator+=(float value) {
}

inline Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other) const {
	return Matrix3x3();
}

inline Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& other) {
}

inline Matrix3x3 Matrix3x3::operator-(float value) const {
	return Matrix3x3();
}

inline Matrix3x3& Matrix3x3::operator-=(float value) {
}

inline Matrix3x3 Matrix3x3::operator*(float value) const {
	return Matrix3x3();
}

inline Matrix3x3& Matrix3x3::operator*=(float value) {
}

inline Matrix3x3 Matrix3x3::operator/(float value) const {
	return Matrix3x3();
}

inline Matrix3x3& Matrix3x3::operator/=(float value) {
	
}

inline bool Matrix3x3::operator==(const Matrix3x3& other) const {
	return true;
}

inline bool Matrix3x3::operator!=(const Matrix3x3& other) const {
	return true;
}

inline void Matrix3x3::operator=(const Matrix3x3& other) {
	for (int i = 0; i < 9; i++)
	{
		this->m[i] = other.m[i];
	}
}

inline Matrix3x3 Matrix3x3::Identity(){
	return Matrix3x3();
}

inline float Matrix3x3::Determinant() const {

	float res = (m[0] * m[4] * m[8]) + (m[6] * m[5] * m[1]) + (m[7] * m[3] * m[2]);
	res -= (m[6] * m[4] * m[2]) + (m[3] * m[1] * m[8]) + (m[7] * m[5] * m[0]);

	return res;
}

inline bool Matrix3x3::GetInverse(Matrix3x3& out) const {
	return true;
}

inline bool Matrix3x3::Inverse() {	
	return true;
}

inline Matrix3x3 Matrix3x3::Translate(const Vector2& mov_vector) {	
	return Matrix3x3();
}

inline Matrix3x3 Matrix3x3::Translate(float x, float y) {
	return Matrix3x3();
}

inline Matrix3x3 Matrix3x3::Multiply(const Matrix3x3& other) const {
	return Matrix3x3();
}

inline Matrix3x3 Matrix3x3::Adjoint() const {
	return Matrix3x3();
}

inline Matrix3x3 Matrix3x3::Transpose() const {
	return Matrix3x3();
}

inline Vector3 Matrix3x3::GetColum(int colum) const {
	return Vector3();
}

inline Vector3 Matrix3x3::GetLine(int line) const {
	return Vector3();
}

#endif 