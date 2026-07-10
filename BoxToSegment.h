#pragma once
#include "Object.h"
#include "Vectol.h"
#include "BoxA.h"
#include "Vector3Mas.h"

class BoxToSegment {
public:
	bool IsCollision(const AABB& aabb, const Segment& segment);

	void Initialize();
	void Update();
#ifdef _DEBUG
	void ImguiUpdate();
#endif // _DEBUG
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix);


private:
	Vector3Mas vector3Mas_;
	AABB aabb_;
	Segment segment_;
	Vectol vectol_;
	BoxA box_;

	bool isCollision_;
};


