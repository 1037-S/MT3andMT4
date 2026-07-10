#pragma once
#include "Object.h"
#include "MakeMatrix.h"
#include <cmath>

class Bezier3 {
public:
	Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);

	void DrawBezier(const Vector3& controlPoints0, const Vector3& controlPoints1, const Vector3& controlPoints2, 
			const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix, uint32_t color);

	void Initialize();
	void Update();
#ifdef _DEBUG
	void ImguiUpdate();
#endif // _DEBUG
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix);

private:
	Vector3 controlPoints_[3];
	MakeMatrix makeMatrix_;
};
