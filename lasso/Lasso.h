#ifndef _LASSO_H_
#define _LASSO_H_

#include "Matrix.h"
#include "numpy.h"

using namespace arith;
using namespace std;

	//------------------------------------------//
	//              ク　ラ　ス                   //
	//------------------------------------------//
	class Lasso{

		private:

			double alpha_;				// 正則化項の係数
			int max_iter_;				// 繰り返しの回数
			bool fit_intercept_;		// 切片(i.e., \beta_0)を用いるか
			Matrix coef_;				// 回帰係数(i.e., \beta)保存用変数
			double intercept_;			// 切片保存用変数

		public:
			// コンストラクタ
			explicit Lasso(double alpha, int max_iter, bool fit_intercept);

			// デストラクタ
			virtual ~Lasso();

			void soft_thresholding_operator(double x, double lambda);

			void fit(const Matrix& X, const Matrix& y);

			Matrix predict(const Matrix& X);

	};

		// 行列要素を初期化する
	Lasso::Lasso(double alpha, int max_iter, bool fit_intercept) : alpha(1.0), max_iter(1000),fit_intercept(true)
	{
		alpha_ = alpha ;
		max_iter_ = max_iter ;
		fit_intercept_ = fit_intercept ;
		coef_ = 0 ;
		intercept_ = 0;
	}

	void Lasso::soft_thresholding_operator(double x, double lambda){

		if ((x > 0) && (lambda < abs(x))){
		  return x - lambda;
		}else if ((x < 0) && (lambda < abs(x))){
		  return x + lambda;
		}else{
		  return 0;
		}

	}

	void Lasso::fit(const Matrix& X, const Matrix& y){

		//fit_intercept_=true
		Matrix calcX(X.m_row, X.m_col + 1);

		for(int i=0;i<X.m_row;i++){
			for(int j=0;j<X.m_col;j++){
				calcX(i,j + 1) = X(i,j);
			}
		}

		if (fit_intercept_){
			//XX = np.column_stack((np.ones(len(X)),X))
			for(int i=0;i<calcX.m_col;i++){
				calcX(i,0)=1;
			}
		}


	}

	Matrix Lasso::predict(const Matrix& X){

		Matrix y = numpy::mult(X,coef_);   // 内積
		Matrix wrk(1, y.m_col);

		//np.ones(len(y))
		for(int i=0;i<y.m_col;i++){
			wrk(0,i)=1;
		}

		if (fit_intercept_){
			y += intercept_ * wrk;
		}

		return y;
	}

#endif // _LASSO_H_

