#include "PlaneSphere.h"
#include <Novice.h>
#include <cmath>
#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG


bool PlaneSphere::IsCollision(const Sphere& sphere, const Plane& plane) {
	
	

	float cn = // 方程式
	vector3Mas_.Dot(sphere.center,plane.normal) ; 
	
	float k = cn - plane.distance; // 符号付き距離(平面との点の距離)

	//float q; // 平面上に下ろした点
	
	return std::abs(k) <= sphere.radius; 

}

Vector3 PlaneSphere::Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return {-vector.y, vector.x, 0.0f};
	}
	return {0.0f, -vector.z, vector.y};
}

void PlaneSphere::DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix, uint32_t color) {
	Vector3 center = vector3Mas_.Multiply(plane.distance, plane.normal); // その1

	Vector3 perpendiculars[4];
	perpendiculars[0] = vector3Mas_.Normalize(Perpendicular(plane.normal));                 // その2
	perpendiculars[1] = {-perpendiculars[0].x, -perpendiculars[0].y, -perpendiculars[0].z}; // その3
	perpendiculars[2] = POLYGON_.Cross(plane.normal, perpendiculars[0]);                    // その4
	perpendiculars[3] = {-perpendiculars[2].x, -perpendiculars[2].y, -perpendiculars[2].z}; // その5
	// その6
	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = vector3Mas_.Multiply(2.0f, perpendiculars[index]);
		Vector3 point = vector3Mas_.Add(center, extend);
		points[index] = makeMatrix_.Transform(makeMatrix_.Transform(point, viewProjectionMatrix), viewPortMatrix);
	}
	Novice::DrawLine((int)points[2].x, (int)points[2].y, (int)points[0].x, (int)points[0].y, color);
	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[3].x, (int)points[3].y, color);
	Novice::DrawLine((int)points[3].x, (int)points[3].y, (int)points[1].x, (int)points[1].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[2].x, (int)points[2].y, color);
}

void PlaneSphere::Initialize() { 
	
	plane_.normal = vector3Mas_.Normalize(plane_.normal);
	//plane_.normal = {0.0f, 1.0f, 0.0f};
	//plane_.distance = 1.0f;

	// 球の初期化
	//sphere_.center = {0.0f, 1.0f, 0.0f};
	//sphere_.radius = 0.5f;
}

void PlaneSphere::Update() {
	isCollision_ = IsCollision(sphere_, plane_);
}
#ifdef _DEBUG
void PlaneSphere::ImguiUpdate() {
	//ImGui::DragFloat3("plane.Normal", &plane_.normal.x, 0.01f);
	//ImGui::DragFloat3("SphereCenter", &sphere_.center.x, 0.01f);
	//ImGui::DragFloat("SphereRadius", &sphere_.radius, 0.01f);
}
#endif // _DEBUG
void PlaneSphere::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix) { 
	
	DrawPlane(plane_,viewProjectionMatrix,viewPortMatrix,WHITE); 
	//uint32_t color = isCollision_ ? RED : WHITE;
	//grid_.DrawSphere(sphere_,viewProjectionMatrix,viewPortMatrix,color);
}
