#pragma once
#include "Object.h"
#include "Matrix4.h"
#include "RringPlineVer2.h"
#include "Rotate.h"
//#include "POLYGON.h"
#include "GRID.h"
#include "MakeMatrix.h"
#include <cmath>
#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG
#include "Bezier3.h"

class GameScene {
public:
	
	~GameScene();

	void Initialize();
	void Update(char* keys);
	void Draw();

private:

	Matrix4 m4_;
	MakeMatrix MM_;
	WorldM4 wm4_;
	GRID grid_;

	//POLYGON polygon_;
	Rotate rtt_;
	RringPlineVer2 RPV2_;

	Bezier3 bezier_; 
	
	// カメラ用
	const Vector3 CameraPos_ = {0.0f, 0.0f, -10.0f};
	Vector3 rotate{};
	Vector3 translate{};
	Matrix4x4 cameraMatrix_;
	Matrix4x4 worldMatrix_;
	Matrix4x4 viewMatrix_;
	Matrix4x4 projectionMatrix_;
	//  WorldViewProjectionMatrix、略してWVPMatrixを作る
	Matrix4x4 viewProjectionMatrix_;
	Matrix4x4 viewPortMatrix_;
	Vector3 cameraTranslate_{0.0f, 1.9f, -6.49f};
	Vector3 cameraRotate_{0.26f, 0.0f, 0.0f};
	// ここまで

};

