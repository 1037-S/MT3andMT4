#include "Tangle.h"
#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG
#include <Novice.h>


bool Tangle::IsCollision(const Triangle& triangle, const Segment& segment , const Plane& plane) {

	float dot = vector3Mas_.Dot(segment.diff, plane.normal);

	if (dot == 0.0f) {
		return false;
	}

	float t = (plane.distance - vector3Mas_.Dot(segment.origin, plane.normal)) / dot;

	if (t < 0.0f || t > 1.0f) {
		return false;
	}

	Vector3 p = {
		segment.origin.x + segment.diff.x * t,
		segment.origin.y + segment.diff.y * t,
		segment.origin.z + segment.diff.z * t,
	
	};
	
	
	Vector3 v01 = vector3Mas_.Subtract(triangle.vertices[1], triangle.vertices[0]);
	Vector3 v12 = vector3Mas_.Subtract(triangle.vertices[2], triangle.vertices[1]);
	Vector3 v20 = vector3Mas_.Subtract(triangle.vertices[0], triangle.vertices[2]);
	


	Vector3 v0p = vector3Mas_.Subtract(p, triangle.vertices[0]);
	Vector3 v1p = vector3Mas_.Subtract(p, triangle.vertices[1]);
	Vector3 v2p = vector3Mas_.Subtract(p, triangle.vertices[2]);


	Vector3 closs01 = closs_.Cross(v01,v0p);
	Vector3 closs12 = closs_.Cross(v12,v1p);
	Vector3 closs20 = closs_.Cross(v20,v2p);
	
	if (
		vector3Mas_.Dot(closs01,plane.normal) >= 0.0f&&
		vector3Mas_.Dot(closs12,plane.normal) >= 0.0f&&
		vector3Mas_.Dot(closs20,plane.normal) >= 0.0f
		) {
		return true;
	}
	
	
	return false;
}

void Tangle::DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix, uint32_t color) {
	// 3つの頂点分、スクリーン座標に変換した結果を格納する配列
	Vector3 screenVertices[3];

	// 各頂点を 3D空間 -> ビュープロジェクション空間 -> スクリーン空間 へ変換
	for (int i = 0; i < 3; ++i) {
		screenVertices[i] = makeMatrix_.Transform(makeMatrix_.Transform(triangle.vertices[i], viewProjectionMatrix), viewPortMatrix);
	}

	// Noviceの三角形描画関数を使って画面に描画
	// ※引数は (x1, y1, x2, y2, x3, y3, 色, 塗りつぶしモード) です
	Novice::DrawTriangle(
	    int(screenVertices[0].x), int(screenVertices[0].y), int(screenVertices[1].x), int(screenVertices[1].y), int(screenVertices[2].x), int(screenVertices[2].y), color,
	    kFillModeWireFrame // 最初はワイヤーフレーム（線だけ）にすると、裏側や交点が見やすくておすすめです
	);

}

void Tangle::Initialize() {
	triangle_.vertices[0] = {0.0f, 1.0f, 0.0f};   // 頂点0：上
	triangle_.vertices[1] = {1.0f, -1.0f, 0.0f};  // 頂点1：右下
	triangle_.vertices[2] = {-1.0f, -1.0f, 0.0f}; // 頂点2：左下
	segment_ = {
	    {0.0f, 0.0f, -2.0f},
        {0.0f,  0.0f,  2.0f}
    };
	plane_.normal = {0.0f, 0.0f, -1.0f};
	plane_.distance = 0.0f;
}

void Tangle::Update() {
	
	

	isCollition_ = IsCollision(triangle_,segment_,plane_); }
#ifdef _DEBUG
void Tangle::ImguiUpdate() {
	ImGui::DragFloat3("triangle vertices[0]", (float*)&triangle_.vertices[0], 0.1f); 
	ImGui::DragFloat3("triangle vertices[1]", (float*)&triangle_.vertices[1], 0.1f); 
	ImGui::DragFloat3("triangle vertices[2]", (float*)&triangle_.vertices[2], 0.1f); 
	ImGui::DragFloat3("segment origin", (float*)&segment_.origin, 0.1f);
	ImGui::DragFloat3("segment Diff", (float*)&segment_.diff, 0.1f);
}
#endif // _DEBUG
void Tangle::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix) {
	// 衝突状態によって色を変える
	uint32_t color = isCollition_ ? RED : WHITE;

	// 三角形を描画
	DrawTriangle(triangle_, viewProjectionMatrix, viewPortMatrix, WHITE);

	// 線分（Vectol）も一緒に描画する
	vectol_.Draw(segment_, color, viewProjectionMatrix, viewPortMatrix);
}
