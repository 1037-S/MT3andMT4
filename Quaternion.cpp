#include "Quaternion.h"
#include <Novice.h>
#include <cmath>

// Quaternionの積
Quaternion QuaternionClass::Multiply(const Quaternion& lhs, const Quaternion& rhs) { 
	Quaternion result = {};

	result.x = lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y;
	result.y = lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x;
	result.z = lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w;
	result.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;

	return result;
}
// 乗法単位元を返す
Quaternion QuaternionClass::IdentityQuaternion() { 
	Quaternion result = {};


	result.w = 1.0f;
	

	return result;
}
// 共役Quaternionを返す
Quaternion QuaternionClass::Conjugate(const Quaternion& quaternion) { 
	Quaternion result = {};

	result.x = -quaternion.x;
	result.y = -quaternion.y;
	result.z = -quaternion.z;
	result.w = quaternion.w;

	return result;
}
// Quaternionのnormを返す
float QuaternionClass::Norm(const Quaternion& quaternion) { 
	float result = {};

	result = std::sqrtf(
		quaternion.w * quaternion.w + 
		quaternion.x * quaternion.x + 
		quaternion.y * quaternion.y +
		quaternion.z * quaternion.z);

	return result;
}
// 正規化したQuaternionを返す
Quaternion QuaternionClass::Normalize(const Quaternion& quaternion) { 
	Quaternion result = {};

	// ノルム（長さ）を計算
	float norm = Norm(quaternion);

	// 0での除算を防止
	if (norm > 0.0f) {
		float invNorm = 1.0f / norm; // 割り算の回数を減らすため逆数を掛ける
		result.x = quaternion.x * invNorm;
		result.y = quaternion.y * invNorm;
		result.z = quaternion.z * invNorm;
		result.w = quaternion.w * invNorm;
	} else {
		// ノルムが0（または極めて0に近い）の場合は単位クォータニオン等を返す
		result = IdentityQuaternion();
	}

	return result;
}
// 逆Quaternionを返す
Quaternion QuaternionClass::Inverase(const Quaternion& quaternion) { 
	Quaternion result = {};

	// ノルムの二乗（w^2 + x^2 + y^2 + z^2）を計算
	float normSq = quaternion.w * quaternion.w + quaternion.x * quaternion.x + quaternion.y * quaternion.y + quaternion.z * quaternion.z;

	// 0での除算を防止
	if (normSq > 0.0f) {
		float invNormSq = 1.0f / normSq;
		result.x = -quaternion.x * invNormSq;
		result.y = -quaternion.y * invNormSq;
		result.z = -quaternion.z * invNormSq;
		result.w = quaternion.w * invNormSq;
	} else {
		// ノルムが0の場合は単位クォータニオン等を返す
		result = IdentityQuaternion();
	}

	return result;
}

void QuaternionClass::QuaternionScreenPrintf(
	int x, int y,
	const Quaternion& quaternion,
	const char* label) 
{
	Novice::ScreenPrintf(x, y, "%.02f", quaternion.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", quaternion.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", quaternion.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%.02f", quaternion.w);
	Novice::ScreenPrintf(x + kColumnWidth * 4, y, "%s", label);
}

void QuaternionClass::Initialize() { 
	q1_ = {2.0f,3.0f,4.0f,1.0f};
	q2_ = {1.0f,3.0f,5.0f,2.0f};
}

#ifdef _DEBUG
void QuaternionClass::ImguiUpdate() {}
#endif // _DEBUG
void QuaternionClass::Update() {

	identity_ = IdentityQuaternion();
	conj_ = Conjugate(q1_);
	inv_ = Inverase(q1_);
	normal_ = Normalize(q1_);
	mul1_ = Multiply(q1_, q2_);
	mul2_ = Multiply(q2_, q1_);
	norm_ = Norm(q1_);

}

void QuaternionClass::Draw() {
	// VectorScreenPrintf(0, 0, resultAdd_, " : Add");
	// VectorScreenPrintf(0, kRowHeight, resultSubtract_, ": Subtract");
	// VectorScreenPrintf(0, kRowHeight * 2, resultMultiply_, ": Multiply");
	QuaternionScreenPrintf(0, 0, identity_ ,": Identity");
	QuaternionScreenPrintf(0, kRowHeight, conj_, ": Conjugate");
	QuaternionScreenPrintf(0, kRowHeight * 2, inv_, ": Inverase");
	QuaternionScreenPrintf(0, kRowHeight * 3, normal_, ": Normalize");
	QuaternionScreenPrintf(0, kRowHeight * 4, mul1_, ": Multiply(q1_, q2_)");
	QuaternionScreenPrintf(0, kRowHeight * 5, mul2_, ": Multiply(q2_, q1_)");
	Novice::ScreenPrintf(0, kRowHeight * 6, "%.02f : Norm", norm_);
}
