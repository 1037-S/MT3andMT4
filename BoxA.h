#pragma once
#include "Object.h"
#include "Matrix4.h"
#include "Vector3Mas.h"
#include "MakeMatrix.h"
#include <cmath>

class BoxA {
public:
	bool IsCollision(const AABB& aabb1, const AABB& aabb2);

	void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
	void Initialize();
	void Update();
#ifdef _DEBUG
	void ImguiUpdate();
#endif // _DEBUG

	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix);

private:
	AABB aabb1_;
	AABB aabb2_;
	
	Vector3Mas vector3Mas_; 
	MakeMatrix makeMatrix_;

	bool isCollision_;
};

