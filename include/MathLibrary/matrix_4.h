#ifndef __MATRIX4_H__
#define __MATRIX4_H__ 1

#include "vector_3.h"
#include "vector_4.h"
#include "matrix_3.h"
#include "stdio.h"

class Matrix4x4{
 public:

  Matrix4x4();
  Matrix4x4(float a[16]);
  Matrix4x4(float value);
  Matrix4x4(float a, float b, float c, float d,
			float e, float f, float g, float h,
			float i, float j, float k, float l,
			float m, float n, float o, float p);
  Matrix4x4(const Matrix4x4& copy);
	Matrix4x4(const float* mat);
  ~Matrix4x4();

  static Matrix4x4 Identity();
  Matrix4x4 Multiply(const Matrix4x4& other) const;

  float Determinant() const;
  Matrix4x4 Adjoint() const;
  bool GetInverse(Matrix4x4* out) const;
  bool Inverse();

  Matrix4x4 Transpose() const;

  static Matrix4x4 LookAt(Vector3 from, Vector3 to, Vector3 up);
  static Matrix4x4 Projection(float fov, float aspectRatio, float znear, float zfar);

  static Matrix4x4 Translate(const Vector3& distance);
  static Matrix4x4 Translate(float x, float y, float z);

  static Matrix4x4 Scale(const Vector3& scale);
  static Matrix4x4 Scale(float x, float y, float z);

  static Matrix4x4 RotateX(float radians);
  static Matrix4x4 RotateY(float radians);
  static Matrix4x4 RotateZ(float radians);

  static Matrix4x4 GetTransform(const Vector3& translate, const Vector3& scale,
                      float rotateX, float rotateY, float rotateZ);

  static Matrix4x4 GetTransform(float trans_x, float trans_y, float trans_z,
                      float scale_x, float scale_y, float scale_Z,
                      float rotateX, float rotateY, float rotateZ);

  Matrix4x4 PerspectiveMatrix(float fov, float aspect,
	  float near, float far) const;

  Matrix4x4 OrthoMatrix(float right, float left, float top, float valueottom,
	  float near, float far) const;

  Vector4 GetColum(int colum) const;
  Vector4 GetLine(int line) const;

  Matrix4x4 operator+(const Matrix4x4& other) const;
  Matrix4x4& operator+=(const Matrix4x4& other);
  Matrix4x4 operator+(float value) const;
  Matrix4x4& operator+=(float value);
  Matrix4x4 operator-(const Matrix4x4& other) const;
  Matrix4x4& operator-=(const Matrix4x4& other);
  Matrix4x4 operator-(float value) const;
  Matrix4x4& operator-=(float value);
  Matrix4x4& operator*=(float value);
  Matrix4x4 operator*(float value) const;
  Matrix4x4& operator/=(float value);
  Matrix4x4 operator/(float value) const;
  bool operator==(const Matrix4x4& other);
  bool operator!=(const Matrix4x4& other);
  void operator=(const Matrix4x4& other);

  float m[16];
};


inline Matrix4x4::Matrix4x4() {

}

inline Matrix4x4::Matrix4x4(float array[16]) {
	for (int i = 0; i < 16; i++)
	{
		this->m[i] = array[i];
	}
}

inline Matrix4x4::Matrix4x4(float value) {
	for (int i = 0; i < 16; i++)
	{
		this->m[i] = value;
	}
}

inline Matrix4x4::Matrix4x4(float a, float b, float c, float d, 
							float e, float f, float g, float h, 
							float i, float j, float k, float l,
							float m, float n, float o, float p) {
	this->m[0] = a;
	this->m[1] = b;
	this->m[2] = c;
	this->m[3] = d;
	this->m[4] = e;
	this->m[5] = f;
	this->m[6] = g;
	this->m[7] = h;
	this->m[8] = i;
	this->m[9] = j;
	this->m[10] = k;
	this->m[11] = l;
	this->m[12] = m;
	this->m[13] = n;
	this->m[14] = o;
	this->m[15] = p;
}

inline Matrix4x4::Matrix4x4(const Matrix4x4& copy) {
	for (int i = 0; i < 16; i++)
	{
		this->m[i] = copy.m[i];
	}
}

inline Matrix4x4::Matrix4x4(const float* mat)
{

	for (int i = 0; i < 16; ++i) {
		m[i] = mat[i];
	}

}

