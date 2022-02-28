#ifndef _VEC_H_
#define _VEC_H_


#include <iostream>
#include <ostream>

#include "Matrix.h"

using namespace std;


class Vec2 {
public:
	double x, y;
	static Vec2 ZERO;

public:
	Vec2(double x=0, double y=0) : x(x), y(y) {};


	Vec2 operator + (const Vec2& b) {
		return Vec2(x + b.x, y + b.y);
	}
	

	Vec2 operator-() {
		return Vec2(-x, -y);
	}

	friend Vec2 operator - (const Vec2& a, const Vec2& b) {
		return Vec2(a.x - b.x, a.y - b.y);
	}

	friend ostream& operator<<(ostream& out, const Vec2& a) {
		out << "<Vec2> (" << a.x << "," << a.y << ")";
		return out;
	}

	Matrix<double> toMatrix() {
		Matrix<double> m(1, 2);
		double t[] = { x, y};
		m = t;
		return m;
	}
};

class Vec3{
public:
	double x, y, z;
	static Vec3 ZERO;

public:
	Vec3(Vec2 v) : x(v.x), y(v.y), z(0) {};
	Vec3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {};

	Vec3 operator + (const Vec3& b) {
		return Vec3(x + b.x, y + b.y, z + b.z);
	}

	Vec3 operator * (double b) {
		return Vec3(x * b, y * b, z * b);;
	}

	Vec3 crossWith(Vec3& b) {
		Vec3 res = Vec3(1, 0, 0) * (y * b.z - z * b.y) - Vec3(0, 1, 0) * (x * b.z - z * b.x) + Vec3(0, 0, 1) * (x * b.y - y*b.x);
		return res;
	}

	double pointWith(Vec3& b) {
		return x * b.x + y * b.y + z * b.z;
	}

	Vec3 operator-() {
		return Vec3(-x, -y, -z);
	}

	Vec3& operator=(const Vec3& v) {
		x = v.x, y = v.y, z = v.z;
		return *this;
	}

	Vec3& operator=(const Matrix<double>& m) {
		if (m.row() < 3) return *this;
		x = m.at(0, 0), y = m.at(1, 0), z = m.at(2, 0);
		return *this;
	}

	friend Vec3 operator - (const Vec3& a, const Vec3& b) {
		return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	friend ostream& operator<<(ostream& out, const Vec3& a) {
		out << "<Vec3> (" << a.x << "," << a.y << "," << a.z << ")";
		return out;
	}

	double norm() {
		return sqrt(pointWith(*this));
	}

	Vec3 normalize() {
		double n = norm();
		Vec3 res(x / n, y / n, z / n);
		//cout << res;
		return res;
	}

	Vec2 ToVec2() {
		return Vec2(x, y);
	}

	Matrix<double> toMatrix() {
		Matrix<double> m(1, 3);
		double t[] = { x, y, z };
		m = t;
		return m;
	}
};

class Vec4 {
public:
	double x, y, z, w;
	static Vec4 ZERO;

public:
	Vec4(Vec2 v) : x(v.x), y(v.y), z(0), w(0) {};
	Vec4(Vec3 v) : x(v.x), y(v.y), z(v.z), w(0) {};
	Vec4(double x = 0, double y = 0, double z = 0, double w = 0) : x(x), y(y), z(z), w(w) {};

	Vec4 operator + (const Vec4& b) {
		return Vec4(x + b.x, y + b.y, z + b.z, w + b.z);
	}

	Vec4 operator-() {
		return Vec4(-x, -y, -z, -w);
	}

	Vec4 operator - (const Vec4& b) {
		return Vec4(x - b.x, y - b.y, z - b.z, w - b.w);
	}

	friend ostream& operator<<(ostream& out, const Vec4& a) {
		out << "<Vec4> (" << a.x << "," << a.y << "," << a.z << "," << a.w << ")";
		return out;
	}

	Vec4 operator * (double b) {
		return Vec4(x * b, y * b, z * b, w * b);
	}

	Vec2 toVec2() {
		return Vec2(x, y);
	}

	Vec3 toVec3() {
		return Vec3(x, y, z);
	}

	Matrix<double> toMatrix() {
		Matrix<double> m(1, 4);
		double t[] = { x, y, z, w };
		m = t;
		return m;
	}
};

Vec2 Vec2::ZERO = Vec2(0, 0);
Vec3 Vec3::ZERO = Vec3(0, 0, 0);
Vec4 Vec4::ZERO = Vec4(0, 0, 0, 0);




#endif
