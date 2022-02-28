#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;

template<typename T> class Matrix {
public:
	int rows_num, cols_num;
	vector<vector<T>> p;
	

public:
	Matrix<T>(const Matrix<T>&);
	Matrix<T>(vector<T>);
	Matrix<T>(int, int);
	Matrix<T>(int, int, T);//预配分空间
	~Matrix();
	Matrix<T>& operator=(const Matrix<T>&);//矩阵的复制
	Matrix<T>& operator=(T*);//将数组的值传给矩阵
	Matrix<T>& operator+=(const Matrix<T>&);//矩阵的+=操作
	Matrix<T>& operator-=(const Matrix<T>&);//-=
	Matrix<T> operator+(const Matrix<T>&);//+
	Matrix<T> operator-(const Matrix<T>&);//-
	Matrix<T>& operator*=(const Matrix<T>&);//*=
	Matrix<T> operator*(const Matrix<T>& m)const;
	void initialize();//初始化矩阵
	void print() const;//矩阵显示
	double det();//求矩阵的行列式
	T at(int i, int j) const;
	void set(int i, int j, T value);
	static Matrix<T> eye(int, T);//制造一个对角型矩阵
	int row() const;
	int col() const;
	static Matrix<T> t(const Matrix<T>& m);//矩阵转置的实现,且不改变矩阵
};


using std::endl;
using std::cout;
using std::istream;
const double EPS = 1e-10;

template<typename T>
inline void Matrix<T>::initialize() {//初始化矩阵大小
	p.clear();
	for (int i = 0; i < rows_num; ++i) {
		p.push_back(vector<T>());
		for (int j = 0; j < cols_num; ++j) {
			p[i].push_back(0);
		}
	}
}
//声明一个全0矩阵
template<typename T>
inline Matrix<T>::Matrix(int rows, int cols)
{
	rows_num = rows;
	cols_num = cols;
	initialize();
}
//声明一个值全部为value的矩阵
template<typename T>
inline Matrix<T>::Matrix(int rows, int cols, T value)
{
	rows_num = rows;
	cols_num = cols;
	initialize();
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			p[i][j] = value;
		}
	}
	
}

template<typename T>
inline Matrix<T>::Matrix(vector<T> array)
{
	int n = array.size();
	rows_num = 1;
	cols_num = n;
	initialize();
	
	for(int i=0; i<n; i++){
		p[0] = array;
	}
}

//析构函数
template<typename T>
inline Matrix<T>::~Matrix() {
	p.clear();
	
}

//复制构造
template<typename T>
inline Matrix<T>::Matrix(const Matrix<T>& m) {
	p.clear();
	rows_num = m.row();
	cols_num = m.col();
	initialize();
	for (int i = 0; i < rows_num; i++){
		for (int j = 0; j < cols_num; j++){
			p[i][j] = m.p[i][j];
		}
	}

}


//实现矩阵的复制
template<typename T>
inline Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m)
{
	if (this == &m) {
		return *this;
	}

	if (rows_num != m.rows_num || cols_num != m.cols_num) {

		p.clear();

		rows_num = m.rows_num;
		cols_num = m.cols_num;
		initialize();
	}

	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			p[i][j] = m.p[i][j];
		}
	}
	return *this;
}
//将数组的值传递给矩阵(要求矩阵的大小已经被声明过了)
template<typename T>
inline Matrix<T>& Matrix<T>::operator=(T* a) {
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			p[i][j] = *(a + i * cols_num + j);
		}
	}
	return *this;
}
//+=操作
template<typename T>
inline Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& m)
{
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			p[i][j] += m.p[i][j];
		}
	}
	return *this;
}
//实现-
template<typename T>
inline Matrix<T> Matrix<T>::operator-(const Matrix<T>& m)
{
	Matrix res(rows_num, cols_num);
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			res.p[i][j] = p[i][j] - m.p[i][j];
		}
	}
	return res;
}

