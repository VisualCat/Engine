#ifndef __VECTOR3_H__
#define __VECTOR3_H__ 1

#include "math_utils.h"
#include "math.h"

class Vector3 {

public:
	Vector3();
	Vector3(float value);
	Vector3(float x, float y, float z);
	Vector3(float* values_array);
	Vector3(const Vector3& other);
	~Vector3();

	Vector3 operator+(const Vector3& other) const;
	Vector3 operator+(float value) const;
	Vector3& operator+=(const Vector3& other);
	Vector3& operator+=(float value);
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator-(float value) const;
	Vector3& operator-=(const Vector3& other);
	Vector3& operator-=(float value);
	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;
	void operator=(const Vector3& other);
	void operator=(float value);
	Vector3 operator*(float value) const;
	Vector3& operator*=(float value);
	Vector3 operator/(float value) const;
	Vector3& operator/=(float value);

	float Magnitude() const;
	Vector3 Normalized() const;
	void Normalize();
	float SqrMagnitude() const;
	void Scale(const Vector3& other);

	static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
	static Vector3 LerpUnclamped(const Vector3& a, const Vector3& b, float t);
	static float DotProduct(const Vector3& a, const Vector3& b);
	static float Angle(const Vector3& a, const Vector3& b);
	static Vector3 CrossProduct(const Vector3& a,const Vector3& b);	
	static float Distance(const Vector3& a, const Vector3& b);
	static Vector3 Reflect(const Vector3& direction, const Vector3& normal);

	static const Vector3 up;
	static const Vector3 down;
	static const Vector3 right;
	static const Vector3 left;
	static const Vector3 forward;
	static const Vector3 back;
	static const Vector3 zero;
	static const Vector3 unit;

	float x;
	float y;
	float z;
};
inline Vector3::Vector3() {
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

inline Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

inline Vector3::Vector3(float *values_array) {
	this->x = *values_array;
	this->y = (*values_array+1);
	this->z = (*values_array+2);
}

inline Vector3::Vector3(float value) {
	this->x = value;
	this->y = value;
	this->z = value;
}

inline Vector3::Vector3(const Vector3& other) {
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

inline Vector3::~Vector3() {}

inline float Vector3::Magnitude() const {
	return sqrtf(SqrMagnitude());
}

inline void Vector3::Normalize() {	

	float inverseMagnitude = 1.0f / Magnitude();
	*this *= inverseMagnitude;
}

inline Vector3 Vector3::Normalized() const {
	Vector3 auxVec;
	auxVec.x = this->x;
	auxVec.y = this->y;
	auxVec.z = this->z;
	auxVec.Normalize();
	return auxVec;
}

inline float Vector3::DotProduct(const Vector3& a, const Vector3& other)  {
	return (a.x*other.x) + (a.y*other.y) + (a.z*other.z);
}

inline float Vector3::Angle(const Vector3& a, const Vector3& other)  {
	
	return acosf(Vector3::DotProduct(a, other) / (a.Magnitude() * other.Magnitude()));
}

inline Vector3 Vector3::CrossProduct(const Vector3& a, const Vector3& other)  {
	
	Vector3 result;

	result.x = (a.y*other.z) - (a.z*other.y);
	result.y = (a.z*other.x) - (a.x*other.z);
	result.z = (a.x*other.y) - (a.y*other.x);
	
	return result;
}

inline float Vector3::SqrMagnitude() const {
	return (x * x) + (y * y) + (z * z);
}

inline void Vector3::Scale(const Vector3& other) {
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
}

inline Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t) {

	t = MathUtils::Clamp(t, 0.0f, 1.0f);

	return Vector3::LerpUnclamped(a, b, t);
}

inline Vector3 Vector3::LerpUnclamped(const Vector3& a, const Vector3& b, float t) {
	Vector3 result;
	result = a + ((b - a)*t);
	return result;
}

inline float Vector3::Distance(const Vector3& a, const Vector3& b) {
	return (b - a).Magnitude();
}

inline Vector3 Vector3::Reflect(const Vector3& direction, const Vector3& normal) {
	/*
	Vector3 dotRes = Vector3::DotProduct(direction, normal);
	Vector3 norm = normal;
	norm.Normalize();
	dotRes = direction - dotRes * 2;*/
	return Vector3::zero;
}

inline Vector3 Vector3::operator+(const Vector3& other) const {
	Vector3 result;
	result.x = this->x + other.x;
	result.y = this->y + other.y;
	result.z = this->z + other.z;
	return result;
}

inline Vector3 Vector3::operator+(float value) const {
	Vector3 result;
	result.x = this->x + value;
	result.y = this->y + value;
	result.z = this->z + value;
	return result;
}

inline Vector3& Vector3::operator+=(const Vector3& other) {
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

inline Vector3& Vector3::operator+=(float value) {
	this->x += value;
	this->y += value;
	this->z += value;
	return *this;
}

inline Vector3 Vector3::operator-(const Vector3& other) const {
	Vector3 result;
	result.x = this->x - other.x;
	result.y = this->y - other.y;
	result.z = this->z - other.z;
	return result;
}

inline Vector3 Vector3::operator-(float value) const {
	Vector3 result;
	result.x = this->x - value;
	result.y = this->y - value;
	result.z = this->z - value;
	return result;
}

inline Vector3& Vector3::operator-=(const Vector3& other) {
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

inline Vector3& Vector3::operator-=(float value) {
	this->x -= value;
	this->y -= value;
	this->z -= value;
	return *this;
}

inline bool Vector3::operator==(const Vector3& other) const {
	return (this->x == other.x && this->y == other.y && this->z == other.z);
	
}

inline bool Vector3::operator!=(const Vector3& other) const {
	return (this->x == other.x && this->y == other.y && this->z == other.z);
}

inline void Vector3::operator=(const Vector3& other) {
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

inline void Vector3::operator=(float value) {
	this->x = value;
	this->y = value;
	this->z = value;
}

inline Vector3 Vector3::operator*(float value) const {
	Vector3 result;
	result.x = this->x * value;
	result.y = this->y * value;
	result.z = this->z * value;
	return result;
}

inline Vector3& Vector3::operator*=(float value) {
	this->x *= value;
	this->y *= value;
	this->z *= value;
	return *this;
}

inline Vector3 Vector3::operator/(float value) const {
	Vector3 result;
	result.x = this->x / value;
	result.y = this->y / value;
	result.z = this->z / value;
	return result;
}

inline Vector3& Vector3::operator/=(float value) {
	this->x /= value;
	this->y /= value;
	this->z /= value;
	return *this;
}

#endif 
