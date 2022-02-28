#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include "Vec.h"
#include "Face.h"

class Figure {
public:
	string name;
	vector<Vec3> vs;
	vector<vector<int>> fs;
public:
	Figure() {

	}
	Figure& operator=(const Figure& obj) {
		if (this == &obj) {
			return *this;
		}
		vs = obj.vs;
		fs = obj.fs;
		return *this;
	}
	void addVector(Vec3 v) {
		//cout << "add: " << v << endl;
		vs.push_back(v);

	}
	void addFace(vector<int> v) {
		fs.push_back(v);
	}

	void rotate(Vec3& angle) {
		double theataX = angle.x;
		double theataY = angle.y;
		double theataZ = angle.z;

		for (int i = 0; i < vs.size(); i++) {
			double ts[3][9] = { { 1, 0, 0, 0, cos(theataX), sin(theataX), 0, -sin(theataX), cos(theataX)},
							{ cos(theataY), 0,  -sin(theataY), 0, 1, 0, sin(theataY), 0, cos(theataY)},
							{ cos(theataZ), sin(theataZ), 0, -sin(theataZ), cos(theataZ), 0, 0, 0, 1} };

			Matrix<double> r_mat(3, 3), mat(3, 3);
			mat = Matrix<double>::eye(3, 1);
			for (int j = 0; j < 3; j++) {
				r_mat = ts[j];
				mat *= r_mat;
			}

			double p[3] = { vs[i].x, vs[i].y, vs[i].z };
			Matrix<double> v_mat(3, 1);
			v_mat = p;
			mat *= v_mat;
			vs[i] = mat;
		}
	}
	void scale(double k) {
		for (int i = 0; i < vs.size(); i++) {
			Matrix<double> mat = Matrix<double>::eye(3, k);
			double p[3] = { vs[i].x, vs[i].y, vs[i].z };
			Matrix<double> v_mat(3, 1);
			v_mat = p;
			mat *= v_mat;
			vs[i] = mat;
			//cout << vs[i] << endl;
		}
	}
	void move(Vec3 &v){
		for (int i = 1; i < vs.size(); i++) {
			vs[i] = vs[i] + v;
			//cout << vs[i] << endl;
		}
	}
	
	
};

Figure ReadObj(const string& name) {
		//创建流对象
		ifstream ifs;
	
		//打开文件并且判断是否打开成功
		ifs.open(name, ios::in);
		if (!ifs.is_open()) {
			cout << "文件[" << name << "]打开失败" << endl;
		}
		Figure obj;
		string line, head, mata;
		obj.addVector(Vec3(0, 0, 0));//占位用
		while (getline(ifs, line)) {
			stringstream sst;
			sst << line;
			
			while (sst >> head) {
				if (head == "v") {
					double x, y, z;
					sst >> x >> y >> z;
					Vec3 v(x, y, z);
					obj.addVector(v);
					//cout << "add: " << v << endl;
				}
				else if (head == "f") {
					//cout << "f" << endl;
					vector<int> ids;
					while (sst >> mata) {
						stringstream ssm;
						ssm << mata;
						int id;
						ssm >> id;
						//cout << id << " ";
						ids.push_back(id);
					}
					//cout << endl;
					obj.addFace(ids);
	
				}
			}
		}
		//cout << "v:" << obj.vs.size() << ", f:" << obj.fs.size() << endl;
		return obj;
	}

#endif // !_OBJECT_H_

