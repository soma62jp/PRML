#ifndef _LASSO_H_
#define _LASSO_H_

#include "Matrix.h"
#include "numpy.h"

using namespace arith;
using namespace std;

// ------------------------------------------//
// Lasso回帰                    			//
// ------------------------------------------//
class Lasso {

private:
public:

	double alpha_; // 正則化項の係数
	int max_iter_; // 繰り返しの回数
	bool fit_intercept_; // 切片(i.e., ¥beta_0)を用いるか
	Matrix* coef_; // 回帰係数(i.e., ¥beta)保存用変数
	double intercept_; // 切片保存用変数

	//
	explicit Lasso(double alpha, int max_iter, bool fit_intercept);

	//
	virtual ~Lasso();

	double soft_thresholding_operator(double x, double lambda);

	void fit(Matrix& X, Matrix& y);

	Matrix predict(const Matrix& X);

};

//
Lasso::Lasso(double alpha, int max_iter, bool fit_intercept)
	: alpha_(1.0), max_iter_(1000), fit_intercept_(true) {
	alpha_ = alpha;
	max_iter_ = max_iter;
	fit_intercept_ = fit_intercept;
	coef_ = NULL;
	intercept_ = 0;
}

Lasso::~Lasso() {
	if(coef_!=NULL){
		delete coef_;
	}
}

double Lasso::soft_thresholding_operator(double x, double lambda) {

	if ((x > 0) && (lambda < abs(x))) {
		return x - lambda;
	}
	else if ((x < 0) && (lambda < abs(x))) {
		return x + lambda;
	}
	else {
		return 0;
	}

}

void Lasso::fit(Matrix& X, Matrix& y) {

	double sum;
	double arg1;
	double arg2;
	int start;

	// fit_intercept_=true
	Matrix calcX(X.m_row, X.m_col + 1);
	Matrix beta(1, calcX.m_col);
	Matrix tmp_beta(1, calcX.m_col);
	Matrix r_j(y.m_row, y.m_col);
	coef_ = new Matrix(1, calcX.m_col - 1); // coefのサイズを作る

	for (unsigned int i = 0; i < X.m_row; i++) {
		for (unsigned int j = 0; j < X.m_col; j++) {
			calcX.val[i][j + 1] = X.val[i][j];
		}
	}


	for (unsigned int i = 0; i < calcX.m_row; i++) {
		calcX(i, 0) = 1;
	}


	if (fit_intercept_) {
		sum = 0;
		for (unsigned int i = 0; i < y.m_col; i++) {
			sum += y(0, i);
		}
		sum /= X.m_row;
		beta(0, 0) = sum;
	}else{
    	beta(0, 0) = 0;
	}

	for (int i = 0; i < max_iter_; i++) {

		if (fit_intercept_) {
			start = 1;
		}
		else {
			start = 0;
		}

		for (unsigned int j = start; j < beta.m_col; j++) {

			arg1 = 0;
			arg2 = 0;
			sum = 0;

			tmp_beta = beta;
			tmp_beta(0, j) = 0;
			Matrix wk1(1, calcX.m_row);

			for (unsigned int k = 0; k < calcX.m_row; k++) {
				sum = 0;
				for (unsigned int l = 0; l < calcX.m_col; l++) {
					sum += calcX(k, l) * tmp_beta(0, l);
				}
				wk1(0, k) = sum;
			}

			r_j = y - wk1;

			for (unsigned int k = 0; k < calcX.m_row; k++) {
				arg1 += calcX(k, j) * r_j(0, k);
			}
			arg2 = (double)calcX.m_row * alpha_;

			sum = 0;
			for (unsigned int k = 0; k < X.m_row; k++) {
				sum += calcX(k, j) * calcX(k, j);
			}

			beta(0, j) = soft_thresholding_operator(arg1, arg2) / sum;

			if (fit_intercept_) {
				Matrix wk2(y.m_row, y.m_col);
				for (unsigned int k = 0; k < X.m_row; k++) {
					sum = 0;
					for (unsigned int l = 0; l < X.m_col; l++) {
						sum += X(k, l) * beta(0, l + 1);
					}
					wk2(0, k) = sum;

				}

				sum = 0;
				Matrix wk3(y.m_row, y.m_col);
				wk3 = y - wk2;
				for (unsigned int l = 0; l < X.m_row; l++) {
					sum += wk3(0, l);
				}

				sum /= calcX.m_row;

				beta(0, 0) = sum;

			}

		}
	}

	for (unsigned int l = 0; l < X.m_col; l++) {
		coef_->val[0][l] = beta(0, l + 1);
	}

	if (fit_intercept_) {
		intercept_ = beta(0, 0);
	}
	else {
		intercept_ = 0;
	}

}

Matrix Lasso::predict(const Matrix& X) {

	Matrix y(1, X.m_row);

	for (unsigned int i = 0; i < X.m_col; i++) {
		for (unsigned int j = 0; j < X.m_row; j++) {
			y(0, j) += X.val[j][i] * coef_->val[0][i];
		}
	}

	if (fit_intercept_) {
		y += intercept_;
	}

	return y;
}

#endif // _LASSO_H_
