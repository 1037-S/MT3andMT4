#pragma once
#include "Object.h"
#include "Vector3Mas.h"
#include "POLYGON.h"
#include <algorithm>
#include <cmath>
#include <numbers>
#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

class GameMachMT4 {

public:
	Spherical ToSpherical(const Vector3 p);
	Vector3 ToCartesian(const Spherical s);

	void Initialize();
#ifdef _DEBUG
	void ImguiUpdate();
#endif // _DEBUG
	void Update();
	void Draw();

private:
	Vector3Mas vector3Mas_;
	POLYGON polygon_;

	const float limit = std::numbers::pi_v<float> / 2.0f;

	Spherical s_{
	    6.0f, 0.0f, limit
	    //-std::numbers::pi_v<float> / 2.0f
	};
	Vector3 pos;
	Vector3 target = {0.0f, 0.0f, 0.0f}; // 注視点(原点)
	Vector3 eye ;

	float t;
	Vector3 camera_;

	float r_;
	float sinTheta_;
	float phi_;

	// 注視点(原点)への向きからカメラ行列を作成して表示
	// 初期値:前(0,0,1)、右(1,0,0)、上(0,1,0)
	Vector3 worldUp ;
	Vector3 forward;
	Vector3 right;
	Vector3 up;

	Matrix4x4 cameraMatrix;

	int mousePosX;
	int mousePosY;

	Vector2 redPos;
	Vector2 greenPos;
	// 追従補間
	const float kDeltaTime = 1.0f / 60.0f; // 60fps固定の1フレーム時間
	float speed;                    // 追従速度（お好みの値に調整可能）
};
