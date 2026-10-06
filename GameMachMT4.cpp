#include "GameMachMT4.h"
#include <Novice.h>


Spherical GameMachMT4::ToSpherical(const Vector3 p) {
	r_ = std::sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
	if (r_ == 0){
		return {0.0f, 0.0f, 0.0f};
	}
	sinTheta_ = std::clamp(p.y / r_, -1.0f, 1.0f);
	phi_ = 0.0f;
	if (p.x != 0.0f || p.z != 0.0f) {
		phi_ = std::atan2(p.z, p.x);
	}
	
	return {r_, std::asin(sinTheta_), phi_};
}

// 球面座標系
Vector3 GameMachMT4::ToCartesian(const Spherical s) {
	float rho = s.radius * std::cos(s.theta);

	return {
	    rho * std::cos(s.phi),
	    s.radius * std::sin(s.theta),
		rho * std::sin(s.phi)
	};
}

void GameMachMT4::Initialize() { 
	
	greenPos = {KWindowWidth/2, KWindowHeight/2};
	speed = 5.0f;
	//s_.radius = std::max(s_.radius,0.1f); 
	//s_.theta = std::clamp(s_.theta, -limit, limit);
}
#ifdef _DEBUG
void GameMachMT4::ImguiUpdate() {
	//ImGui::Text("Target Position: (%.3f, %.3f, %.3f)/ +Y up / Camera +z forward", target.x, target.y, target.z);
	ImGui::Text("TargetMouse Position (Red Circle)");
	ImGui::Separator();
	// 球面座標系の各パラメータを直接変更（+-調整可能）
	//bool changed = false;
	//// 半径 (radius): 0.1 以上に制限
	//if (ImGui::InputFloat("Radius ", &s_.radius, 0.01f, 1.0f, "%.3f")) {
	//	changed = true;
	//}
	//// 仰角 (theta): -limit から limit に制限 (上下の回転)
	//if (ImGui::InputFloat("Theta", &s_.theta, 0.01f, 1.0f, "%.3f")) {
	//	changed = true;
	//}
	//// 方位角 (phi): -PI から PI (左右の回転)
	//if (ImGui::InputFloat("Phi", &s_.phi, 0.01f, 1.0f ,"%.3f")) {
	//	changed = true;
	//}
	ImGui::Text("[Linear Interpolation - student Mode]");
	ImGui::DragFloat("Speed", &speed, 0.1f, 0.1f, 40.0f, "%.1f");
	//ImGui::DragFloat("DeltaTime", &kDeltaTime, 0.1f, 0.1f, 1.0f, "%.1f");
	ImGui::Text("Mouse Position : (%.1f, %.1f)", redPos.x, redPos.y);
	ImGui::Text("Circle Position : (%.1f, %.1f)", greenPos.x, greenPos.y);
	ImGui::Text("Distance : %.1f", vector3Mas_.Length({redPos.x - greenPos.x, redPos.y - greenPos.y, 0.0f}));
	ImGui::Separator();
	// 読み取り専用として forward, right, up のベクトルを表示
	//ImGui::Text("Spherical : r = (%.3f), theta = (%.3f)rad, phi = (%.3f)rad", s_.radius, s_.theta, s_.phi);
	//ImGui::Text("Cartesian:   (%.3f, %.3f, %.3f)", pos.x, pos.y, pos.z);
	ImGui::Text("[Teacher Comparison Option]");
	//if (ImGui::Button("Show Exponential Decay(Compare)")) {
	//}
	ImGui::Separator();
	//ImGui::Text("Camera Matrix");
	//ImGui::Text("Right:   %.3f, %.3f, %.3f, %.3f", right.x, right.y, right.z, 0.0f);
	//ImGui::Text("Up:      %.3f, %.3f, %.3f, %.3f", up.x, up.y, up.z, 0.0f);
	//ImGui::Text("Forward: %.3f, %.3f, %.3f, %.3f", forward.x, forward.y, forward.z, 0.0f);
	//ImGui::Text("Eye:     %.3f, %.3f, %.3f, %.3f", eye.x, eye.y, eye.z, 1.0f);

}
#endif // _DEBUG

void GameMachMT4::Update() {
	pos = ToCartesian(s_);
	eye = pos + target;

	worldUp = {0.0f, 1.0f, 0.0f};
	forward = vector3Mas_.Subtract(target, eye);
	right = vector3Mas_.Normalize(polygon_.Cross(worldUp, forward));
	up = polygon_.Cross(forward, right);

	 cameraMatrix = {
	    {{right.x, right.y, right.z, 0.0f}, 
		{up.x, up.y, up.z, 0.0f}, 
		{forward.x, forward.y, forward.z, 0.0f}, 
		{eye.x, eye.y, eye.z, 1.0f}}
    };
	Novice::GetMousePosition(&mousePosX, &mousePosY);
	 redPos.x = static_cast<float>(mousePosX);
	 redPos.y = static_cast<float>(mousePosY);

	 // pos += (speed * deltaTime) * (target - pos);
	greenPos.x += (speed * kDeltaTime) * (redPos.x - greenPos.x);
	greenPos.y += (speed * kDeltaTime) * (redPos.y - greenPos.y);
	 
}

void GameMachMT4::Draw() {
	Novice::DrawLine(static_cast<int>(greenPos.x), static_cast<int>(greenPos.y), static_cast<int>(redPos.x), static_cast<int>(redPos.y), WHITE);
	Novice::DrawEllipse(static_cast<int>(greenPos.x), static_cast<int>(greenPos.y), 20, 20, 0.0f, GREEN, kFillModeSolid);
	Novice::DrawEllipse(static_cast<int>(redPos.x), static_cast<int>(redPos.y), 12, 12, 0.0f, RED, kFillModeSolid); }
