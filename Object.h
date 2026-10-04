#pragma once

struct Matrix4x4 {
	float m[4][4];
};

struct Vector2 {
	float x;
	float y;
};

struct Vector3 {
	float x;
	float y;
	float z;

	Vector3& operator+=(const Vector3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	Vector3 operator+ (const Vector3& v) 
	{
		Vector3 result;
		result.x = x + v.x;
		result.y = y + v.y;
		result.z = z + v.z;

		return result;
	}

	Vector3& operator-=(const Vector3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	Vector3& operator*=(float s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	Vector3& operator/=(float s) {
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}
};

struct Sphere // 球
{
	Vector3 center; //!< 球の中心点
	float radius;   //!< 球の半径
};

struct Line // 直線
{
	Vector3 origin; //!< 始点
	Vector3 diff;   //!< 終点の差分ベクトル
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

struct Plane // 平面
{
	Vector3 normal; //!< 法線(平面の向き) n
	float distance; //!< 距離
};

struct AABB { // 軸平行境界箱(Axis-Allgned Bounding-Box)
	Vector3 min; //!< 最小点
	Vector3 max; //!< 最大点
};

struct OBB {
	Vector3 center;				//!< 中心点
	Vector3 orientations[3];	//!< 座標軸。正規化・直交必須
	Vector3 size;               //!< 座標軸方向の長さの半分。　中心から面までの距離
};

struct Spherical {
	float radius;	// 動経 r
	float theta;	// 抑角 θ
	float phi;		// 方位角 φ
};


static const int kColumnWidth = 60;
static const int kRowHeight = 20;

const int KWindowWidth = 1280;
const int KWindowHeight = 720;
