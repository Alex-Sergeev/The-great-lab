#ifndef __QS_MATRIX_H
#define __QS_MATRIX_H

#include <vector>

template <typename T> class QSMatrix {
private:
	std::vector<std::vector<T> > mat;
	unsigned rows = 0;
	unsigned cols = 0;
	double det(int n, double _mat[10][10]) {
		if (n == 1) {
			return _mat[0][0];
		}
		double submat[10][10], d = 0;
		if (n == 2) {
			return((_mat[0][0] * _mat[1][1]) - (_mat[1][0] * _mat[0][1]));
		}
		else {
			for (int c = 0; c < n; c++) {
				for (int i = 1, subi = 0; i < n; i++, subi++)
					for (int j = 0, subj = 0; j < n; j++)
						if (j != c)	submat[subi][subj++] = _mat[i][j];
				d = d + (pow(-1, c) * _mat[0][c] * det(n - 1, submat));
			}
		}
		return d;
	}
	double subDet(int _i, int _j)
	{
		if (rows == 1) {
			return mat[0][0];
		}
		std::vector<std::vector<double>> tmp_mat;
		for (int i = 0; i < mat.size(); i++) {
			if (i != _i)
			{
				std::vector<double> tmp_vec;
				for (int j = 0; j < mat.size(); j++) {
					if (j != _j)
					{
						tmp_vec.push_back(mat[i][j]);
					}
				}
				tmp_mat.emplace_back(tmp_vec);
			}
		}
		double mat1[10][10];
		for (int i = 0; i < tmp_mat.size(); i++)
			for (int j = 0; j < tmp_mat[i].size(); j++)
				mat1[i][j] = tmp_mat[i][j];
		return det(tmp_mat.size(), mat1);
	}
public:
	QSMatrix() { }
	QSMatrix(unsigned _rows, unsigned _cols, const T& _initial);
	QSMatrix(const QSMatrix<T>& rhs);
	virtual ~QSMatrix();
	double Det() {
		if (rows == 1) {
			return mat[0][0];
		}
		double mat1[10][10];
		for (int i = 0; i < mat.size(); i++)
			for (int j = 0; j < mat[i].size(); j++)
				mat1[i][j] = mat[i][j];
		return det(mat.size(), mat1);
	}

	QSMatrix<T> getReversed() {
		QSMatrix<T> ret(rows, cols, 0.0);
		if (rows == 1) {
			ret(0, 0) = mat[0][0];
			return ret;
		}
		double deter = this->Det();
		for (int i = 0; i<rows; i++) {
			for (int j = 0; j<cols; j++) {
				ret(i, j) = subDet(i, j) / deter;
			}
		}
		return ret;
	}
	// Operator overloading, for "standard" mathematical matrix operations                                                                                                                                                          
	QSMatrix<T>& operator=(const QSMatrix<T>& rhs);

	// Matrix mathematical operations                                                                                                                                                                                               
	QSMatrix<T> operator+(const QSMatrix<T>& rhs);
	QSMatrix<T>& operator+=(const QSMatrix<T>& rhs);
	QSMatrix<T> operator-(const QSMatrix<T>& rhs);
	QSMatrix<T>& operator-=(const QSMatrix<T>& rhs);
	QSMatrix<T> operator*(const QSMatrix<T>& rhs);
	QSMatrix<T>& operator*=(const QSMatrix<T>& rhs);
	QSMatrix<T> transpose();

	// Matrix/scalar operations                                                                                                                                                                                                     
	QSMatrix<T> operator+(const T& rhs);
	QSMatrix<T> operator-(const T& rhs);
	QSMatrix<T> operator*(const T& rhs);
	QSMatrix<T> operator/(const T& rhs);

	// Matrix/vector operations                                                                                                                                                                                                     
	std::vector<T> operator*(const std::vector<T>& rhs);
	std::vector<T> diag_vec();

	// Access the individual elements                                                                                                                                                                                               
	T& operator()(const unsigned& row, const unsigned& col);
	const T& operator()(const unsigned& row, const unsigned& col) const;

	// Access the row and column sizes                                                                                                                                                                                              
	unsigned get_rows() const;
	unsigned get_cols() const;

};

#include "matrix.cpp"

#endif