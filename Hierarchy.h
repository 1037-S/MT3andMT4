#pragma once
#include "Object.h"
#include "Matrix4.h"
#include "GRID.h"
#include "WorldM4.h"
#include "MakeMatrix.h"

class Hierarchy {
public:
	//~Hierarchy();

	void Initialize();
	void Update();
#ifdef _DEBUG
	void ImguiUpdate();
#endif // _DEBUG
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix);

private:
	Vector3 transletes_[3];
	Vector3 rotates_[3];
	Vector3 scales_[3];

	
	Matrix4 matrix4_;

	MakeMatrix makeMatrix_;

	Matrix4x4 worldMatrixS_;

	Matrix4x4 localMatrixE_;
	Matrix4x4 localMatrixH_;

	Matrix4x4 worldMatrixE_;
	Matrix4x4 worldMatrixH_;

	WorldM4 world_;
	GRID sphered1_;
	GRID sphered2_;
	GRID sphered3_;
	Sphere sphere1_;
	Sphere sphere2_;
	Sphere sphere3_;

	Vector3 start_;
	Vector3 end_;
};
