#include "Hierarchy.h"
#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG
#include <Novice.h>

void Hierarchy::Initialize() {
	transletes_[0] = {0.2f, 1.0f, 0.0f};
	transletes_[1] = {0.4f, 0.0f, 0.0f};
	transletes_[2] = {0.3f, 0.0f, 0.0f};
	rotates_[0] = {0.0f, 0.0f, -6.8f};
	rotates_[1] = {0.0f, 0.0f, -1.4f};
	rotates_[2] = {0.0f, 0.0f, 0.0f};
	scales_[0] = {1.0f, 1.0f, 1.0f};
	scales_[1] = {1.0f, 1.0f, 1.0f};
	scales_[2] = {1.0f, 1.0f, 1.0f};
	sphere1_.center = {};
	sphere1_.radius = 0.1f;
	sphere2_.center = {};
	sphere2_.radius = 0.1f;
	sphere3_.center = {};
	sphere3_.radius = 0.1f;
}

void Hierarchy::Update() {
	worldMatrixS_ = world_.MakeAffineMatrix(scales_[0], rotates_[0], transletes_[0]);
	localMatrixE_ = world_.MakeAffineMatrix(scales_[1], rotates_[1], transletes_[1]);
	localMatrixH_ = world_.MakeAffineMatrix(scales_[2], rotates_[2], transletes_[2]);

	worldMatrixE_ = matrix4_.Multiply(localMatrixE_, worldMatrixS_);
	worldMatrixH_ = matrix4_.Multiply(localMatrixH_, worldMatrixE_);
}

#ifdef _DEBUG
void Hierarchy::ImguiUpdate() {
	ImGui::DragFloat3("transletes_[0]", &transletes_[0].x, 0.01f);
	ImGui::DragFloat3("rotates_[0]", &rotates_[0].x, 0.01f);
	ImGui::DragFloat3("scales_[0]", &scales_[0].x, 0.01f);
	ImGui::DragFloat3("transletes_[1]", &transletes_[1].x, 0.01f);
	ImGui::DragFloat3("rotates_[1]", &rotates_[1].x, 0.01f);
	ImGui::DragFloat3("scales_[1]", &scales_[1].x, 0.01f);
	ImGui::DragFloat3("transletes_[2]", &transletes_[2].x, 0.01f);
	ImGui::DragFloat3("rotates_[2]", &rotates_[2].x, 0.01f);
	ImGui::DragFloat3("scales_[2]", &scales_[2].x, 0.01f);
}
#endif // _DEBUG

void Hierarchy::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix) {
	// 1. 各ノードのワールド行列からワールド座標（中心位置）を抽出する
	Vector3 positionS = makeMatrix_.Transform(sphere1_.center, worldMatrixS_); // ルートノード[cite: 7, 8]
	Vector3 positionE = makeMatrix_.Transform(sphere2_.center, worldMatrixE_); // 子ノード[cite: 7, 8]
	Vector3 positionH = makeMatrix_.Transform(sphere3_.center, worldMatrixH_); // 孫・葉ノード[cite: 7, 8]

	// 2. 抽出したワールド座標を球体の中心点（center）に適用する
	Sphere drawSphereS = {positionS, sphere1_.radius}; // ルートの球[cite: 7, 8]
	Sphere drawSphereE = {positionE, sphere2_.radius}; // 子の球[cite: 7, 8]
	Sphere drawSphereH = {positionH, sphere3_.radius}; // 孫の球[cite: 7, 8]

	Vector3 dcS = makeMatrix_.Transform(positionS, viewProjectionMatrix);
	Vector3 screenS = makeMatrix_.Transform(dcS, viewPortMatrix);

	Vector3 dcE = makeMatrix_.Transform(positionE, viewProjectionMatrix);
	Vector3 screenE = makeMatrix_.Transform(dcE, viewPortMatrix);

	Novice::DrawLine((int)screenS.x, (int)screenS.y, (int)screenE.x, (int)screenE.y, WHITE);

	// 子(E) から 孫(H) への線を引く
	Vector3 dcH = makeMatrix_.Transform(positionH, viewProjectionMatrix);
	Vector3 screenH = makeMatrix_.Transform(dcH, viewPortMatrix);

	Novice::DrawLine((int)screenE.x, (int)screenE.y, (int)screenH.x, (int)screenH.y, WHITE);

	sphered1_.DrawSphere(drawSphereS, viewProjectionMatrix, viewPortMatrix, RED);
	sphered2_.DrawSphere(drawSphereE, viewProjectionMatrix, viewPortMatrix, GREEN);
	sphered3_.DrawSphere(drawSphereH, viewProjectionMatrix, viewPortMatrix, BLUE);
}
