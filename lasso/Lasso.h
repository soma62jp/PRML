#ifndef _LASSO_H_
#define _LASSO_H_

#include "Matrix.h"
#include "numpy.h"

using namespace arith;
using namespace std;

	//------------------------------------------//
	//             Lasso回帰                    //
	//------------------------------------------//
	class Lasso{

		private:

			double alpha_;				// 正則化項の係数
			int max_iter_;				// 繰り返しの回数
			bool fit_intercept_;		// 切片(i.e., ¥beta_0)を用いるか
			Matrix* coef_;				// 回帰係数(i.e., ¥beta)保存用変数
			double intercept_;			// 切片保存用変数

		public:
			// 
			explicit Lasso(double alpha, int max_iter, bool fit_intercept);

			// 
			virtual ~Lasso();

			double soft_thresholding_operator(double x, double lambda);

			void fit(const Matrix& X, const Matrix& y);

			Matrix predict(const Matrix& X);

	};

	//
	Lasso::Lasso(double alpha, int max_iter, bool fit_intercept) : alpha_(1.0), max_iter_(1000),fit_intercept_(true)
	{
		alpha_ = alpha ;
		max_iter_ = max_iter ;
		fit_intercept_ = fit_intercept;
		coef_ = NULL;
		intercept_ = 0;
	}

	Lasso::~Lasso(){
		delete coef_;
	}

	double Lasso::soft_thresholding_operator(double x, double lambda){

		if ((x > 0) && (lambda < abs(x))){
		  return x - lambda;
		}else if ((x < 0) && (lambda < abs(x))){
		  return x + lambda;
		}else{
		  return 0;
		}

	}

	void Lasso::fit(const Matrix& X, const Matrix& y){

		coef_ = new Matrix(1,1);    // coefのサイズを作る

		//fit_intercept_=true
		Matrix calcX(X.m_row, X.m_col + 1);

		for(unsigned int i=0;i<X.m_row;i++){
			for(unsigned int j=0;j<X.m_col;j++){
				calcX.val[i][j + 1] = X.val[i][j];
			}
		}

		if (fit_intercept_){
			//XX = np.column_stack((np.ones(len(X)),X))
			for(unsigned int i=0;i<calcX.m_col;i++){
				calcX(i,0) = 1;
			}
		}

		//numpy::print(calcX);


	}

	Matrix Lasso::predict(const Matrix& X){

		Matrix y = numpy::mult(X,*coef_);   //
		Matrix wrk(1, y.m_col);

		//np.ones(len(y))
		for(unsigned int i=0;i<y.m_col;i++){
			wrk(0,i) = 1;
		}

		if (fit_intercept_){
			y += wrk * intercept_;
		}

		return y;
	}

#endif // _LASSO_H_