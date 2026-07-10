#include "BoxA.h"
#include <Novice.h>
#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG



bool BoxA::IsCollision(const AABB& aabb1, const AABB& aabb2) { 

	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) && 
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) && 
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)) {
		return true;
	}
	
	return false; }

void BoxA::DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	// 1. AABBのローカル/ワールド8頂点を定義
	Vector3 vertices[8] = {
	    {aabb.min.x, aabb.min.y, aabb.min.z}, // 0: 左下前
	    {aabb.max.x, aabb.min.y, aabb.min.z}, // 1: 右下前
	    {aabb.min.x, aabb.max.y, aabb.min.z}, // 2: 左上前
	    {aabb.max.x, aabb.max.y, aabb.min.z}, // 3: 右上前
	    {aabb.min.x, aabb.min.y, aabb.max.z}, // 4: 左下奥
	    {aabb.max.x, aabb.min.y, aabb.max.z}, // 5: 右下奥
	    {aabb.min.x, aabb.max.y, aabb.max.z}, // 6: 左上奥
	    {aabb.max.x, aabb.max.y, aabb.max.z}  // 7: 右上奥
	};

// 2. 8つの頂点をスクリーン座標に変換する
	Vector3 screenVertices[8];
	for (int i = 0; i < 8; ++i) {
		// ① まずビュープロジェクション行列でカメラ・画面空間（正規化デバイス座標系）へ変換
		Vector3 ndcVertex = makeMatrix_.Transform(vertices[i], viewProjectMatrix);

		// ② 次にビューポート行列で実際のスクリーン座標（ピクセル単位）へ変換
		screenVertices[i] = makeMatrix_.Transform(ndcVertex, viewportMatrix);
	}

	// 3. 12本の辺をループや個別指定で描画する
	// 前面 (Z min側)
	Novice::DrawLine((int)screenVertices[0].x, (int)screenVertices[0].y, (int)screenVertices[1].x, (int)screenVertices[1].y, color);
	Novice::DrawLine((int)screenVertices[1].x, (int)screenVertices[1].y, (int)screenVertices[3].x, (int)screenVertices[3].y, color);
	Novice::DrawLine((int)screenVertices[3].x, (int)screenVertices[3].y, (int)screenVertices[2].x, (int)screenVertices[2].y, color);
	Novice::DrawLine((int)screenVertices[2].x, (int)screenVertices[2].y, (int)screenVertices[0].x, (int)screenVertices[0].y, color);

	// 後面 (Z max側)
	Novice::DrawLine((int)screenVertices[4].x, (int)screenVertices[4].y, (int)screenVertices[5].x, (int)screenVertices[5].y, color);
	Novice::DrawLine((int)screenVertices[5].x, (int)screenVertices[5].y, (int)screenVertices[7].x, (int)screenVertices[7].y, color);
	Novice::DrawLine((int)screenVertices[7].x, (int)screenVertices[7].y, (int)screenVertices[6].x, (int)screenVertices[6].y, color);
	Novice::DrawLine((int)screenVertices[6].x, (int)screenVertices[6].y, (int)screenVertices[4].x, (int)screenVertices[4].y, color);

	// 前面と後面を繋ぐ辺
	Novice::DrawLine((int)screenVertices[0].x, (int)screenVertices[0].y, (int)screenVertices[4].x, (int)screenVertices[4].y, color);
	Novice::DrawLine((int)screenVertices[1].x, (int)screenVertices[1].y, (int)screenVertices[5].x, (int)screenVertices[5].y, color);
	Novice::DrawLine((int)screenVertices[2].x, (int)screenVertices[2].y, (int)screenVertices[6].x, (int)screenVertices[6].y, color);
	Novice::DrawLine((int)screenVertices[3].x, (int)screenVertices[3].y, (int)screenVertices[7].x, (int)screenVertices[7].y, color);
}

void BoxA::Initialize() {
	aabb1_ = {
	    .min{-0.5f, -0.5f, -0.5f },
	    .max{ 0.0f,  0.0f,  0.0f },
	};

	aabb2_ = {
	    .min{ 0.2f, 0.2f, 0.2f},
	    .max{ 1.0f, 1.0f, 1.0f },
	};
}

void BoxA::Update() {
	isCollision_ = IsCollision(aabb1_, aabb2_); }
#ifdef _DEBUG
void BoxA::ImguiUpdate() { 
	ImGui::DragFloat3("AABB1 Min", &aabb1_.min.x,0.01f); 
	ImGui::DragFloat3("AABB1 Max", &aabb1_.max.x,0.01f); 
	ImGui::DragFloat3("AABB2 Min", &aabb2_.min.x,0.01f); 
	ImGui::DragFloat3("AABB2 Max", &aabb2_.max.x,0.01f); 
	
}
#endif // _DEBUG

void BoxA::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix) {
	uint32_t color = isCollision_ ? RED : WHITE;
	DrawAABB(aabb2_, viewProjectionMatrix, viewPortMatrix, WHITE);
	DrawAABB(aabb1_, viewProjectionMatrix, viewPortMatrix, color);
}
