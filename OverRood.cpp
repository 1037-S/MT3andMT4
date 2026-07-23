#include "OverRood.h"
#include <Novice.h>
#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2) { return Matrix4::Add(m1, m2); }
Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2) { return Matrix4::Subtract(m1, m2); }
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) { return Matrix4::Multiply(m1, m2); }
Vector3 operator+(const Vector3& v1, const Vector3& v2) { return Vector3Mas::Add(v1, v2); }
Vector3 operator-(const Vector3& v1, const Vector3& v2) { return Vector3Mas::Subtract(v1, v2); }
Vector3 operator*(float s, const Vector3& v) { return Vector3Mas::Multiply(s, v); }

void OverRood::Initialize() {
	a_ = {0.2f, 1.0f, 0.0f};
	b_ = {2.4f, 3.1f, 2.2f};
	rotate = {0.4f, 1.43f, -0.0f};
}

void OverRood::Update() {
	c_ = a_ + b_;
	d_ = a_ - b_;
	e_ = 2.4f * a_;
	rotateXMatrix = rotate_.MakeRotateXMatrix(rotate.x);
	rotateYMatrix = rotate_.MakeRotateYMatrix(rotate.y);
	rotateZMatrix = rotate_.MakeRotateZMatrix(rotate.z);
	rotateMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;
}
#ifdef _DEBUG
void OverRood::ImguiUpdate() { 
	
	ImGui::Begin("Window");
	ImGui::Text("c::%f,%f,%f",c_.x,c_.y,c_.z);
	ImGui::Text("d::%f,%f,%f",d_.x,d_.y,d_.z);
	ImGui::Text("e::%f,%f,%f",e_.x,e_.y,e_.z);
	ImGui::Text("matrix\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n", 
		rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2], rotateMatrix.m[0][3],
		rotateMatrix.m[1][0], rotateMatrix.m[1][1], rotateMatrix.m[1][2], rotateMatrix.m[1][3],
		rotateMatrix.m[2][0], rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3],
		rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2], rotateMatrix.m[3][3]
		);
	ImGui::End();
}
#endif // _DEBUG
void OverRood::Draw() {}
