#pragma once

struct PosVec {
	float x;
	float y;
	float z;

	PosVec() :x(0), y(0), z(0) {}
	PosVec(float _x, float _y) :x(_x), y(_y), z(0) {}
	PosVec(float _x, float _y, float _z) :x(_x), y(_y), z(_z) {}
};