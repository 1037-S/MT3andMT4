#pragma once
#include "Object.h"
#include "Matrix4.h"
#include "Vector3Mas.h"
#include "QuaternionRotate.h"
#include <cmath>
#include <algorithm>

class QuaternionRotate2 {
public:
	// 球面線形補間
	Quaternion Slerp(const Quaternion& q0, const Quaternion& q1,float t);

	void Initialize();

	void Update();

	void Draw();

private:
	QuaternionClass quaternion_;
	QuaternionRotate qr1_;

	Quaternion rotation0_;
	Quaternion rotation1_;

	Quaternion interpolate0_;
	Quaternion interpolate1_;
	Quaternion interpolate2_;
	Quaternion interpolate3_;
	Quaternion interpolate4_;

};
