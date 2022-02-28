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
	Matrix<T>(int, int, T);//Ԥ��ֿռ�
	~Matrix();
	Matrix<T>& operator=(const Matrix<T>&);//����ĸ���
	Matrix<T>& operator=(T*);//�������ֵ��������
	Matrix<T>& operator+=(const Matrix<T>&);//�����+=����
	Matrix<T>& operator-=(const Matrix<T>&);//-=
	Matrix<T> operator+(const Matrix<T>&);//+
	Matrix<T> operator-(const Matrix<T>&);//-
	Matrix<T>& operator*=(const Matrix<T>&);//*=
	Matrix<T> operator*(const Matrix<T>& m)const;
	void initialize();//��ʼ������
	void print() const;//������ʾ
	double det();//����������ʽ
	T at(int i, int j) const;
	void set(int i, int j, T value);
	static Matrix<T> eye(int, T);//����һ���Խ��;���
	int row() const;
	int col() const;
	static Matrix<T> t(const Matrix<T>& m);//����ת�õ�ʵ��,�Ҳ��ı����
};


using std::endl;
using std::cout;
using std::istream;
const double EPS = 1e-10;

template<typename T>
inline void Matrix<T>::initialize() {//��ʼ�������С
	p.clear();
	for (int i = 0; i < rows_num; ++i) {
		p.push_back(vector<T>());
		for (int j = 0; j < cols_num; ++j) {
			p[i].push_back(0);
		}
	}
}
//����һ��ȫ0����
template<typename T>
inline Matrix<T>::Matrix(int rows, int cols)
{
	rows_num = rows;
	cols_num = cols;
	initialize();
}
//����һ��ֵȫ��Ϊvalue�ľ���
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

//��������
template<typename T>
inline Matrix<T>::~Matrix() {
	p.clear();
	
}

//���ƹ���
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


//ʵ�־���ĸ���
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
//�������ֵ���ݸ�����(Ҫ�����Ĵ�С�Ѿ�����������)
template<typename T>
inline Matrix<T>& Matrix<T>::operator=(T* a) {
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			p[i][j] = *(a + i * cols_num + j);
		}
	}
	return *this;
}
//+=����
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
//ʵ��-
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
//ʵ��-=
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
//ʵ��*=
template<typename T>
inline Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& m)
{
	Matrix temp(rows_num, m.cols_num);//��C=AB,�����C���������ھ���A��������C����������B��������
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
//ʵ�־���ĳ˷�
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



//������ʾ
template<typename T>
inline void Matrix<T>::print() const {
	cout << rows_num <<" "<<cols_num<< endl;//��ʾ���������������
	for (int i = 0; i < rows_num; i++) {
		cout << "\t";
		for (int j = 0; j < cols_num; j++) {
			cout << p[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//�����������ʽ��ֵ
template<typename T>
inline double Matrix<T>::det() {
	//Ϊ��������ʽ��һ������
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
		std::abort();//ֻ�з�����ܼ�������ʽ����������ж�ǿ��ֹͣ����
	}
	double ans = 1;
	for (int i = 0; i < rows_num; i++) {
		//ͨ���б仯����ʽ��ʹ�þ���Խ����ϵ���Ԫ�ز�Ϊ0
		if (abs(p[i][i]) <= EPS) {
			bool flag = false;
			for (int j = 0; (j < cols_num) && (!flag); j++) {
				//�������һ���Խ����ϵ�Ԫ�ؽӽ���0���ܹ�ͨ���б任ʹ�þ���Խ����ϵ�Ԫ�ز�Ϊ0
				if ((abs(p[i][j]) > EPS) && (abs(p[j][i]) > EPS)) {
					flag = true;
					//ע�����л�����,p[i][j]��Ϊp[j][j]��p[j][i]��Ϊp[i][i]
					//�Ծ�������б任
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
//���ؾ����i�е�j�е���
template<typename T>
inline T Matrix<T>::at(int i, int j) const {
	return this->p[i][j];
}

template<typename T>
inline void Matrix<T>::set(int i, int j, T value){
	this->p[i][j] = value;
}

//����һ����λ����
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
//��ȡ����������
template<typename T>
inline int Matrix<T>::row() const {
	return rows_num;
}
template<typename T>
inline int Matrix<T>::col() const {
	return cols_num;
}
//ʵ�־����ת��
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
