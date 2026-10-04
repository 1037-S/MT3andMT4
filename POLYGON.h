#pragma once
#include "Object.h"
#include "Vector3Mas.h"
#include "Matrix4.h"
#include "WorldM4.h"
#include "MakeMatrix.h"
#include "RringPlineVer2.h"

class POLYGON {
public:
	~POLYGON();

	// クロス積(外積)(ベクトル積とも呼ばれる)
	Vector3 Cross(const Vector3& v1, const Vector3& v2);

	void Initialize();
	void Update(char* keys);
	void Draw();

	//void WorldViewPortMatrix();

private:
	Vector3Mas V3mas_;
	Matrix4 m4_;
	Rotate rotate_;
	WorldM4 worldM4_;
	MakeMatrix makeMatrix_;
	RringPlineVer2 rpv2_;
	
	Vector3 v1_;
	Vector3 v2_;
	Vector3 cross_;
	const Vector3 CameraPos_ = {0.0f, 0.0f, -10.0f};
	Vector3 rotate{};
	Vector3 translate{};
	Matrix4x4 cameraMatrix_;
	Matrix4x4 worldMatrix_;
	Matrix4x4 viewMatrix_;
	Matrix4x4 projectionMatrix_;

	//  WorldViewProjectionMatrix、略してWVPMatrixを作る
	Matrix4x4 wvpMatrix_;
	Matrix4x4 vpMatrix_;
	Vector3 screenVertices_[3];
	const Vector3 kLocalVertices_[3] = 
	{{ 0.0f, 1.0f, 0.0f},
	{ 1.0f,-1.0f, 0.0f},
	{-1.0f,-1.0f, 0.0f},};
};

