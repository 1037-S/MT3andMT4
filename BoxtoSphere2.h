#pragma once
#include "Object.h"
#include "Matrix4.h"
#include "MakeMatrix.h"
#include "Rotate.h"
#include <cmath>

class BoxtoSphere2 {
public:

	
	//bool IsCollision(const OBB& obb, const Sphere& sphere);

	//void DrawOBB(const OBB& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix, uint32_t color);

//	void Initialize();
//	void Update();
//#ifdef _DEBUG
//	void ImguiUpdate();
//#endif // _DEBUG
//	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix);

private:
	bool isCollision_;
	Matrix4 m4_;
	MakeMatrix makeMatrix_;
	Rotate rotate_;
	Matrix4x4 rotateMatrix_;
	Matrix4x4 obbWorldMatrix_;
	Vector3 rotate;
	OBB obb_;
	Sphere sphere_;
};
