#pragma once
#include "Object.h"



class Matrix4 {
public:
	
	~Matrix4();

	// 1.行列の加法
	static Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
	// 2.行列の減法
	static Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
	// 3.行列の積
	static Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
	// 4.逆行列
	static Matrix4x4 Inverse(const Matrix4x4& m);
	// 5.転置行列
	static Matrix4x4 Transpose(const Matrix4x4& m);
	// 6.単位行列の作成
	static Matrix4x4 MakeIdentity4x4();

	void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);
	
	
	void Initialize();

	void Update();

	void Draw();

private:

	Matrix4x4 m1_;
	Matrix4x4 m2_;

	Matrix4x4 resultAdd_;
	Matrix4x4 resultSubtract_;
	Matrix4x4 resultMultiply_;
	Matrix4x4 inverseM1_;
	Matrix4x4 inverseM2_;
	Matrix4x4 transposeM1_;
	Matrix4x4 transposeM2_;
	Matrix4x4 identity_;
};

