#pragma once
#include "Object.h"
#include "Matrix4.h"
#include "RringPlineVer2.h"
#include "Rotate.h"
#include "POLYGON.h"
#include "MakeMatrix.h"
#include <cmath>


class GRID {


public:

	~GRID();
	
	// グリッド
	void DrawGrid(const Matrix4x4& viewProjectMatrix, const Matrix4x4& viewportMatrix);
	// 球体
	void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectMatrix, const Matrix4x4& viewportMatrix,uint32_t color);

	void Initialize();
	void Update();
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix);

private:
	Matrix4 m4_;
	MakeMatrix MM_;
	WorldM4 wm4_;
	POLYGON polygon_;
	Rotate rtt_;
	RringPlineVer2 RPV2_;
	const Vector3 CameraPos_ = {0.0f, 0.0f, -10.0f};
	Vector3 rotate{};
	Vector3 translate{};
	Matrix4x4 cameraMatrix_;
	Matrix4x4 worldMatrix_ ;
	Matrix4x4 viewMatrix_;
	Matrix4x4 projectionMatrix_ ;
	//  WorldViewProjectionMatrix、略してWVPMatrixを作る
	Matrix4x4 viewProjectionMatrix_;
	Matrix4x4 viewPortMatrix_ ;
	Vector3 cameraTranslate_{0.0f,1.9f,-6.49f};
	Vector3 cameraRotate_{0.26f,0.0f,0.0f};
	Sphere sphere_;
	float phi_;
};