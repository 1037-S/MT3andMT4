#pragma once
#include "GRID.h"
#include "Object.h"
//#include "Matrix4.h"
#include "MakeMatrix.h"
#include "Vector3Mas.h"
#include <cmath>

struct Line // 直線
{ 
	Vector3 origin; //!< 始点
	Vector3 diff;	//!< 終点の差分ベクトル
};

struct Ray // 半直線
{
	Vector3 origin; //!< 始点
	Vector3 diff;   //!< 終点の差分ベクトル
};

struct Segment // 線分
{
	Vector3 origin; //!< 始点
	Vector3 diff;   //!< 終点の差分ベクトル
};

class Vectol :public GRID{
public:
	~Vectol();

	Vector3 project(const Vector3& v1, const Vector3& v2);
	Vector3 ClosestPoint(const Vector3& point,const Segment& segment);

	void Initialize();
	void Update();
	void Draw(const Segment& segment,uint32_t color, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix);

private:
	Matrix4 m4_;
	Vector3Mas V3mas_;
	MakeMatrix MM_;
	WorldM4 wm4_;
	RringPlineVer2 RPV2_;
	//Segment segment_{};
	Vector3 point_{};
	GRID Sphere_;
	Sphere pointSphere_{};
	Sphere closestPiontSphere_{};
	float phi_ = std::acos(-1.0f);
	const Vector3 CameraPos_ = {0.0f, 0.0f, -10.0f};
	Vector3 rotate{};
	Vector3 translate{};
	Matrix4x4 cameraMatrix_ = wm4_.MakeAffineMatrix({1.0f, 1.0f, 1.0f}, cameraRotate_, cameraTranslate_);
	Matrix4x4 worldMatrix_ = wm4_.MakeAffineMatrix({1.0f, 1.0f, 1.0f}, rotate, translate);
	Matrix4x4 viewMatrix_ = m4_.Inverse(cameraMatrix_);
	Matrix4x4 projectionMatrix_ = RPV2_.MakePerspectiveFovMatrix(0.45f, float(KWindowWidth) / float(KWindowHeight), 0.1f, 100.0f);
	//  WorldViewProjectionMatrix、略してWVPMatrixを作る
	Matrix4x4 viewProjectionMatrix_ = m4_.Multiply(viewMatrix_, projectionMatrix_);
	Matrix4x4 viewPortMatrix_ = RPV2_.MakeViewportMatrix(0, 0, float(KWindowWidth), float(KWindowHeight), 0.0f, 1.0f);
	Vector3 cameraTranslate_{0.0f, 1.9f, -6.49f};
	Vector3 cameraRotate_{0.26f, 0.0f, 0.0f};
	// pointを養分に射影したベクトル
	Vector3 project_;
	// この値が線分上の点を表す
	Vector3 closestPoint_;

	Vector3 start_;
	Vector3 end_;
};
