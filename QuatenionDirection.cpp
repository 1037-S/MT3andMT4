#include "QuatenionDirection.h"
#include <cmath>

Quaternion QuatenionDirection::DirectionToDirection(const Vector3& from, const Vector3& to) {
	float dot = vector3Mas_.Dot(from, to);
	Vector3 cross = polygon_.Cross(from, to);
	Quaternion rotation = {cross.x, cross.y, cross.z, 1.0f+dot};	

	const float tolerance = 1.0e-6f;
	
	if (dot >= 1.0f - tolerance) {
		return Quaternion{0.0f, 0.0f, 0.0f, 1.0f}; // 単位クォータニオン（回転なし）
	}

	if (dot <= -1.0f + tolerance) {
		Vector3 referenceAxis = (std::abs(from.x) < 0.9f) ? Vector3{1.0f, 0.0f, 0.0f} : Vector3{0.0f, 1.0f, 0.0f};

		// from に直交する回転軸を求めて正規化
		Vector3 axis = vector3Mas_.Normalize(polygon_.Cross(from, referenceAxis));

		return Quaternion{axis.x, axis.y, axis.z, 0.0f};
	}

	return qClass_.Normalize(rotation); }

void QuatenionDirection::Initialize() {

	form0_ = vector3Mas_.Normalize(Vector3{1.0f, 0.7f, 0.5f});
	to0_ = -form0_;
	form1_ = vector3Mas_.Normalize(Vector3{-0.6f, 0.9f, 0.2f});
	to1_ = vector3Mas_.Normalize(Vector3{0.4f, 0.7f, -0.5f});
}

void QuatenionDirection::Update() {

	rotateMatrix0_ = qRotate_.MakeRotateMatrix(DirectionToDirection(
		vector3Mas_.Normalize(Vector3{1.0f, 0.0f, 0.0f}), 
		vector3Mas_.Normalize(Vector3{-1.0f, 0.0f, 0.0f})));
	
	rotateMatrix1_ = qRotate_.MakeRotateMatrix(DirectionToDirection(form0_, to0_));
	rotateMatrix2_ = qRotate_.MakeRotateMatrix(DirectionToDirection(form1_, to1_));
}

void QuatenionDirection::Draw() { 
	matrix4_.MatrixScreenPrintf(0, kRowHeight * 1, rotateMatrix0_, "rotateMatrix0"); 
	matrix4_.MatrixScreenPrintf(0, kRowHeight * 6, rotateMatrix1_, "rotateMatrix1"); 
	matrix4_.MatrixScreenPrintf(0, kRowHeight * 11, rotateMatrix2_, "rotateMatrix2"); 
}