inline Matrix4x4::~Matrix4x4() {

}

inline Matrix4x4 Matrix4x4::Identity() {

	Matrix4x4 result; 

	result.m[0] = 1.0f;
	result.m[1] = 0.0f;
	result.m[2] = 0.0f;
	result.m[3] = 0.0f;

	result.m[4] = 0.0f;
	result.m[5] = 1.0f;
	result.m[6] = 0.0f;
	result.m[7] = 0.0f;

	result.m[8] = 0.0f;
	result.m[9] = 0.0f;
	result.m[10] = 1.0f;
	result.m[11] = 0.0f;

	result.m[12] = 0.0f;
	result.m[13] = 0.0f;
	result.m[14] = 0.0f;
	result.m[15] = 1.0f;

	return result;
}

inline Matrix4x4 Matrix4x4::Multiply(const Matrix4x4& other)const  {
	
  Matrix4x4 out;

  //First Column
  out.m[0] = (this->m[0] * other.m[0]) + (this->m[1] * other.m[4]) + (this->m[2] * other.m[8]) + (this->m[3] * other.m[12]);
  out.m[4] = (this->m[4] * other.m[0]) + (this->m[5] * other.m[4]) + (this->m[6] * other.m[8]) + (this->m[7] * other.m[12]);
  out.m[8] = (this->m[8] * other.m[0]) + (this->m[9] * other.m[4]) + (this->m[10] * other.m[8]) + (this->m[11] * other.m[12]);
  out.m[12] = (this->m[12] * other.m[0]) + (this->m[13] * other.m[4]) + (this->m[14] * other.m[8]) + (this->m[15] * other.m[12]);

  //Second Column
  out.m[1] = (this->m[0] * other.m[1]) + (this->m[1] * other.m[5]) + (this->m[2] * other.m[9]) + (this->m[3] * other.m[13]);
  out.m[5] = (this->m[4] * other.m[1]) + (this->m[5] * other.m[5]) + (this->m[6] * other.m[9]) + (this->m[7] * other.m[13]);
  out.m[9] = (this->m[8] * other.m[1]) + (this->m[9] * other.m[5]) + (this->m[10] * other.m[9]) + (this->m[11] * other.m[13]);
  out.m[13] = (this->m[12] * other.m[1]) + (this->m[13] * other.m[5]) + (this->m[14] * other.m[9]) + (this->m[15] * other.m[13]);

  //Third Column
  out.m[2] = (this->m[0] * other.m[2]) + (this->m[1] * other.m[6]) + (this->m[2] * other.m[10]) + (this->m[3] * other.m[14]);
  out.m[6] = (this->m[4] * other.m[2]) + (this->m[5] * other.m[6]) + (this->m[6] * other.m[10]) + (this->m[7] * other.m[14]);
  out.m[10] = (this->m[8] * other.m[2]) + (this->m[9] * other.m[6]) + (this->m[10] * other.m[10]) + (this->m[11] * other.m[14]);
  out.m[14] = (this->m[12] * other.m[2]) + (this->m[13] * other.m[6]) + (this->m[14] * other.m[10]) + (this->m[15] * other.m[14]);

  //Fourth Column
  out.m[3] = (this->m[0] * other.m[3]) + (this->m[1] * other.m[7]) + (this->m[2] * other.m[11]) + (this->m[3] * other.m[15]);
  out.m[7] = (this->m[4] * other.m[3]) + (this->m[5] * other.m[7]) + (this->m[6] * other.m[11]) + (this->m[7] * other.m[15]);
  out.m[11] = (this->m[8] * other.m[3]) + (this->m[9] * other.m[7]) + (this->m[10] * other.m[11]) + (this->m[11] * other.m[15]);
  out.m[15] = (this->m[12] * other.m[3]) + (this->m[13] * other.m[7]) + (this->m[14] * other.m[11]) + (this->m[15] * other.m[15]);


  return out;
}


