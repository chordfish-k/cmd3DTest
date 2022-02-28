#ifndef _FACE_H_
#define _FACE_H_

#include <iostream>
#include <vector>
#include "vec.h"
#include "matrix.h"

class Face {
public:
	vector<Vec3> v;
	vector<pair<int, int>> ls;//记录顶点连接
public:
	Face(vector<Vec3> vs) {
		v = vs;
		for (int i = 0; i < vs.size() -1; i++) {
			ls.push_back(make_pair(i, i + 1));
		}
		ls.push_back(make_pair(vs.size() -1, 0));
	}
	

	Face& operator = (const Face&f) {
		for (int i = 0; i < v.size(); i++) {
			v[i] = f.v[i];
		}
		return *this;
	}

	Vec3 CenterPoint() const{
		Vec3 res;
		for (int i = 0; i < v.size(); i++) {
			res.x += v[i].x;
			res.y += v[i].y;
			res.z += v[i].z;
		}
		res.x = res.x / v.size();
		res.y = res.y / v.size();
		res.z = res.z / v.size();
		return res;
	}
	/*
		true为正面
		false为反面
	*/
	bool FrontOrBack() {
		Vec3 p = CenterPoint();
		Vec3 a = v[0] - p;
		Vec3 b = v[1] - p;
		Vec3 c = a.crossWith(b);
		return c.z > 0;
	}


	void rotate(Vec3 &angle) {
		double theataX = angle.x;
		double theataY = angle.y;
		double theataZ = angle.z;

		for (int i = 0; i < v.size(); i++) {
			double ts[3][9] = { { 1, 0, 0, 0, cos(theataX), sin(theataX), 0, -sin(theataX), cos(theataX)},
							{ cos(theataY), 0,  -sin(theataY), 0, 1, 0, sin(theataY), 0, cos(theataY)},
							{ cos(theataZ), sin(theataZ), 0, -sin(theataZ), cos(theataZ), 0, 0, 0, 1} };

			Matrix<double> r_mat(3, 3), mat(3, 3);
			mat = Matrix<double>::eye(3, 1);
			for (int j = 0; j < 3; j++) {
				r_mat = ts[j];
				mat *= r_mat;
			}

			double p[3] = { v[i].x, v[i].y, v[i].z};
			Matrix<double> v_mat(3, 1);
			v_mat = p;
			mat *= v_mat;
			v[i] = mat;
		}
	}

	void scale(double k) {
		
		for (int i = 0; i < v.size(); i++) {
			Matrix<double> mat = Matrix<double>::eye(3, k);
			double p[3] = { v[i].x, v[i].y, v[i].z };
			Matrix<double> v_mat(3, 1);
			v_mat = p;
			mat *= v_mat;
			v[i] = mat;
		}
	}

	bool operator < (const Face& b) {
		return CenterPoint().z > b.CenterPoint().z;
	}
};

#endif

