#pragma once
#include "Object.h"
#include "Matrix4.h"
#include "Vector3Mas.h"
#include "MakeMatrix.h"
#include "Quaternion.h"

class QuaternionRotate {
public:

	// 任意軸回転を表すQuaternionの生成
	Quaternion MakeRotateAxisAxisAngleQuaternion(
		const Vector3& axis, float angle);
	// ベクトルをQuaternionで回転させた結果のベクトルを求める
	Vector3 RotateVector(
		const Vector3& vector, const Quaternion& quaternion);
	// Quaternionから回転行列を求める
	Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion);

	void Initialize();
#ifdef _DEBUG
	void ImguiUpdate();
#endif // _DEBUG
	void Update();
	void Draw();

private:

	Matrix4 matrix4_;
	Vector3Mas vector3Mas_;
	MakeMatrix makeMatrix_;
	QuaternionClass qClass_;

	Quaternion rotation_;
	Vector3 pointY_;
	Matrix4x4 rotateMatrix_;
	Vector3 rotateByQuaternion_;
	Vector3 rotateByMatrix_;

};
