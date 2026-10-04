#include "BoxtoSphere2.h"
#include <Novice.h>
#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG





//bool BoxtoSphere2::IsCollision(const OBB& obb, const Sphere& sphere) { 
//	
//
//	return false; }
//
//void BoxtoSphere2::DrawOBB(const OBB& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix, uint32_t color) {}

//void BoxtoSphere2::Initialize() {
//	rotate = {0.0f, 0.0f, 0.0f};
//	obb_ = {
//	.center{-1.0f,0.0f,0.0f},
//	.orientations{
//	{1.0f,0.0f,0.0f},
//	{0.0f,1.0f,0.0f},
//	{0.0f,0.0f,1.0f}
//	}, 
//	.size{
//	0.5f,0.5f,0.5f
//	}
//	};
//	sphere_ = {
//		.center{0.0f,0.0f,0.0f}, 
//		.radius{0.5f}
//	};
//	rotateMatrix_ = 
//		m4_.Multiply(rotate_.MakeRotateXMatrix(rotate.x), 
//		m4_.Multiply(rotate_.MakeRotateYMatrix(rotate.y),
//					 rotate_.MakeRotateZMatrix(rotate.z)));
//
//	
//
//}
//
//void BoxtoSphere2::Update() {
//	Vector3 centerInOBBLocalSpase = makeMatrix_.Transform(sphere_.center, obbWorldMatrix_);
//
//	AABB aabbOBBLocal{obb_.size,obb_.size};
//	
//	//isCollision_ = IsCollision(obb_, sphere_); 
//
//// 回転行列から軸を摘出
//	obb_.orientations[0].x = rotateMatrix_.m[0][0];
//	obb_.orientations[0].y = rotateMatrix_.m[0][1];
//	obb_.orientations[0].z = rotateMatrix_.m[0][2];
//
//	obb_.orientations[1].x = rotateMatrix_.m[1][0];
//	obb_.orientations[1].y = rotateMatrix_.m[1][1];
//	obb_.orientations[1].z = rotateMatrix_.m[1][2];
//
//	obb_.orientations[2].x = rotateMatrix_.m[2][0];
//	obb_.orientations[2].y = rotateMatrix_.m[2][1];
//	obb_.orientations[2].z = rotateMatrix_.m[2][2];
//}
//#ifdef _DEBUG
//void BoxtoSphere2::ImguiUpdate() {}
//#endif // _DEBUG
//void BoxtoSphere2::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix) { uint32_t color = isCollision_ ? RED : WHITE; }
