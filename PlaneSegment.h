#pragma once
#include "Object.h"
#include "Vectol.h"
#include "PlaneSphere.h"
#include "Matrix4.h"
#include "Vector3Mas.h"

class PlaneSegment {
public:
	
	bool IsCollision(const Segment& segment,const Plane& plane);

	void Initialize();
	void Update();
#ifdef _DEBUG
	void ImguiUpdate();
#endif // _DEBUG
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix);

private:
	Segment segment_;
	Line line_;
	Ray ray_;
	Plane plane_;
	Vectol vectol_;
	Vector3Mas vector3Mas_;
	PlaneSphere planeSphere_;
	bool isCollition_;
};