inline float Matrix4x4::Determinant() const {
	float res;
	Matrix3x3 aux4Det = Matrix3x3(this->m[5], this->m[6], this->m[7], 
								this->m[9], this->m[10], this->m[11], 
								this->m[13], this->m[14], this->m[15]);
	res = this->m[0] * aux4Det.Determinant();
	aux4Det = Matrix3x3(this->m[4], this->m[6], this->m[7],
						this->m[8], this->m[10], this->m[11],
						this->m[12], this->m[14], this->m[15]);
	res -= this->m[1] * aux4Det.Determinant();
	aux4Det = Matrix3x3(this->m[4], this->m[5], this->m[7],
						this->m[8], this->m[9], this->m[11],
						this->m[12], this->m[13], this->m[15]);
	res += this->m[2] * aux4Det.Determinant();
	aux4Det = Matrix3x3(this->m[4], this->m[5], this->m[6],
						this->m[8], this->m[9], this->m[10],
						this->m[12], this->m[13], this->m[14]);
	res -= this->m[3] * aux4Det.Determinant();
	return res;
}


inline Matrix4x4 Matrix4x4::Adjoint() const {
	
	Matrix4x4 result;
	Matrix3x3 aux4Det = Matrix3x3(this->m[5], this->m[6], this->m[7],
		this->m[9], this->m[10], this->m[11],
		this->m[13], this->m[14], this->m[15]);
	result.m[0] = aux4Det.Determinant();

	aux4Det = Matrix3x3(this->m[4], this->m[6], this->m[7],
		this->m[8], this->m[10], this->m[11],
		this->m[12], this->m[14], this->m[15]);
	result.m[1] = -aux4Det.Determinant();

	aux4Det = Matrix3x3(this->m[4], this->m[5], this->m[7],
		this->m[8], this->m[9], this->m[11],
		this->m[12], this->m[13], this->m[15]);
	result.m[2] = aux4Det.Determinant();

	aux4Det = Matrix3x3(this->m[4], this->m[5], this->m[6],
		this->m[8], this->m[9], this->m[10],
		this->m[12], this->m[13], this->m[14]);
	result.m[3] = -aux4Det.Determinant();

	//-------------------

	aux4Det = Matrix3x3(this->m[1], this->m[2], this->m[3],
		this->m[9], this->m[10], this->m[11],
		this->m[13], this->m[14], this->m[15]);
	result.m[4] = -aux4Det.Determinant();

	aux4Det = Matrix3x3(this->m[0], this->m[2], this->m[3],
		this->m[8], this->m[10], this->m[11],
		this->m[12], this->m[14], this->m[15]);
	result.m[5] = aux4Det.Determinant();

	aux4Det = Matrix3x3(this->m[0], this->m[1], this->m[3],
		this->m[8], this->m[9], this->m[11],
		this->m[12], this->m[13], this->m[15]);
	result.m[6] = -aux4Det.Determinant();

	aux4Det = Matrix3x3(this->m[0], this->m[1], this->m[2],
		this->m[8], this->m[9], this->m[10],
		this->m[12], this->m[13], this->m[14]);
	result.m[7] = aux4Det.Determinant();

	//-------------------

	aux4Det = Matrix3x3(this->m[1], this->m[2], this->m[3],
		this->m[5], this->m[6], this->m[7],
		this->m[13], this->m[14], this->m[15]);
	result.m[8] = aux4Det.Determinant();

	aux4Det = Matrix3x3(this->m[0], this->m[2], this->m[3],
		this->m[4], this->m[6], this->m[7],
		this->m[12], this->m[14], this->m[15]);
	result.m[9] = -aux4Det.Determinant();

	aux4Det = Matrix3x3(this->m[0], this->m[1], this->m[3],
		this->m[4], this->m[5], this->m[7],
		this->m[12], this->m[13], this->m[15]);
	result.m[10] = aux4Det.Determinant();

	aux4Det = Matrix3x3(this->m[0], this->m[1], this->m[2],
		this->m[4], this->m[5], this->m[6],
		this->m[12], this->m[13], this->m[14]);
	result.m[11] = -aux4Det.Determinant();

	//-------------------

	aux4Det = Matrix3x3(this->m[1], this->m[2], this->m[3],
		this->m[5], this->m[6], this->m[7],
		this->m[9], this->m[10], this->m[11]);
	result.m[12] = -aux4Det.Determinant();

	aux4Det = Matrix3x3(this->m[0], this->m[2], this->m[3],
		this->m[4], this->m[6], this->m[7],
		this->m[8], this->m[10], this->m[11]);
	result.m[13] = aux4Det.Determinant();

	aux4Det = Matrix3x3(this->m[0], this->m[1], this->m[3],
		this->m[4], this->m[5], this->m[7],
		this->m[8], this->m[9], this->m[11]);
	result.m[14] = -aux4Det.Determinant();

	aux4Det = Matrix3x3(this->m[0], this->m[1], this->m[2],
		this->m[4], this->m[5], this->m[6],
		this->m[8], this->m[9], this->m[10]);
	result.m[15] = aux4Det.Determinant();
		
	result.Transpose();
	
	return result;

}

