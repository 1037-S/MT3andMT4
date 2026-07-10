#include "GameScene.h"
#include <Novice.h>

GameScene::~GameScene() {}

void GameScene::Initialize() {
	grid_.Initialize();
	boxToSegment_.Initialize();
}

void GameScene::Update(char* keys) {

	grid_.Update();
	boxToSegment_.Update();

#ifdef _DEBUG
	ImGui::Begin("Window");
	ImGui::DragFloat3("CameraTranslate", &cameraTranslate_.x, 0.01f);
	ImGui::DragFloat3("CameraRotate", &cameraRotate_.x, 0.01f);
	boxToSegment_.ImguiUpdate();
	ImGui::End();

	float cameraSpeed = 0.05f;
	if (keys[DIK_E]) {
		cameraTranslate_.z += cameraSpeed;
	}
	if (keys[DIK_Q]) {
		cameraTranslate_.z -= cameraSpeed;
	}
	if (keys[DIK_A]) {
		cameraTranslate_.x += cameraSpeed;
	}
	if (keys[DIK_D]) {
		cameraTranslate_.x -= cameraSpeed;
	}
	if (keys[DIK_W]) {
		cameraTranslate_.y -= cameraSpeed;
	}
	if (keys[DIK_S]) {
		cameraTranslate_.y += cameraSpeed;
	}
	if (keys[DIK_UP]) {
		cameraRotate_.x += cameraSpeed / 5;
	}
	if (keys[DIK_DOWN]) {
		cameraRotate_.x -= cameraSpeed / 5;
	}
	if (keys[DIK_LEFT]) {
		cameraRotate_.y += cameraSpeed / 5;
	}
	if (keys[DIK_RIGHT]) {
		cameraRotate_.y -= cameraSpeed / 5;
	}

#endif // _DEBUG

	// 各種行列の計算
	RPV2_.WorldViewPortMatrix(cameraMatrix_, worldMatrix_, viewMatrix_, projectionMatrix_);
	cameraMatrix_ = wm4_.MakeAffineMatrix({1.0f, 1.0f, 1.0f}, cameraRotate_, cameraTranslate_);
	worldMatrix_ = wm4_.MakeAffineMatrix({1.0f, 1.0f, 1.0f}, rotate, translate);
	viewMatrix_ = m4_.Inverse(cameraMatrix_);
	projectionMatrix_ = RPV2_.MakePerspectiveFovMatrix(0.45f, float(KWindowWidth) / float(KWindowHeight), 0.1f, 100.0f);
	//  ViewProjectionMatrixを作る
	viewProjectionMatrix_ = m4_.Multiply(viewMatrix_, projectionMatrix_);
	viewPortMatrix_ = RPV2_.MakeViewportMatrix(0, 0, float(KWindowWidth), float(KWindowHeight), 0.0f, 1.0f);
}

void GameScene::Draw() {
	grid_.Draw(viewProjectionMatrix_, viewPortMatrix_);
	boxToSegment_.Draw(viewProjectionMatrix_, viewPortMatrix_);
}
