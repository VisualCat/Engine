#ifndef __VECTOR2_H__
#define __VECTOR2_H__ 1

#include "math.h"
#include "math_utils.h"

class Vector2 {
public:
  Vector2();
  Vector2(float x, float y);
  Vector2(const Vector2 &copy);
  ~Vector2();

  Vector2 operator+(const Vector2 &other) const;
  Vector2 operator+(float value);
  Vector2 &operator+=(const Vector2 &other);
  Vector2 &operator+=(float value);
  Vector2 operator-(const Vector2 &other) const;
  Vector2 operator-(float value) const;
  Vector2 &operator-();
  Vector2 &operator-=(const Vector2 &other);
  Vector2 &operator-=(float value);
  bool operator==(const Vector2 &other) const;
  bool operator!=(const Vector2 &other) const;
  void operator=(const Vector2 &other);
  void operator=(float value);
  Vector2 operator*(float value) const;
  Vector2 &operator*=(float value);
  Vector2 operator/(float value) const;
  Vector2 &operator/=(float value);

  float Magnitude() const;
  void Normalize();
  Vector2 Normalized() const;

  void Scale(const Vector2 scale);

  float SqrMagnitude() const;
  static float Distance(const Vector2 a, const Vector2 b);

  static float DotProduct(Vector2 a, Vector2 b);

  static Vector2 Lerp(const Vector2 a, const Vector2 b, float t);
  static Vector2 LerpUnclamped(const Vector2 a, const Vector2 b, float t);

  static const Vector2 up;
  static const Vector2 down;
  static const Vector2 right;
  static const Vector2 left;
  static const Vector2 zero;
  static const Vector2 one;

  float x;
  float y;
};

inline Vector2::Vector2() {
  this->x = 0.0f;
  this->y = 0.0f;
}

inline Vector2::Vector2(float x, float y) {
  this->x = x;
  this->y = y;
}

inline Vector2::Vector2(const Vector2 &other) {
  this->x = other.x;
  this->y = other.y;
}

inline Vector2::~Vector2() {}

inline Vector2 Vector2::operator+(const Vector2 &other) const {
	Vector2 result;
	result.x = this->x + other.x;
	result.y = this->y + other.y;
  return result;
}

inline Vector2 Vector2::operator+(float value) { 
	Vector2 result;
	result.x = this->x + value;
	result.y = this->y + value;
	return result; 
}

inline Vector2 &Vector2::operator+=(const Vector2 &other) { 
	this->x += other.x;
	this->y += other.y;
	return *this; 
}

inline Vector2 &Vector2::operator+=(float value) {
	this->x += value;
	this->y += value;
	return *this;
}

inline Vector2 Vector2::operator-(const Vector2 &other) const {
	Vector2 result;
	result.x = this->x - other.x;
	result.y = this->y - other.y;
	return result;
}

inline Vector2 Vector2::operator-(float value) const {
	Vector2 result;
	result.x = this->x - value;
	result.y = this->y - value;
	return result;
}
inline Vector2 &Vector2::operator-() { 
	this->x = -this->x;
	this->y = -this->y;
	return *this; 
}

inline Vector2 &Vector2::operator-=(const Vector2 &other) {
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

inline Vector2 &Vector2::operator-=(float value) {
	this->x -= value;
	this->y -= value;
	return *this;
}

inline bool Vector2::operator==(const Vector2 &value) const { 
	if (this->x == value.x && this->y == value.y)
	{
		return true;
	}
	return false; 
}

inline bool Vector2::operator!=(const Vector2 &value) const {
	if (this->x == value.x && this->y == value.y)
	{
		return false;
	}
	return true;
}

inline void Vector2::operator=(const Vector2 &other) {
	this->x = other.x;
	this->y = other.y;
}

inline void Vector2::operator=(float value) {
	this->x = value;
	this->y = value;
}

inline Vector2 Vector2::operator*(float value) const {
	Vector2 result;
	result = this->x * value;
	result = this->y * value;
	return result;
}

inline Vector2 &Vector2::operator*=(float value) {
	this->x *= value;
	this->y *= value;
	return *this;
}

inline Vector2 Vector2::operator/(float value) const {
	Vector2 result;
	result = this->x / value;
	result = this->y / value;
	return result;
}
inline Vector2 &Vector2::operator/=(float value) {
	this->x /= value;
	this->y /= value;
	return *this;
}
inline float Vector2::Magnitude() const { 
	return sqrtf((x * x) + (y * y));
}

inline void Vector2::Normalize() {
	
	float inverseMagnitude = 1.0f / this->Magnitude();
	*this *= inverseMagnitude;
}

inline Vector2 Vector2::Normalized() const {

	float mag = this->Magnitude();
	Vector2 result;

	result.x = this->x / mag;
	result.y = this->y / mag;
	
	return result;
}
inline void Vector2::Scale(const Vector2 scale) {
	this->x *= scale.x;
	this->y *= scale.y;
}

inline float Vector2::SqrMagnitude() const { 
	return (x*x) + (y*y);
}

inline float Vector2::Distance(const Vector2 a, const Vector2 b) {
  return (b-a).Magnitude();
}

inline Vector2 Vector2::Lerp(const Vector2 a, const Vector2 b, float t) {
	
	MathUtils::Clamp(t, 0.0f, 1.0f);
	
  return Vector2::LerpUnclamped(a, b, t);
}

inline Vector2 Vector2::LerpUnclamped(const Vector2 a, const Vector2 b,
                                      float t) {
	Vector2 result;
	result = a + ((b-a)*t);
	return result;
}

inline float Vector2::DotProduct(Vector2 a, Vector2 b) { 
	return (a.x*b.x) + (a.y*b.y); 
}

#endif
