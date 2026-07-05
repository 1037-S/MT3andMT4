#pragma once
#include "Object.h"
#include "GRID.h"
#include "BoxA.h"
#include "Vector3Mas.h"
#include <algorithm>

class BoxToSphere {
public:

	bool IsCollision(const AABB& aabb,const Sphere& sphere);

	void Initialize();
	void Update();
#ifdef _DEBUG
	void ImguiUpdate();
#endif // _DEBUG
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix);


private:
	AABB aabb_;
	Sphere sphere_;
	GRID gridSphere_;
	BoxA box_;
	Vector3Mas vector3Mas_;
	bool isCollision_;
};

