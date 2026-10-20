#include "QuaternionRotate.h"

#include <cmath>

// 任意軸回転を表すQuaternionの生成
Quaternion QuaternionRotate::MakeRotateAxisAxisAngleQuaternion(const Vector3& axis, float angle) {
	Quaternion result{};

	Vector3 normAxis = vector3Mas_.Normalize(axis);

	float halfAngle = angle / 2.0f;
	float sinHalf = std::sin(halfAngle);
	float cosHalf = std::cos(halfAngle);

	result = {normAxis.x * sinHalf, normAxis.y * sinHalf, normAxis.z * sinHalf, cosHalf};

	return result;
}
// ベクトルをQuaternionで回転させた結果のベクトルを求める
Vector3 QuaternionRotate::RotateVector(const Vector3& vector, const Quaternion& quaternion) {

	Quaternion r = {vector.x, vector.y, vector.z, 0};
	// q*
	Quaternion conj = qClass_.Conjugate(quaternion);

	// 3. q * r を計算
	Quaternion qr = qClass_.Multiply(quaternion,r);
	
	// qrq*を求める
	Quaternion result = qClass_.Multiply(qr,conj);
	
	return {result.x, result.y, result.z};
}
// Quaternionから回転行列を求める
Matrix4x4 QuaternionRotate::MakeRotateMatrix(const Quaternion& quaternion) {
	Matrix4x4 result{};

	result.m[0][0] = 
		  (quaternion.w * quaternion.w)
		+ (quaternion.x * quaternion.x)
		- (quaternion.y * quaternion.y)
		- (quaternion.z * quaternion.z);
	result.m[0][1] = 
		 ((quaternion.x * quaternion.y)
		+ (quaternion.w * quaternion.z))
		* 2.0f;
	result.m[0][2] = 
		 ((quaternion.x * quaternion.z)
		- (quaternion.w * quaternion.y))
		* 2.0f;

	result.m[1][0] = 
		 ((quaternion.x * quaternion.y) 
		- (quaternion.w * quaternion.z)) 
		* 2.0f;
	result.m[1][1] = 
		  (quaternion.w * quaternion.w) 
		- (quaternion.x * quaternion.x)
		+ (quaternion.y * quaternion.y)
		- (quaternion.z * quaternion.z);
	result.m[1][2] = 
		 ((quaternion.z * quaternion.y) 
		+ (quaternion.w * quaternion.x))
		* 2.0f;

	result.m[2][0] = 
		 ((quaternion.x * quaternion.z) 
		+ (quaternion.w * quaternion.y)) 
		* 2.0f;
	result.m[2][1] = 
		 ((quaternion.z * quaternion.y) 
		- (quaternion.w * quaternion.x))
		* 2.0f;
	result.m[2][2] = 
		  (quaternion.w * quaternion.w) 
		- (quaternion.x * quaternion.x) 
		- (quaternion.y * quaternion.y) 
		+ (quaternion.z * quaternion.z);

	result.m[3][3] = 1.0f;

	return result;
}

void QuaternionRotate::Initialize() {
	rotation_ = 
		MakeRotateAxisAxisAngleQuaternion(vector3Mas_.Normalize(Vector3{1.0f,0.4f,-0.2f}),0.45f);
	pointY_ = {2.1f,-0.9f,1.3f};
	

}

#ifdef _DEBUG
void QuaternionRotate::ImguiUpdate() {}
#endif // _DEBUG

void QuaternionRotate::Update() {
	rotateMatrix_ = MakeRotateMatrix(rotation_);
	rotateByQuaternion_ = RotateVector(pointY_, rotation_);
	rotateByMatrix_ = makeMatrix_.Transform(pointY_, rotateMatrix_);
}

void QuaternionRotate::Draw() { 
	qClass_.QuaternionScreenPrintf(0, kRowHeight * 0, rotation_, "   : rotation"); 
matrix4_.MatrixScreenPrintf(0, kRowHeight * 2, rotateMatrix_, "rotateMatrix");
vector3Mas_.VectorScreenPrintf(0, kRowHeight * 6, rotateByQuaternion_, "   : rotateByQuaternion");
vector3Mas_.VectorScreenPrintf(0, kRowHeight * 7, rotateByMatrix_, "   : rotateByMatrix");
}