inline bool Matrix4x4::Inverse() {

	float det = Determinant();

	if (det == 0)
	{
		return false;
	}

	*this = (Adjoint().Transpose()) / det;

	return true;
}

inline bool Matrix4x4::GetInverse(Matrix4x4* out) const {

	return out->Inverse();

}

inline Matrix4x4 Matrix4x4::Transpose() const {
		
  Matrix4x4 result;

  result.m[0] = this->m[0]; result.m[1] = this->m[4]; result.m[2] = this->m[8]; result.m[3] = this->m[12];
  result.m[4] = this->m[1]; result.m[5] = this->m[5]; result.m[6] = this->m[9]; result.m[7] = this->m[13];
  result.m[8] = this->m[2]; result.m[9] = this->m[6]; result.m[10] = this->m[10]; result.m[11] = this->m[14];
  result.m[12] = this->m[3]; result.m[13] = this->m[7]; result.m[14] = this->m[11]; result.m[15] = this->m[15];

  return result;
}

inline Matrix4x4 Matrix4x4::LookAt(Vector3 from, Vector3 to, Vector3 WorldUp) {
	Vector3 forward = (from - to);
	forward.Normalize();
	Vector3 right = Vector3::CrossProduct(WorldUp, forward);
	Vector3 up = Vector3::CrossProduct(forward, right);

	Matrix4x4 translation = Identity(); // Identity matrix by default
	translation.m[3] = -from.x; // Third column, first row
	translation.m[7] = -from.y;
	translation.m[11] = -from.z;
	Matrix4x4 rotation = Identity();
	rotation.m[0] = right.x; // First column, first row
	rotation.m[1] = right.y;
	rotation.m[2] = right.z;
	rotation.m[4] = up.x; // First column, second row
	rotation.m[5] = up.y;
	rotation.m[6] = up.z;
	rotation.m[8] = forward.x; // First column, third row
	rotation.m[9] = forward.y;
	rotation.m[10] = forward.z;

	// Return lookAt matrix as combination of translation and rotation matrix
	return rotation.Multiply(translation).Transpose(); // Remember to read from right to left (first translation then rotation)

	/*
	Matrix4x4 camToWorld = Identity();

	camToWorld.m[0] = right.x;
	camToWorld.m[4] = right.y;
	camToWorld.m[8] = right.z;
	camToWorld.m[1] = up.x;
	camToWorld.m[5] = up.y;
	camToWorld.m[9] = up.z;
	camToWorld.m[2] = forward.x;
	camToWorld.m[6] = forward.y;
	camToWorld.m[10] = forward.z;
	
	camToWorld.m[3] = from.x;
	camToWorld.m[7] = from.y;
	camToWorld.m[11] = from.z;
	return camToWorld;

	*/
}

inline Matrix4x4 Matrix4x4::Projection(float fov, float aspectRatio, float znear, float zfar) {

	float yScale = (1.0f / (tanf((fov / 2.0f) * 3.1416f / 180.0f)));
	float xScale = yScale / aspectRatio;
	float frustrumLength = znear - zfar;

	return Matrix4x4(xScale, 0.0f, 0.0f, 0.0f,
		0.0f, yScale, 0.0f, 0.0f,
		0.0f, 0.0f, ((znear + zfar) / (frustrumLength)), ((2.0f * zfar * znear) / (frustrumLength)),
		0.0f, 0.0f, -1.0f, 0.0f).Transpose();
	


}

inline Matrix4x4 Matrix4x4::Translate(const Vector3& distance){
	
	float newM[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		distance.x, distance.y, distance.z, 1.0f };
	Matrix4x4 transMat = Matrix4x4(newM);

	return transMat;
}

