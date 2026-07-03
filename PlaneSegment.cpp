#include "PlaneSegment.h"
#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG
#include <Novice.h>

bool PlaneSegment::IsCollision(const Segment& segment, const Plane& plane) {
	float dot = vector3Mas_.Dot(segment.diff, plane.normal);

	if (dot == 0.0f) {
		return false;
	}

	float t = (plane.distance - vector3Mas_.Dot(segment.origin, plane.normal)) / dot;

	//if (t == -1.0f) {
	//	return true;
	//}
	//if (t == 2.0f) {
	//	return true;
	//}

	return t >= 0.0f && t <= 1.0f;
}

void PlaneSegment::Initialize() {
	plane_.normal = {0.0f, 1.0f, 0.0f};
	plane_.distance = 1.0f;

	 segment_ = {
	     {-2.0f, -1.0f, 0.0f},
	       {3.0f,  2.0f,  2.0f}
	   };
	vectol_.Initialize();
	planeSphere_.Initialize();
}

void PlaneSegment::Update() { isCollition_ = IsCollision(segment_,plane_); }
#ifdef _DEBUG
void PlaneSegment::ImguiUpdate() {
	ImGui::DragFloat3("Plane Normal", &plane_.normal.x, 0.01f);
	ImGui::DragFloat("Plane Distance", &plane_.distance, 0.01f);
	ImGui::DragFloat3("Segment Origin", &segment_.origin.x, 0.01f);
	ImGui::DragFloat3("Segment Diff", &segment_.diff.x, 0.01f);
}
#endif // _DEBUG
void PlaneSegment::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix) {
	planeSphere_.DrawPlane(plane_, viewProjectionMatrix, viewPortMatrix, WHITE);
	uint32_t color = isCollition_ ? RED : WHITE;
	vectol_.Draw(segment_, color,viewProjectionMatrix,viewPortMatrix);
}
