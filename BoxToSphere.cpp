#include "BoxToSphere.h"
#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG
#include <cmath>
#include <Novice.h>

bool BoxToSphere::IsCollision(const AABB& aabb, const Sphere& sphere) { 
	auto [minX, maxX] = std::minmax(aabb.min.x, aabb.max.x);
	auto [minY, maxY] = std::minmax(aabb.min.y, aabb.max.y);
	auto [minZ, maxZ] = std::minmax(aabb.min.z, aabb.max.z);
	
	Vector3 clossPoint{
	    std::clamp(sphere.center.x, minX, maxX),
	    std::clamp(sphere.center.y, minY, maxY),
	    std::clamp(sphere.center.z, minZ, maxZ),
	};

	Vector3 diff{
		clossPoint.x - sphere.center.x,
		clossPoint.y - sphere.center.y,
		clossPoint.z - sphere.center.z,
	};

	float dlstnce = vector3Mas_.Length(diff);
	
	if (dlstnce <= sphere.radius) {
		return true;
	}

	return false; }

void BoxToSphere::Initialize() { 
	aabb_ = {
	    .min{-0.5f, -0.5f, -0.5f},
	    .max{0.0f,  0.0f,  0.0f },
	};

	sphere_.center = {0.0f, 0.0f, 0.0f};
	sphere_.radius = 1.0f;
}

void BoxToSphere::Update() { isCollision_ = IsCollision(aabb_,sphere_); }
#ifdef _DEBUG
void BoxToSphere::ImguiUpdate() { 
	ImGui::DragFloat3("AABB Min", &aabb_.min.x, 0.01f);
	ImGui::DragFloat3("AABB Max", &aabb_.max.x, 0.01f);
	ImGui::DragFloat3("Sphere Center", &sphere_.center.x, 0.01f);
	ImGui::DragFloat("Sphere Radius", &sphere_.radius, 0.01f);
}
#endif // _DEBUG
void BoxToSphere::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix) {
	uint32_t color = isCollision_ ? RED : WHITE;
	box_.DrawAABB(aabb_,viewProjectionMatrix,viewPortMatrix,color);
	gridSphere_.DrawSphere(sphere_,viewProjectionMatrix,viewPortMatrix,WHITE);
}
