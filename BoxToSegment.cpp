#define NOMINMAX

#include "BoxToSegment.h"
#include <Novice.h>
#include <algorithm>
#include <cmath>
#include <imgui.h>

bool BoxToSegment::IsCollision(const AABB& aabb, const Segment& segment) {
	//float dot = vector3Mas_.Dot(segment.diff,aabb.max);

	//float tXmin = (aabb.min.x - segment.origin.x) / segment.origin.x;
	//float tXmax = (aabb.max.x - segment.origin.x) / segment.diff.x;
	//float tYmin = (aabb.min.y - segment.origin.y) / segment.origin.y;
	//float tYmax = (aabb.max.y - segment.origin.y) / segment.diff.y;
	//float tZmin = (aabb.min.z - segment.origin.z) / segment.origin.z;
	//float tZmax = (aabb.max.z - segment.origin.z) / segment.diff.z;

	//float tNearX = std::min(tXmin, tXmax);
	//float tNearY = std::min(tYmin, tYmax);
	//float tNearZ = std::min(tZmin, tZmax);
	//float tFarX = std::max(tXmin, tXmax);
	//float tFarY = std::max(tYmin, tYmax);
	//float tFarZ = std::max(tZmin, tZmax);
	//  各軸のtの最小・最大値を保持する変数
	float tNearX, tFarX, tNearY, tFarY, tNearZ, tFarZ;

	// 微小な値（ゼロ除算対策）
	const float kEpsilon = 1e-6f;

	// --- X軸の判定 ---
	if (std::abs(segment.diff.x) < kEpsilon) {
		// 線分がX軸に並行な場合、始点がAABBの範囲外なら絶対に当たらない
		if (segment.origin.x < aabb.min.x || segment.origin.x > aabb.max.x)
			return false;
		tNearX = -std::numeric_limits<float>::infinity();
		tFarX = std::numeric_limits<float>::infinity();
	} else {
		float tXmin = (aabb.min.x - segment.origin.x) / segment.diff.x;
		float tXmax = (aabb.max.x - segment.origin.x) / segment.diff.x;
		tNearX = std::min(tXmin, tXmax);
		tFarX = std::max(tXmin, tXmax);
	}

	// --- Y軸の判定 ---
	if (std::abs(segment.diff.y) < kEpsilon) {
		if (segment.origin.y < aabb.min.y || segment.origin.y > aabb.max.y)
			return false;
		tNearY = -std::numeric_limits<float>::infinity();
		tFarY = std::numeric_limits<float>::infinity();
	} else {
		float tYmin = (aabb.min.y - segment.origin.y) / segment.diff.y;
		float tYmax = (aabb.max.y - segment.origin.y) / segment.diff.y;
		tNearY = std::min(tYmin, tYmax);
		tFarY = std::max(tYmin, tYmax); // minになっていたのをmaxに修正
	}

	// --- Z軸の判定 ---
	if (std::abs(segment.diff.z) < kEpsilon) {
		if (segment.origin.z < aabb.min.z || segment.origin.z > aabb.max.z)
			return false;
		tNearZ = -std::numeric_limits<float>::infinity();
		tFarZ = std::numeric_limits<float>::infinity();
	} else {
		float tZmin = (aabb.min.z - segment.origin.z) / segment.diff.z;
		float tZmax = (aabb.max.z - segment.origin.z) / segment.diff.z;
		tNearZ = std::min(tZmin, tZmax);
		tFarZ = std::max(tZmin, tZmax); // minになっていたのをmaxに修正
	}

	// AABBとの衝突点(貫通点)のtが小さい方
	float tmin = std::max(std::max(tNearX, tNearY), tNearZ);
	// AABBとの衝突点(貫通点)のtが大きい方
	float tmax = std::min(std::min(tFarX, tFarY), tFarZ);
	if (tmin <= tmax && tmax >= 0.0f && tmin <= 1.0f) {
		return true;
	}

	return false;
}

void BoxToSegment::Initialize() {
	aabb_ = {
	    .min{-0.5f, -0.5f, -0.5f},
	    .max{0.5f,  0.5f,  0.5f },
	};
	segment_ = {
	    .origin{-0.7f, -0.3f, 0.0f},
	    .diff{2.0f,  -0.5f, 0.0f},
	};
}

void BoxToSegment::Update() { isCollision_ = IsCollision(aabb_, segment_); }

#ifdef _DEBUG
void BoxToSegment::ImguiUpdate() {
	ImGui::DragFloat3("aabb_.min", &aabb_.min.x, 0.01f);
	ImGui::DragFloat3("aabb_.max", &aabb_.max.x, 0.01f);
	ImGui::DragFloat3("segment_.origin", &segment_.origin.x, 0.01f);
	ImGui::DragFloat3("segment_.diff", &segment_.diff.x, 0.01f);
}
#endif // _DEBUG

void BoxToSegment::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix) {
	vectol_.Draw(segment_, WHITE, viewProjectionMatrix, viewPortMatrix);
	uint32_t color = isCollision_ ? RED : WHITE;
	box_.DrawAABB(aabb_, viewProjectionMatrix, viewPortMatrix, color);
}
