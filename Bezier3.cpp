#include "Bezier3.h"
#include <Novice.h>
#include <algorithm>
#include <cmath>
#ifdef _DEBUG
#include<imgui.h>
#endif // _DEBUG


Vector3 Bezier3::Lerp(const Vector3& v1, const Vector3& v2, float t) {
	Vector3 result;

	result.x = t * v1.x + (1.0f - t) * v2.x;
	result.y = t * v1.y + (1.0f - t) * v2.y;
	result.z = t * v1.z + (1.0f - t) * v2.z;

	return result;
}


void Bezier3::DrawBezier(
    const Vector3& controlPoints0, 
	const Vector3& controlPoints1,
	const Vector3& controlPoints2, 
	const Matrix4x4& viewProjectionMatrix, 
	const Matrix4x4& viewPortMatrix, 
	uint32_t color) {

	const int kSubdivisions = 32;

	Vector2 prevScreenPos = {0.0f, 0.0f};
	for (int i = 0; i <= kSubdivisions; ++i) {
		// t を 0.0 から 1.0 まで変化させる
		float t = static_cast<float>(i) / kSubdivisions;
	Vector3 p0p1 = Lerp(controlPoints0, controlPoints1,t);
	Vector3 p1p2 = Lerp(controlPoints1, controlPoints2,t);
	Vector3 p = Lerp(p0p1,p1p2,t);
	Vector3 ndcSpace = makeMatrix_.Transform(p, viewProjectionMatrix); // 疑似コード: WVP変換とw除算
	Vector3 screenSpace = makeMatrix_.Transform(ndcSpace, viewPortMatrix); // 疑似コード: ビューポート変換

	Vector2 currentScreenPos = {screenSpace.x, screenSpace.y};

	// 最初の点(i=0)以外は、前の点と現在の点を線で結ぶ
	if (i > 0) {
		Novice::DrawLine(static_cast<int>(prevScreenPos.x), static_cast<int>(prevScreenPos.y), static_cast<int>(currentScreenPos.x), static_cast<int>(currentScreenPos.y), color);
		
	}

	// 次のループのために現在の座標を保存
	prevScreenPos = currentScreenPos;
	}
}

void Bezier3::Initialize() {
	
	controlPoints_[0] = {-0.8f, 0.58f, 1.0f};
	controlPoints_[1] = {1.76f, 1.0f, -0.3f};
	controlPoints_[2] = {0.94f, -0.7f, -0.3f};
}
void Bezier3::Update() {}

#ifdef _DEBUG
void Bezier3::ImguiUpdate() { 
	ImGui::DragFloat3("controlPoints[0]", &controlPoints_[0].x, 0.01f);
	ImGui::DragFloat3("controlPoints[1]", &controlPoints_[1].x, 0.01f);
	ImGui::DragFloat3("controlPoints[2]", &controlPoints_[2].x, 0.01f);
}
#endif // _DEBUG

void Bezier3::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix) {
	DrawBezier(controlPoints_[0], controlPoints_[1], controlPoints_[2], viewProjectionMatrix, viewPortMatrix, BLUE);
}