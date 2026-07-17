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



static const int kColumnWidth = 60;
static const int kRowHeight = 20;

const int KWindowWidth = 1280;
const int KWindowHeight = 720;
