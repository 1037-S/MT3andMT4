#pragma once
#include "Object.h"

class QuaternionClass {
public:

	// Quaternionの積
	Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);
	// 乗法単位元を返す
	Quaternion IdentityQuaternion();
	// 共役Quaternionを返す
	Quaternion Conjugate(const Quaternion& quaternion);
	// Quaternionのnormを返す
	float Norm(const Quaternion& quaternion);
	// 正規化したQuaternionを返す
	Quaternion Normalize(const Quaternion& quaternion);
	// 逆Quaternionを返す
	Quaternion Inverase(const Quaternion& quaternion);
	
	void QuaternionScreenPrintf(int x, int y, const Quaternion& quaternion, const char* label);


	void Initialize();
#ifdef _DEBUG
	void ImguiUpdate();
#endif // _DEBUG
	void Update();
	void Draw();

private:
	Quaternion q1_;
	Quaternion q2_;
	Quaternion identity_;
	Quaternion conj_;
	Quaternion inv_;
	Quaternion normal_;
	Quaternion mul1_;
	Quaternion mul2_;
	float norm_;

};