template<typename T>
inline Matrix<T> Matrix<T>::operator+(const Matrix<T>& m)
{
	Matrix<T> res(rows_num, cols_num);
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			res.p[i][j] = p[i][j] + m.p[i][j];
		}
	}
	return res;
}
//实现-=
template<typename T>
inline Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& m)
{
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			p[i][j] -= m.p[i][j];
		}
	}
	return *this;
}
//实现*=
template<typename T>
inline Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& m)
{
	Matrix temp(rows_num, m.cols_num);//若C=AB,则矩阵C的行数等于矩阵A的行数，C的列数等于B的列数。
	for (int i = 0; i < temp.rows_num; i++) {
		for (int j = 0; j < temp.cols_num; j++) {
			for (int k = 0; k < cols_num; k++) {
				temp.p[i][j] += (p[i][k] * m.p[k][j]);
			}
		}
	}
	*this = temp;
	return *this;
}
//实现矩阵的乘法
template<typename T>
inline Matrix<T> Matrix<T>::operator*(const Matrix<T>& m)const {
	Matrix ba_M(rows_num, m.cols_num, 0.0);
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < m.cols_num; j++) {
			for (int k = 0; k < cols_num; k++) {
				ba_M.p[i][j] += (p[i][k] * m.p[k][j]);
			}
		}
	}
	return ba_M;
}



//矩阵显示
template<typename T>
inline void Matrix<T>::print() const {
	cout << rows_num <<" "<<cols_num<< endl;//显示矩阵的行数和列数
	for (int i = 0; i < rows_num; i++) {
		cout << "\t";
		for (int j = 0; j < cols_num; j++) {
			cout << p[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//计算矩阵行列式的值
template<typename T>
inline double Matrix<T>::det() {
	//为计算行列式做一个备份
	double** back_up;
	back_up = new double* [rows_num];
	for (int i = 0; i < rows_num; i++) {
		back_up[i] = new double[cols_num];
	}
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			back_up[i][j] = p[i][j];
		}
	}
	if (rows_num != cols_num) {
		std::abort();//只有方阵才能计算行列式，否则调用中断强制停止程序
	}
	double ans = 1;
	for (int i = 0; i < rows_num; i++) {
		//通过行变化的形式，使得矩阵对角线上的主元素不为0
		if (abs(p[i][i]) <= EPS) {
			bool flag = false;
			for (int j = 0; (j < cols_num) && (!flag); j++) {
				//若矩阵的一个对角线上的元素接近于0且能够通过行变换使得矩阵对角线上的元素不为0
				if ((abs(p[i][j]) > EPS) && (abs(p[j][i]) > EPS)) {
					flag = true;
					//注：进行互换后,p[i][j]变为p[j][j]，p[j][i]变为p[i][i]
					//对矩阵进行行变换
					double temp;
					for (int k = 0; k < cols_num; k++) {
						temp = p[i][k];
						p[i][k] = p[j][k];
						p[j][k] = temp;
					}
				}
			}
			if (flag)
				return 0;
		}
	}
	for (int i = 0; i < rows_num; i++) {
		for (int j = i + 1; j < rows_num; j++) {
			for (int k = i + 1; k < cols_num; k++) {
				p[j][k] -= p[i][k] * (p[j][i] * p[i][i]);
			}
		}
	}
	for (int i = 0; i < rows_num; i++) {
		ans *= p[i][i];
	}
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			p[i][j] = back_up[i][j];
		}
	}
	return ans;
}
//返回矩阵第i行第j列的数
template<typename T>
inline T Matrix<T>::at(int i, int j) const {
	return this->p[i][j];
}

template<typename T>
inline void Matrix<T>::set(int i, int j, T value){
	this->p[i][j] = value;
}

//制造一个单位矩阵
template<typename T>
inline Matrix<T> Matrix<T>::eye(int n, T k) {
	Matrix<T> A(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				A.p[i][j] = k;
			}
			else {
				A.p[i][j] = 0;
			}
		}
	}
	return A;
}
//读取矩阵行列数
template<typename T>
inline int Matrix<T>::row() const {
	return rows_num;
}
template<typename T>
inline int Matrix<T>::col() const {
	return cols_num;
}
//实现矩阵的转置
template<typename T>
inline Matrix<T> Matrix<T>::t(const Matrix<T>& m)
{
	int col_size = m.col();
	int row_size = m.row();
	Matrix<T> mt(col_size, row_size);
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			mt.p[j][i] = m.p[i][j];
		}
	}
	return mt;
}

//vec

typedef Matrix<double> RowVec;
typedef Matrix<double> ColVec;

RowVec makePoint(double x, double y){
	vector<double> ls;
	ls.push_back(x);
	ls.push_back(y);
	
	return RowVec(ls);
}

#endif
