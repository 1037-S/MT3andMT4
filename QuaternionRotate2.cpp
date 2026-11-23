#include "QuaternionRotate2.h"

Quaternion QuaternionRotate2::Slerp(const Quaternion& q0, const Quaternion& q1, float t) { 
	float dot = q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w;

	Quaternion q0_copy = q0;

	if (dot < 0.0f) {
		q0_copy = -q0_copy; // もう片方の回転を利用
		dot = -dot;	// 内積も反転
	}
	if (dot >= 0.9995f) {
		// 線形補間（Lerp）して正規化する
		Quaternion result = {
			q0_copy.x + t * (q1.x - q0_copy.x), 
			q0_copy.y + t * (q1.y - q0_copy.y),
			q0_copy.z + t * (q1.z - q0_copy.z),
			q0_copy.w + t * (q1.w - q0_copy.w)};
		// 正規化（長さを1にする）※自作のNormalize関数があればそれを使ってください
		float len = std::sqrt(result.x * result.x + result.y * result.y + result.z * result.z + result.w * result.w);
		return {result.x / len, result.y / len, result.z / len, result.w / len};
	}
	// なす角を求める
	dot = std::clamp(dot, -1.0f, 1.0f);
	float theta = std::acos(dot);
	float sinTheta = std::sin(theta);

	// thataとsinを使って補間係数scene0,scene1を求める
	float scale0 = std::sin((1.0f - t) * theta) / sinTheta;
	float scale1 = std::sin(t * theta) / sinTheta;


	// それぞれも補間係数を利用し、補間後のQuaternionを求める
	return scale0 * q0_copy + scale1 * q1;
}

void QuaternionRotate2::Initialize() {
	rotation0_ = qr1_.MakeRotateAxisAxisAngleQuaternion({0.71f,0.71f,0.0f},0.3f);
	rotation1_ = qr1_.MakeRotateAxisAxisAngleQuaternion({0.71f, 0.0f,0.71f}, 3.141592f);
}

void QuaternionRotate2::Update() { 
	interpolate0_ = Slerp(rotation0_, rotation1_,0.0f);
	interpolate1_ = Slerp(rotation0_, rotation1_,0.3f);
	interpolate2_ = Slerp(rotation0_, rotation1_,0.5f);
	interpolate3_ = Slerp(rotation0_, rotation1_,0.7f);
	interpolate4_ = Slerp(rotation0_, rotation1_,1.0f);
}

void QuaternionRotate2::Draw() {

	quaternion_.QuaternionScreenPrintf(0, kRowHeight * 0, interpolate0_, ":interpolate0, Slerp(q0,q1,0.0f)");
	quaternion_.QuaternionScreenPrintf(0, kRowHeight * 1, interpolate1_, ":interpolate1, Slerp(q0,q1,0.3f)");
	quaternion_.QuaternionScreenPrintf(0, kRowHeight * 2, interpolate2_, ":interpolate2, Slerp(q0,q1,0.5f)");
	quaternion_.QuaternionScreenPrintf(0, kRowHeight * 3, interpolate3_, ":interpolate3, Slerp(q0,q1,0.7f)");
	quaternion_.QuaternionScreenPrintf(0, kRowHeight * 4, interpolate4_, ":interpolate4, Slerp(q0,q1,1.0f)");


}
