#ifndef __Vector4_H__
#define __Vector4_H__ 1

#include "vector_3.h"


class Vector4 {
public:

	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(Vector3 a, float w);
	Vector4(float a);
	Vector4(float* values_array);
	Vector4(const Vector4& other);
	~Vector4();
	
	Vector4 operator+(const Vector4& other) const;
	Vector4 operator+(float value) const;
	void operator+=(const Vector4& other);
	void operator+=(float value);
	Vector4 operator-(const Vector4& other) const;
	Vector4 operator-(float value) const;
	void operator -=(const Vector4& other);
	void operator -=(float value);

	Vector4 operator*(float value) const;
	void operator*=(float value);
	Vector4 operator/(float value) const;
	void operator/=(float value);
	bool operator==(const Vector4& other);
	bool operator!=(const Vector4& other);
	void operator=(const Vector4& other);

	float Magnitude() const;
	void Normalize();
	Vector4 Normalized() const;
	void Scale(Vector4 scale);
	float SqrMagnitude() const;

	static float Distance(const Vector4& a, const Vector4& b);
	static float DotProduct(Vector4 a, Vector4 b);
	static Vector4 Lerp(const Vector4& a, const Vector4& b, float index);	
	static Vector4 MultiplyMatrix(Vector4 vec, const float* mat);
	static float SignedDistancePlane(Vector4 point, Vector4 plane);

	static const Vector4 one;
	static const Vector4 zero;

	float x;
	float y;
	float z;
	float w;

};

inline Vector4::Vector4() {

}

inline Vector4::Vector4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

inline Vector4::Vector4(Vector3 a, float w) {
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;
	this->w = w;
}

inline Vector4::Vector4(float a) {
	x = a;
	y = a;
	z = a;
	w = a;
}

inline Vector4::Vector4(float* values_array) {
	x = values_array[0];
	y = values_array[1];
	z = values_array[2];
	w = values_array[3];
}

inline Vector4::Vector4(const Vector4& other) {
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	this->w = other.w;
}

inline Vector4::~Vector4() {

}

inline float Vector4::Magnitude() const{
  float temp = (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w);
  float magnitude = powf(temp, 0.5f);

  return magnitude;	
}

inline void Vector4::Normalize() {	
	float magnitude = this->Magnitude();

	if (magnitude == 0.0f) {
		return;
	}

	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
	w /= magnitude;
}

inline Vector4 Vector4::Normalized() const {
	float magnitude = this->Magnitude();

	if (magnitude == 0.0f) {
		return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	return Vector4(this->x / magnitude, this->y / magnitude, this->z / magnitude, this->w / magnitude);
}

inline void Vector4::Scale(Vector4 scale) {
	this->x *= scale.x;
	this->y *= scale.y;
	this->z *= scale.z;
	this->w *= scale.w;	
}

inline float Vector4::SqrMagnitude() const {
	float sqrtMagnitudeResult = (this->x * this->x) + (this->y * this->y) +
														(this->z * this->z) + (this->w * this->w);
	return sqrtMagnitudeResult;
}

inline float Vector4::Distance(const Vector4& a, const Vector4& b) {

	Vector4 resultVector;

	resultVector.x = b.x - a.x; resultVector.y = b.y - a.y;
	resultVector.z = b.z - a.z; resultVector.w = b.w - a.w;

	return resultVector.Magnitude();
}

inline float Vector4::DotProduct(Vector4 a, Vector4 b) {

	float dotProductCalculation = (a.x * b.x) + (a.y * b.y) + (a.z * b.z) +
														(a.w * b.w);

	return dotProductCalculation;
}

inline Vector4 Vector4::Lerp(const Vector4& a, const Vector4& b, float index) {	
	float clamped_t = MathUtils::Clamp(index, 0.0f, 1.0f);

	float clampedX = a.x + (b.x - a.x) * clamped_t;
	float clampedY = a.y + (b.y - a.y) * clamped_t;
	float clampedZ = a.z + (b.z - a.z) * clamped_t;
	float clampedW = a.w + (b.w - a.w) * clamped_t;

	return Vector4(clampedX, clampedY, clampedZ, clampedW);
}

inline Vector4 Vector4::MultiplyMatrix(Vector4 vec, const float* mat) {

	float x = (vec.x * mat[0]) + (vec.y * mat[1]) + (vec.z * mat[2]) + (vec.w * mat[3]);
	float y = (vec.x * mat[4]) + (vec.y * mat[5]) + (vec.z * mat[6]) + (vec.w * mat[7]);
	float z = (vec.x * mat[8]) + (vec.y * mat[9]) + (vec.z * mat[10]) + (vec.w * mat[11]);
	float w = (vec.x * mat[12]) + (vec.y * mat[13]) + (vec.z * mat[14]) + (vec.w * mat[15]);

	return Vector4(x, y, z, w);
}

inline float Vector4::SignedDistancePlane(Vector4 point, Vector4 plane) {
	Vector3 planePointVec = Vector3(plane.x, plane.y, plane.z);
	float planeMagnitude = planePointVec.SqrMagnitude();
	Vector3 normalPlane = (planePointVec / planeMagnitude).Normalized();
	Vector3 pointGo = Vector3(point.x, point.y, point.z);


	float dist = plane.w + Vector3::DotProduct(normalPlane, pointGo);

	return dist;

}

inline Vector4 Vector4::operator+(const Vector4& other) const{

	float results[4] = {
		this->x + other.x,
		this->y + other.y,
		this->z + other.z,
		this->w + other.w
	};

	return Vector4(results[0], results[1], results[2], results[3]);
}

inline Vector4 Vector4::operator+(float value) const{
	float results[4] = {
		this->x + value,
		this->y + value,
		this->z + value,
		this->w + value
	};

	return Vector4(results[0], results[1], results[2], results[3]);
}

inline void Vector4::operator+=(const Vector4& other) {
	*this = *this + other;
}

inline void Vector4::operator+=(float value) {
	*this = *this + value;
}

inline Vector4 Vector4::operator-(const Vector4& other) const{
	float results[4] = {
		this->x - other.x,
		this->y - other.y,
		this->z - other.z,
		this->w - other.w
	};

	return Vector4(results[0], results[1], results[2], results[3]);
}

inline Vector4 Vector4::operator-(float value) const{
	float results[4] = {
		this->x - value,
		this->y - value,
		this->z - value,
		this->w - value
	};

	return Vector4(results[0], results[1], results[2], results[3]);
}

inline void Vector4::operator -=(const Vector4& other) {	
	*this = *this - other;
}

inline void Vector4::operator -=(float value) {
	*this = *this - value;
}

inline Vector4 Vector4::operator*(float value) const{
	float results[4] = {
		this->x * value,
		this->y * value,
		this->z * value,
		this->w * value
	};

	return Vector4(results[0], results[1], results[2], results[3]);
}

inline void Vector4::operator*=(float value) {
	*this = *this * value;
}

inline Vector4 Vector4::operator/(float value) const{	
	float results[4] = {
		x / value,
		y / value,
		z / value,
		w / value
	};

	return Vector4(results[0], results[1], results[2], results[3]);
}

inline void Vector4::operator/=(float value) {
	x /= value;
	y /= value;
	z /= value;
	w /= value;
}

inline bool Vector4::operator==(const Vector4& other) {
	return (this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w);
}
inline bool Vector4::operator!=(const Vector4& other) {
	return (this->x != other.x && this->y != other.y && this->z != other.z && this->w != other.w);
}
inline void Vector4::operator=(const Vector4& other) {
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	this->w = other.w;
}

#endif 