inline Matrix4x4 Matrix4x4::Translate(float x, float y, float z){
	
	float newM[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
					   0.0f, 1.0f, 0.0f, 0.0f,
					   0.0f, 0.0f, 1.0f, 0.0f,
						  x,	y,	  z, 1.0f };
	Matrix4x4 transMat = Matrix4x4(newM);

	return transMat;
}

inline Matrix4x4 Matrix4x4::Scale(const Vector3& scale){
	
	float newM[16] = { scale.x, 0.0f, 0.0f, 0.0f,
						0.0f, scale.y, 0.0f, 0.0f,
						0.0f, 0.0f, scale.z, 0.0f,
						0.0f, 0.0f, 0.0f, 1 };
	Matrix4x4 scaleMat = Matrix4x4(newM);
	return scaleMat;
}

inline Matrix4x4 Matrix4x4::Scale(float x, float y, float z){
	
	float newM[16] = { x, 0.0f, 0.0f, 0.0f,
					0.0f, y, 0.0f, 0.0f,
					0.0f, 0.0f, z, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f };
	Matrix4x4 scaleMat = Matrix4x4(newM);
	return scaleMat;
}

inline Matrix4x4 Matrix4x4::RotateX(float radians){

	float sinCalc = sinf(radians);
	float cosCalc = cosf(radians);
	
	float newM[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
					  0.0f, cosCalc, -sinCalc, 0.0f,
					  0.0f, sinCalc, cosCalc, 0.0f,
					  0.0f, 0.0f, 0.0f, 1.0f };
	Matrix4x4 rotateX = Matrix4x4(newM);
	return rotateX;
}

inline Matrix4x4 Matrix4x4::RotateY(float radians){

	float sinCalc = sinf(radians);
	float cosCalc = cosf(radians);
	
	float newM[16] = { cosCalc, 0.0f, sinCalc, 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						-sinCalc, 0.0f, cosCalc, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f };

	Matrix4x4 rotateY = Matrix4x4(newM);
	return rotateY;
}

inline Matrix4x4 Matrix4x4::RotateZ(float radians) {

	float sinCalc = sinf(radians);
	float cosCalc = cosf(radians);
	
	float newM[16] = { cosCalc, -sinCalc, 0.0f, 0.0f,
					sinCalc, cosCalc, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f };

	Matrix4x4 rotateZ = Matrix4x4(newM);
	return rotateZ;
}

inline Matrix4x4 Matrix4x4::GetTransform(const Vector3& translate,
								const Vector3& scale,
								float rotateX, float rotateY,
								float rotateZ)   {

  Matrix4x4 model = model.Identity();

  Matrix4x4 scaleM = scaleM.Identity().Multiply(scaleM.Scale(scale.x, scale.y, scale.z));
  
  Matrix4x4 rotationM = rotationM.Identity().Multiply(rotationM.RotateX(rotateX));
  rotationM = rotationM.Multiply(rotationM.RotateY(rotateY));
  rotationM = rotationM.Multiply(rotationM.RotateZ(rotateZ));

  Matrix4x4 translationM = translationM.Identity().Multiply(translationM.Translate(translate.x, translate.y, translate.z));
 
  model = scaleM.Multiply(rotationM);
  model = model.Multiply(translationM);

  return model;
}

inline Matrix4x4 Matrix4x4::GetTransform(float trans_x, float trans_y, float trans_z,
	float scale_x, float scale_y, float scale_Z,
	float rotateX, float rotateY, float rotateZ)  {
	
	Matrix4x4 rotateMat = Matrix4x4::RotateX(rotateX);
	rotateMat = rotateMat.Multiply(Matrix4x4::RotateY(rotateY));
	rotateMat = rotateMat.Multiply(Matrix4x4::RotateZ(rotateZ));

	Matrix4x4 scaleMat = Matrix4x4::Scale(scale_x, scale_y, scale_Z);
	Matrix4x4 translateMat = Matrix4x4::Translate(trans_x, trans_y, trans_z);

	Matrix4x4 transform = translateMat.Multiply(rotateMat);
	transform = transform.Multiply(scaleMat);

	return transform;

}

inline Vector4 Matrix4x4::GetColum(int colum) const {
	Vector4 colVec;

	colVec.x = m[colum];
	colVec.y = m[colum + 4];
	colVec.z = m[colum + 8];
	colVec.w = m[colum + 12];

	return colVec;
}

