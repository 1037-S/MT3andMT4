#include "POLYGON.h"
#include <Novice.h>

POLYGON::~POLYGON() {}


// クロス積(外積)(ベクトル積とも呼ばれる)
Vector3 POLYGON::Cross(const Vector3& v1, const Vector3& v2) { 
	Vector3 result = {};
	
	result.x = (v1.y * v2.z - v1.z * v2.y);	
	result.y = (v1.z * v2.x - v1.x * v2.z);
	result.z = (v1.x * v2.y - v1.y * v2.x);
	
	return result;
}

void POLYGON::Initialize() { 
	v1_ = {1.2f,-3.9f,2.5f};
	v2_ = {2.8f,0.4f,-1.3f};
	cross_ = Cross(v1_, v2_);
}

void POLYGON::Update(char* keys) {
	rotate.y += 0.05f;
	if (keys[DIK_W]) {
		translate.z -= 0.2f;
	}
	if (keys[DIK_S]) {
		translate.z += 0.2f;
	}
	if (keys[DIK_A]) {
		translate.x -= 0.1f;
	}
	if (keys[DIK_D]) {
		translate.x += 0.1f;
	}
	// 各種行列の計算
	rpv2_.WorldViewPortMatrix(cameraMatrix_,worldMatrix_,viewMatrix_,projectionMatrix_);
	cameraMatrix_ = worldM4_.MakeAffineMatrix({1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, CameraPos_);
	worldMatrix_ = worldM4_.MakeAffineMatrix({1.0f, 1.0f, 1.0f}, rotate, translate);
	viewMatrix_ = m4_.Inverse(cameraMatrix_);
	projectionMatrix_ = rpv2_.MakePerspectiveFovMatrix(0.45f, float(KWindowWidth) / float(KWindowHeight), 0.1f, 100.0f);
	//  WorldViewProjectionMatrix、略してWVPMatrixを作る
	wvpMatrix_ = m4_.Multiply(worldMatrix_, m4_.Multiply(viewMatrix_, projectionMatrix_));
	vpMatrix_ = rpv2_.MakeViewportMatrix(0, 0, float(KWindowWidth), float(KWindowHeight), 0.0f, 1.0f);
	for (uint32_t i = 0; i < 3; ++i) {
		Vector3 ndcVertex = makeMatrix_.Transform(kLocalVertices_[i], wvpMatrix_);
		screenVertices_[i] = makeMatrix_.Transform(ndcVertex,vpMatrix_);
	}
}

void POLYGON::Draw() { 
	V3mas_.VectorScreenPrintf(0, 0, cross_, "cross");
	V3mas_.VectorScreenPrintf(0, 20, screenVertices_[0], "screenVertices_[0]");
	V3mas_.VectorScreenPrintf(0, 40, screenVertices_[1], "screenVertices_[1]");
	V3mas_.VectorScreenPrintf(0, 60, screenVertices_[2], "screenVertices_[2]");
	Novice::DrawTriangle(
		int(screenVertices_[0].x), int(screenVertices_[0].y),
		int(screenVertices_[1].x), int(screenVertices_[1].y), 
		int(screenVertices_[2].x), int(screenVertices_[2].y), 
		RED,kFillModeSolid);
}
