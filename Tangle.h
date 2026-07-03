#pragma once
#include "Object.h"
#include "Vector3Mas.h"
#include "Vectol.h"
#include "PlaneSphere.h"
#include "MakeMatrix.h"

#include "POLYGON.h"

struct Triangle {
	Vector3 vertices[3]; //!< 頂点の座標
};

class Tangle {
public:

	bool IsCollision(const Triangle& triangle, const Segment& segment, const Plane& plane);

	void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix, uint32_t color);
	void Initialize();
	void Update();
#ifdef _DEBUG
	void ImguiUpdate();
#endif // _DEBUG
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix);


private:


	Triangle triangle_;
	MakeMatrix makeMatrix_;
	POLYGON closs_;
	Segment segment_;
	Plane plane_;
	Line line_;
	Ray ray_;
	
	Vectol vectol_;
	Vector3Mas vector3Mas_;
	PlaneSphere planeSphere_;
	bool isCollition_;
};
