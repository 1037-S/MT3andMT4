#pragma once
#include "Object.h"
#include "Matrix4.h"
#include "Vector3Mas.h"
#include "Rotate.h"


class OverRood {
public:

	void Initialize();
	void Update();
#ifdef _DEBUG
	void ImguiUpdate();
#endif // _DEBUG
	void Draw();

	

private:
	Rotate rotate_;
	
	Vector3 a_;
	Vector3 b_;
	Vector3 c_;	
	Vector3 d_;
	Vector3 e_;
	Vector3 rotate;
	Matrix4x4 rotateXMatrix;
	Matrix4x4 rotateYMatrix;
	Matrix4x4 rotateZMatrix;
	Matrix4x4 rotateMatrix;


};
