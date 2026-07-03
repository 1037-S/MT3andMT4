#include "Vectol.h"
#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG
#include <Novice.h>
#include <algorithm>

Vectol::~Vectol() {}

Vector3 Vectol::project(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};

	float dot = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);

	float nolm = (v2.x * v2.x) + (v2.y * v2.y) + (v2.z * v2.z);

	result.x = (dot / nolm * v2.x);
	result.y = (dot / nolm * v2.y);
	result.z = (dot / nolm * v2.z);

	return result;
}

Vector3 Vectol::ClosestPoint(const Vector3& point, const Segment& segment) {
	Vector3 result{};

	Vector3 a = V3mas_.Subtract(point,segment.origin);
	
	float dot = (a.x * segment.diff.x) + (a.y * segment.diff.y) + (a.z * segment.diff.z);
	float nolm = (segment.diff.x * segment.diff.x) + (segment.diff.y * segment.diff.y) + (segment.diff.z * segment.diff.z);

	float t = 0.0f;
	if (nolm != 0.0f) {

		t = std::clamp(dot / nolm, 0.0f, 1.0f);
		
	}
	result.x = segment.origin.x + segment.diff.x * t;
	result.y = segment.origin.y + segment.diff.y * t;
	result.z = segment.origin.z + segment.diff.z * t;
	return result;
}

void Vectol::Initialize() {
	//segment_ = {
	//    {-2.0f, -1.0f, 0.0f},
 //       {3.0f,  2.0f,  2.0f}
 //   };
	point_ = {-1.5f, 0.6f, 0.6f};

	Sphere_.Initialize();

	//project_ = project(V3mas_.Subtract(point_, segment_.origin), segment_.diff);

	//closestPoint_ = ClosestPoint(point_, segment_);

	// 点の描画
	pointSphere_ = {point_, 0.01f}; // 1cmの弾を描画する
	closestPiontSphere_ = {closestPoint_, 0.01f};
	
}

void Vectol::Update() {
#ifdef _DEBUG
	ImGui::InputFloat3("Project", &project_.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
#endif // _DEBUG
}

void Vectol::Draw(const Segment& segment , uint32_t color, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix) {
	// 点の描画
	//Sphere_.DrawSphere(pointSphere_, viewProjectionMatrix_, viewPortMatrix_, RED);
	//Sphere_.DrawSphere(closestPiontSphere_, viewProjectionMatrix_, viewPortMatrix_, BLACK);
	// 線分の描画
	// 線分の描画
	start_ = MM_.Transform(MM_.Transform(segment.origin, viewProjectionMatrix), viewPortMatrix);
	end_ = MM_.Transform(MM_.Transform(V3mas_.Add(segment.origin, segment.diff), viewProjectionMatrix), viewPortMatrix);
	Novice::DrawLine(int(start_.x), int(start_.y), int(end_.x), int(end_.y), color);
}
