#pragma once
#include "Object.h"
#include "Matrix4.h"
#include "Vector3Mas.h"
#include "MakeMatrix.h"
#include "GRID.h"
#include "POLYGON.h"

struct Plane // 平面
{
	Vector3 normal;	//!< 法線(平面の向き) n
	float distance; //!< 距離
};

class PlaneSphere {
public:
	
	bool IsCollision(const Sphere& sphere, const Plane& plane);
	// 平面の描画
	Vector3 Perpendicular(const Vector3& vector);
	void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix,uint32_t color);

	void Initialize();
	void Update();
#ifdef _DEBUG
	void ImguiUpdate();
#endif // _DEBUG
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix);

private:
	GRID grid_;
	Matrix4 matrix4_;
	Vector3Mas vector3Mas_;
	MakeMatrix makeMatrix_;
	POLYGON POLYGON_;

	Plane plane_;
	Sphere sphere_; 

	
	bool isCollision_;
};