inline Vector4 Matrix4x4::GetLine(int line) const {
	Vector4 lineVec;

	lineVec.x = m[line*4];
	lineVec.y = m[line*4 + 1];
	lineVec.z = m[line*4 + 2];
	lineVec.w = m[line*4 + 3];

	return lineVec;
}

inline Matrix4x4 Matrix4x4::PerspectiveMatrix(float fov, float aspect,
											float near, float far) const {
	float tanResult = (float)tan((fov / 2)*3.141592/180);
	float d = (1 / tanResult);
	float frustrumLength = near - far;

	return Matrix4x4(d / aspect, 0.0f,		0.0f,	0.0f,
					0.0f,		d,			0.0f,	0.0f,
					0.0f,		0.0f,	(near + far) / (frustrumLength), ((2 * far * near) / (frustrumLength)),
					0.0f,		 0.0f,		-1.0f,	 0.0f);
}

inline Matrix4x4 Matrix4x4::OrthoMatrix(float right, float left, float top, float valueottom,
	float near, float far) const {

	return Matrix4x4(2/(right-left),	0.0f,					0.0f,		-((right+left)/(right-left)),
					0.0f,		2/(top-valueottom),				0.0f,		-((top + valueottom) / (top - valueottom)),
					0.0f,				0.0f,			-2 / (far - near),  -((far + near) / (far - near)),
					0.0f,				0.0f,					0.0f,					1.0f);
}



inline Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const {
	Matrix4x4 result;
	for (int i = 0; i < 16; i++)
	{
		result.m[i] = this->m[i] + other.m[i];
	}
	return result;
}

inline Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& other) {
	for (int i = 0; i < 16; i++)
	{
		this->m[i] += other.m[i];
	}
}

inline Matrix4x4 Matrix4x4::operator+(float value) const {
	Matrix4x4 result;
	for (int i = 0; i < 16; i++)
	{
		result.m[i] = this->m[i] + value;
	}
	return result;
}

inline Matrix4x4& Matrix4x4::operator+=(float value) {
	for (int i = 0; i < 16; i++)
	{
		m[i] += value;
	}
}

inline Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const {
	Matrix4x4 result;
	for (int i = 0; i < 16; i++)
	{
		result.m[i] = this->m[i] - other.m[i];
	}
	return result;
}

inline Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& other) {
	for (int i = 0; i < 16; i++)
	{
		this->m[i] -= other.m[i];
	}
}

inline Matrix4x4 Matrix4x4::operator-(float value) const {
	Matrix4x4 result;
	for (int i = 0; i < 16; i++)
	{
		result.m[i] = this->m[i] - value;
	}
	return result;
}

inline Matrix4x4& Matrix4x4::operator-=(float value) {
	for (int i = 0; i < 16; i++)
	{
		m[i] -= value;
	}
}

inline Matrix4x4& Matrix4x4::operator*=(float value) {
	for (int i = 0; i < 16; i++)
	{
		m[i] *= value;
	}
}

inline Matrix4x4 Matrix4x4::operator*(float value) const  {
	Matrix4x4 result;
	for (int i = 0; i < 16; i++)
	{
		result.m[i] = this->m[i] * value;
	}
	return result;
}

inline Matrix4x4& Matrix4x4::operator/=(float value) {
	for (int i = 0; i < 16; i++)
	{
		m[i] /= value;
	}
}

inline Matrix4x4 Matrix4x4::operator/(float value) const {
	Matrix4x4 result;
	for (int i = 0; i < 16; i++)
	{
		result.m[i] = this->m[i] / value;
	}
	return result;
}

inline bool Matrix4x4::operator==(const Matrix4x4& other) {
	for (int i = 0; i < 16; i++)
	{
		if (this->m[i] != other.m[i])
		{
			return false;
		}
	}
	return true;
}

inline bool Matrix4x4::operator!=(const Matrix4x4& other) {
	for (int i = 0; i < 16; i++)
	{
		if (this->m[i] != other.m[i])
		{
			return true;
		}
	}
	return false;
}

inline void Matrix4x4::operator=(const Matrix4x4& other) {
	for (int i = 0; i < 16; i++)
	{
		this->m[i] = other.m[i];
	}
}

#endif
