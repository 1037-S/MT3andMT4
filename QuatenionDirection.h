#pragma once
#include "Object.h"
#include "Matrix4.h"
#include "Vector3Mas.h"
#include "MakeMatrix.h"
#include "POLYGON.h"
#include "Quaternion.h"
#include "QuaternionRotate.h"
class QuatenionDirection {
public:

	Quaternion DirectionToDirection(const Vector3& from, const Vector3& to);

	void Initialize();
	void Update();
	void Draw();

private:
	Matrix4 matrix4_;
	Vector3Mas vector3Mas_;
	MakeMatrix makeMatrix_;
	POLYGON polygon_;
	QuaternionClass qClass_;
	QuaternionRotate qRotate_;

	Vector3 form0_;
	Vector3 to0_;
	Vector3 form1_;
	Vector3 to1_;
	Matrix4x4 rotateMatrix0_;
	Matrix4x4 rotateMatrix1_;
	Matrix4x4 rotateMatrix2_;
};
